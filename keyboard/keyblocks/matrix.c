/*

Note for ErgoDox EZ customizers: Here be dragons!
This is not a file you want to be messing with.
All of the interesting stuff for you is under keymaps/ :)
Love, Erez

Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "ergodox_ez.h"
#include "i2cmaster.h"
#ifdef DEBUG_MATRIX_SCAN_RATE
#include  "timer.h"
#endif

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows();
static void select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;

#ifdef DEBUG_MATRIX_SCAN_RATE
uint32_t matrix_timer;
uint32_t matrix_scan_count;
#endif


__attribute__ ((weak))
void * matrix_init_kb(void) {
};

__attribute__ ((weak))
void * matrix_scan_kb(void) {
};

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // initialize row and col

    mcp23018_status = init_mcp23018();


    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif

    if (matrix_init_kb) {
        (*matrix_init_kb)();
    }

}

uint8_t matrix_scan(void)
{
    if (mcp23018_status) { // if there was an error
        if (++mcp23018_reset_loop == 0) {
            // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("MCP23018 not responding\n");
            } else {
                print("MCP23018 ready\n");
                ergodox_blink_all_leds();
            }
        }
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_scan_count++;

    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, matrix_timer)>1000) {
        print("matrix scan frequency: ");
        pdec(matrix_scan_count);
        print("\n");

        matrix_timer = timer_now;
        matrix_scan_count = 0;
    }
#endif

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        matrix_row_t cols = read_cols(i);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }


    if (matrix_scan_kb) {
        (*matrix_scan_kb)();
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

 /* Column pin configuration
 *
 * Teensy
 * col: A   B   C   D   E   F   G   H
 * pin: F0  F1  F4  F5  F6  F7  D4  D5
 *
 * MCP23018 @ 0x20 - 0x27
 * col: A   B   C   D   E   F   G   H
 * pin: B0  B1  B2  B3  B4  B5  B6  B7
 */
static void  init_cols(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // init on teensy
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
    PORTF |=  (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
    DDRD  &= ~(1<<5 | 1<<4);
    PORTD |=  (1<<5 | 1<<4);
}

static matrix_row_t read_cols(uint8_t row)
{
    if (row < 8) {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            for (uint8_t i=0; i<expanders_connected; i++) {
                uint8_t addr_from_arr = i2c_addr_array[i];
                uint8_t addr_to_write = ( (addr_from_arr<<1) | 0 );
                uint8_t addr_to_read = ( (addr_from_arr<<1) | 1 );
                mcp23018_status = i2c_start(addr_to_write);    if (mcp23018_status) goto out;
                mcp23018_status = i2c_write(GPIOB);            if (mcp23018_status) goto out;
                mcp23018_status = i2c_start(addr_to_read);     if (mcp23018_status) goto out;
                data = i2c_readNak();
                data = ~data;
            }
        out:
            i2c_stop();
            return data;
        }
    } else {
        _delay_us(30);  // without this wait read unstable value.
        // read from teensy
        return
            (PINF&(1<<0) ? 0 : (1<<0)) |
            (PINF&(1<<1) ? 0 : (1<<1)) |
            (PINF&(1<<4) ? 0 : (1<<2)) |
            (PINF&(1<<5) ? 0 : (1<<3)) |
            (PINF&(1<<6) ? 0 : (1<<4)) |
            (PINF&(1<<7) ? 0 : (1<<5)) |
            (PIND&(1<<4) ? 0 : (1<<6)) |
            (PIND&(1<<5) ? 0 : (1<<7)) ;
    }
}

 /* Row pin configuration
 *
 * Teensy - ACTIVE
 * row: 0   1   2   3   4   5   6   7
 * pin: B0  B1  B2  B3  D2  D3  C6  C7
 *
 * MCP23018 @ 0x20 - ACTIVE
 * row: 8   9   10  11  12  13  14  15
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
 *
 * MCP23018 @ 0x21
 * row: 16  17  18  19  20  21  22  23
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
 *
 * MCP23018 @ 0x22
 * row: 24  25  26  27  28  29  30  31
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
  *
 * MCP23018 @ 0x23
 * row: 32  33  34  35  36  37  38  39
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
  *
 * MCP23018 @ 0x24
 * row: 40  41  42  43  44  45  46  47
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
  *
 * MCP23018 @ 0x25
 * row: 48  49  50  51  52  53  54  55
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
  *
 * MCP23018 @ 0x26
 * row: 56  57  58  59  60  61  62  63
 * pin: A0  A1  A2  A3  A4  A5  A6  A7
  *
 * MCP23018 @ 0x27
 * row: 64  65  66  67  68  69  70  71
 * pin: A0  A1  A2  A3  A4  A5  A6  A7

 */

