#include "keyblocks.h"
#include "i2cmaster.h"

bool i2c_initialized = 0;
uint8_t i2c_addr_array[8];
uint8_t expanders_connected = 0;

__attribute__ ((weak))
void * matrix_init_user(void) {
    return NULL;
};

__attribute__ ((weak))
void * matrix_scan_user(void) {
    return NULL;
};

void * matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - D7, E6
    // set as input with internal pull-ip enabled
    // DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<7);
    DDRE  &= ~(1<<6);
    // PORTC |=  (1<<7);
    PORTD |=  (1<<7);
    PORTE |=  (1<<6);

    if (matrix_init_user) {
        (*matrix_init_user)();
    }

    return NULL;
};

void * matrix_scan_kb(void) {

    if (matrix_scan_user) {
        (*matrix_scan_user)();
    }

    return NULL;
};


void keyblocks_blink_all_leds(void)
{
    keyblocks_led_all_off();
    keyblocks_led_all_set(LED_BRIGHTNESS_HI);
    keyblocks_right_led_1_on();
    _delay_ms(50);
    keyblocks_right_led_2_on();
    _delay_ms(50);
    keyblocks_right_led_3_on();
    _delay_ms(50);
    keyblocks_right_led_1_off();
    _delay_ms(50);
    keyblocks_right_led_2_off();
    _delay_ms(50);
    keyblocks_right_led_3_off();
    //keyblocks_led_all_on();
    //_delay_ms(333);
    keyblocks_led_all_off();
}

void init_mcp23018(uint8_t *mcp_status_arr) {

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized++;
        _delay_ms(1000);
    }

    // Scan for connected MCP chips, from 0x20 to 0x27
    for (uint8_t i=0; i<8; i++) {
        mcp_status_arr[i] = 1;
        uint8_t test_addr = 0x20 + i; // BANANA - Maybe change this, the address could be wrong
        uint8_t test_addr_write = ( (test_addr<<1) | 0 );
        uint8_t test_addr_read = ( (test_addr<<1) | 1 );
        mcp_status_arr[expanders_connected] = i2c_start(test_addr_write);
        i2c_stop();
        if (mcp_status_arr[expanders_connected] == 0) {
            i2c_addr_array[expanders_connected] = test_addr;
            expanders_connected++;
            // keyblocks_blink_all_leds();
            // _delay_ms(50);
        }
    } 

    for (uint8_t i=0; i<expanders_connected; i++) {

        uint8_t addr_from_arr = i2c_addr_array[i];
        uint8_t addr_to_write = ( (addr_from_arr<<1) | 0 );

        // set pin direction
        // - unused  : input  : 1
        // - input   : input  : 1
        // - driving : output : 0
        mcp_status_arr[i] = i2c_start(addr_to_write);     if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(IODIRA);            if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(0b00000000);        if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(0b11111111);        if (mcp_status_arr[i] == 1) goto out;
        i2c_stop();

        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp_status_arr[i] = i2c_start(addr_to_write);     if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(GPPUA);             if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(0b00000000);        if (mcp_status_arr[i] == 1) goto out;
        mcp_status_arr[i] = i2c_write(0b11111111);        if (mcp_status_arr[i] == 1) goto out;

        out:
            i2c_stop();

    } //closing MCP23018Array loop

    // return mcp23018_status;
}