static void unselect_rows(void)
{
    // unselect on mcp23018
    if (mcp23018_status) { // if there was an error
        // do nothing
    } else {
        // set all rows hi-Z : 1
        for (uint8_t i=0; i<expanders_connected; i++) {
            uint8_t addr_from_arr = i2c_addr_array[i];
            uint8_t addr_to_write = ( (addr_from_arr<<1) | 0 );
            mcp23018_status = i2c_start(addr_to_write);     if (mcp23018_status) goto out0;
            mcp23018_status = i2c_write(GPIOA);             if (mcp23018_status) goto out0;
            mcp23018_status = i2c_write( 0xFF
                                & ~(0<<7)
                            );                              if (mcp23018_status) goto out0;
        }
    out0:
        i2c_stop();
    }

    // unselect on teensy
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    PORTB &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    DDRD  &= ~(1<<2 | 1<<3);
    PORTD &= ~(1<<2 | 1<<3);
    DDRC  &= ~(1<<6 | 1<<7);
    PORTC &= ~(1<<6 | 1<<7);
}

static void select_row(uint8_t row)
{
    switch (row) {
        // select on mcp23018
        case 0 ... 7:
            if (mcp23018_status) { // if there was an error
                // do nothing
            } else {
                // set active row low  : 0
                // set other rows hi-Z : 1
                    uint8_t addr_from_arr = i2c_addr_array[0];
                    uint8_t addr_to_write = ( (addr_from_arr<<1) | 0 );
                    mcp23018_status = i2c_start(addr_to_write);         
                    if (mcp23018_status) goto out1;
                    mcp23018_status = i2c_write(GPIOA);                 
                    if (mcp23018_status) goto out1;
                    mcp23018_status = i2c_write( 0xFF & ~(1<<row) & ~(0<<7) );                                
                    if (mcp23018_status) goto out1;
            out1:
                i2c_stop();
            }
            break;
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        case 8:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 9:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
        case 10:
            DDRB  |= (1<<2);
            PORTB &= ~(1<<2);
            break;
        case 11:
            DDRB  |= (1<<3);
            PORTB &= ~(1<<3);
            break;
        case 12:
            DDRD  |= (1<<2);
            PORTD &= ~(1<<2);
            break;
        case 13:
            DDRD  |= (1<<3);
            PORTD &= ~(1<<3);
            break;
        case 14:
            DDRC  |= (1<<6);
            PORTC &= ~(1<<6);
            break;
        case 15:
            DDRC  |= (1<<7);
            PORTC &= ~(1<<7);
            break;
        case 16 ... 23:
            if (mcp23018_status) { // if there was an error
                // do nothing
            } else {
                // set active row low  : 0
                // set other rows hi-Z : 1
                    uint8_t addr_from_arr = i2c_addr_array[1];
                    uint8_t addr_to_write = ( (addr_from_arr<<1) | 0 );
                    mcp23018_status = i2c_start(addr_to_write);         
                    if (mcp23018_status) goto out2;
                    mcp23018_status = i2c_write(GPIOA);                 
                    if (mcp23018_status) goto out2;
                    mcp23018_status = i2c_write( 0xFF & ~(1<<row) & ~(0<<7) );                                
                    if (mcp23018_status) goto out2;
            out2:
                i2c_stop();
            }
            break;
    }
}

