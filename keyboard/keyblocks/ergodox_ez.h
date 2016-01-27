#ifndef ERGODOX_EZ_H
#define ERGODOX_EZ_H

#include "matrix.h"
#include "keymap_common.h"
#include "backlight.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
// Last three binary characters define address 000 = 0x20, 001 = 0x21, 010 = 0x22, 011 = 0x23 etc. up to 0x27
extern uint8_t expanders_connected;
extern uint8_t i2c_addr_array[8];
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t mcp23018_status;
// status uint8_t mcp_status_arr[8];

void init_ergodox(void);
void ergodox_blink_all_leds(void);
void init_mcp23018(uint8_t *mcp_status_arr, size_t mcp_status_arr_size);
uint8_t ergodox_left_leds_update(void);

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255


inline void ergodox_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void ergodox_right_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void ergodox_right_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void ergodox_right_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void ergodox_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

inline void ergodox_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void ergodox_right_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void ergodox_right_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void ergodox_right_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void ergodox_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

inline void ergodox_led_all_on(void)
{
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

inline void ergodox_led_all_off(void)
{
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

inline void ergodox_right_led_1_set(uint8_t n)    { OCR1A = n; }
inline void ergodox_right_led_2_set(uint8_t n)    { OCR1B = n; }
inline void ergodox_right_led_3_set(uint8_t n)    { OCR1C = n; }
inline void ergodox_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void ergodox_led_all_set(uint8_t n)
{
    ergodox_right_led_1_set(n);
    ergodox_right_led_2_set(n);
    ergodox_right_led_3_set(n);
}

#define KEYMAP( \
      k00A, k00B, k00C, k00D, k00E, k00F, k00G, k00H, \
      k01A, k01B, k01C, k01D, k01E, k01F, k01G, k01H, \
      k02A, k02B, k02C, k02D, k02E, k02F, k02G, k02H, \
      k03A, k03B, k03C, k03D, k03E, k03F, k03G, k03H, \
      k04A, k04B, k04C, k04D, k04E, k04F, k04G, k04H, \
      k05A, k05B, k05C, k05D, k05E, k05F, k05G, k05H, \
      k06A, k06B, k06C, k06D, k06E, k06F, k06G, k06H, \
      k07A, k07B, k07C, k07D, k07E, k07F, k07G, k07H, \
      k08A, k08B, k08C, k08D, k08E, k08F, k08G, k08H, \
      k09A, k09B, k09C, k09D, k09E, k09F, k09G, k09H, \
      k10A, k10B, k10C, k10D, k10E, k10F, k10G, k10H, \
      k11A, k11B, k11C, k11D, k11E, k11F, k11G, k11H, \
      k12A, k12B, k12C, k12D, k12E, k12F, k12G, k12H, \
      k13A, k13B, k13C, k13D, k13E, k13F, k13G, k13H, \
      k14A, k14B, k14C, k14D, k14E, k14F, k14G, k14H, \
      k15A, k15B, k15C, k15D, k15E, k15F, k15G, k15H  \
) \
{ \
    { k00A, k00B, k00C, k00D, k00E, k00F, k00G, k00H }, \
    { k01A, k01B, k01C, k01D, k01E, k01F, k01G, k01H }, \
    { k02A, k02B, k02C, k02D, k02E, k02F, k02G, k02H }, \
    { k03A, k03B, k03C, k03D, k03E, k03F, k03G, k03H }, \
    { k04A, k04B, k04C, k04D, k04E, k04F, k04G, k04H }, \
    { k05A, k05B, k05C, k05D, k05E, k05F, k05G, k05H }, \
    { k06A, k06B, k06C, k06D, k06E, k06F, k06G, k06H }, \
    { k07A, k07B, k07C, k07D, k07E, k07F, k07G, k07H }, \
    { k08A, k08B, k08C, k08D, k08E, k08F, k08G, k08H }, \
    { k09A, k09B, k09C, k09D, k09E, k09F, k09G, k09H }, \
    { k10A, k10B, k10C, k10D, k10E, k10F, k10G, k10H }, \
    { k11A, k11B, k11C, k11D, k11E, k11F, k11G, k11H }, \
    { k12A, k12B, k12C, k12D, k12E, k12F, k12G, k12H }, \
    { k13A, k13B, k13C, k13D, k13E, k13F, k13G, k13H }, \
    { k14A, k14B, k14C, k14D, k14E, k14F, k14G, k14H }, \
    { k15A, k15B, k15C, k15D, k15E, k15F, k15G, k15H }  \
} 

// #define KEYMAP( \
//       k00A, k00B, k00C, k00D, k00E, k00F, k00G, k00H, \
//       k01A, k01B, k01C, k01D, k01E, k01F, k01G, k01H, \
//       k02A, k02B, k02C, k02D, k02E, k02F, k02G, k02H, \
//       k03A, k03B, k03C, k03D, k03E, k03F, k03G, k03H, \
//       k04A, k04B, k04C, k04D, k04E, k04F, k04G, k04H, \
//       k05A, k05B, k05C, k05D, k05E, k05F, k05G, k05H, \
//       k06A, k06B, k06C, k06D, k06E, k06F, k06G, k06H, \
//       k07A, k07B, k07C, k07D, k07E, k07F, k07G, k07H, \
//       k08A, k08B, k08C, k08D, k08E, k08F, k08G, k08H, \
//       k09A, k09B, k09C, k09D, k09E, k09F, k09G, k09H, \
//       k10A, k10B, k10C, k10D, k10E, k10F, k10G, k10H, \
//       k11A, k11B, k11C, k11D, k11E, k11F, k11G, k11H, \
//       k12A, k12B, k12C, k12D, k12E, k12F, k12G, k12H, \
//       k13A, k13B, k13C, k13D, k13E, k13F, k13G, k13H, \
//       k14A, k14B, k14C, k14D, k14E, k14F, k14G, k14H, \
//       k15A, k15B, k15C, k15D, k15E, k15F, k15G, k15H, \
//       k16A, k16B, k16C, k16D, k16E, k16F, k16G, k16H, \
//       k17A, k17B, k17C, k17D, k17E, k17F, k17G, k17H, \
//       k18A, k18B, k18C, k18D, k18E, k18F, k18G, k18H, \
//       k19A, k19B, k19C, k19D, k19E, k19F, k19G, k19H, \
//       k20A, k20B, k20C, k20D, k20E, k20F, k20G, k20H, \
//       k21A, k21B, k21C, k21D, k21E, k21F, k21G, k21H, \
//       k22A, k22B, k22C, k22D, k22E, k22F, k22G, k22H, \
//       k23A, k23B, k23C, k23D, k23E, k23F, k23G, k23H, \
//       k24A, k24B, k24C, k24D, k24E, k24F, k24G, k24H, \
//       k25A, k25B, k25C, k25D, k25E, k25F, k25G, k25H, \
//       k26A, k26B, k26C, k26D, k26E, k26F, k26G, k26H, \
//       k27A, k27B, k27C, k27D, k27E, k27F, k27G, k27H, \
//       k28A, k28B, k28C, k28D, k28E, k28F, k28G, k28H, \
//       k29A, k29B, k29C, k29D, k29E, k29F, k29G, k29H, \
//       k30A, k30B, k30C, k30D, k30E, k30F, k30G, k30H, \
//       k31A, k31B, k31C, k31D, k31E, k31F, k31G, k31H, \
//       k32A, k32B, k32C, k32D, k32E, k32F, k32G, k32H, \
//       k33A, k33B, k33C, k33D, k33E, k33F, k33G, k33H, \
//       k34A, k34B, k34C, k34D, k34E, k34F, k34G, k34H, \
//       k35A, k35B, k35C, k35D, k35E, k35F, k35G, k35H, \
//       k36A, k36B, k36C, k36D, k36E, k36F, k36G, k36H, \
//       k37A, k37B, k37C, k37D, k37E, k37F, k37G, k37H, \
//       k38A, k38B, k38C, k38D, k38E, k38F, k38G, k38H, \
//       k39A, k39B, k39C, k39D, k39E, k39F, k39G, k39H, \
//       k40A, k40B, k40C, k40D, k40E, k40F, k40G, k40H, \
//       k41A, k41B, k41C, k41D, k41E, k41F, k41G, k41H, \
//       k42A, k42B, k42C, k42D, k42E, k42F, k42G, k42H, \
//       k43A, k43B, k43C, k43D, k43E, k43F, k43G, k43H, \
//       k44A, k44B, k44C, k44D, k44E, k44F, k44G, k44H, \
//       k45A, k45B, k45C, k45D, k45E, k45F, k45G, k45H, \
//       k46A, k46B, k46C, k46D, k46E, k46F, k46G, k46H, \
//       k47A, k47B, k47C, k47D, k47E, k47F, k47G, k47H, \
//       k48A, k48B, k48C, k48D, k48E, k48F, k48G, k48H, \
//       k49A, k49B, k49C, k49D, k49E, k49F, k49G, k49H, \
//       k50A, k50B, k50C, k50D, k50E, k50F, k50G, k50H, \
//       k51A, k51B, k51C, k51D, k51E, k51F, k51G, k51H, \
//       k52A, k52B, k52C, k52D, k52E, k52F, k52G, k52H, \
//       k53A, k53B, k53C, k53D, k53E, k53F, k53G, k53H, \
//       k54A, k54B, k54C, k54D, k54E, k54F, k54G, k54H, \
//       k55A, k55B, k55C, k55D, k55E, k55F, k55G, k55H, \
//       k56A, k56B, k56C, k56D, k56E, k56F, k56G, k56H, \
//       k57A, k57B, k57C, k57D, k57E, k57F, k57G, k57H, \
//       k58A, k58B, k58C, k58D, k58E, k58F, k58G, k58H, \
//       k59A, k59B, k59C, k59D, k59E, k59F, k59G, k59H, \
//       k60A, k60B, k60C, k60D, k60E, k60F, k60G, k60H, \
//       k61A, k61B, k61C, k61D, k61E, k61F, k61G, k61H, \
//       k62A, k62B, k62C, k62D, k62E, k62F, k62G, k62H, \
//       k63A, k63B, k63C, k63D, k63E, k63F, k63G, k63H, \
//       k64A, k64B, k64C, k64D, k64E, k64F, k64G, k64H, \
//       k65A, k65B, k65C, k65D, k65E, k65F, k65G, k65H, \
//       k66A, k66B, k66C, k66D, k66E, k66F, k66G, k66H, \
//       k67A, k67B, k67C, k67D, k67E, k67F, k67G, k67H, \
//       k68A, k68B, k68C, k68D, k68E, k68F, k68G, k68H, \
//       k69A, k69B, k69C, k69D, k69E, k69F, k69G, k69H, \
//       k70A, k70B, k70C, k70D, k70E, k70F, k70G, k70H, \
//       k71A, k71B, k71C, k71D, k71E, k71F, k71G, k71H  \
// ) \
// { \
//     { k00A, k00B, k00C, k00D, k00E, k00F, k00G, k00H }, \
//     { k01A, k01B, k01C, k01D, k01E, k01F, k01G, k01H }, \
//     { k02A, k02B, k02C, k02D, k02E, k02F, k02G, k02H }, \
//     { k03A, k03B, k03C, k03D, k03E, k03F, k03G, k03H }, \
//     { k04A, k04B, k04C, k04D, k04E, k04F, k04G, k04H }, \
//     { k05A, k05B, k05C, k05D, k05E, k05F, k05G, k05H }, \
//     { k06A, k06B, k06C, k06D, k06E, k06F, k06G, k06H }, \
//     { k07A, k07B, k07C, k07D, k07E, k07F, k07G, k07H }, \
//     { k08A, k08B, k08C, k08D, k08E, k08F, k08G, k08H }, \
//     { k09A, k09B, k09C, k09D, k09E, k09F, k09G, k09H }, \
//     { k10A, k10B, k10C, k10D, k10E, k10F, k10G, k10H }, \
//     { k11A, k11B, k11C, k11D, k11E, k11F, k11G, k11H }, \
//     { k12A, k12B, k12C, k12D, k12E, k12F, k12G, k12H }, \
//     { k13A, k13B, k13C, k13D, k13E, k13F, k13G, k13H }, \
//     { k14A, k14B, k14C, k14D, k14E, k14F, k14G, k14H }, \
//     { k15A, k15B, k15C, k15D, k15E, k15F, k15G, k15H }, \
//     { k16A, k16B, k16C, k16D, k16E, k16F, k16G, k16H }, \
//     { k17A, k17B, k17C, k17D, k17E, k17F, k17G, k17H }, \
//     { k18A, k18B, k18C, k18D, k18E, k18F, k18G, k18H }, \
//     { k19A, k19B, k19C, k19D, k19E, k19F, k19G, k19H }, \
//     { k20A, k20B, k20C, k20D, k20E, k20F, k20G, k20H }, \
//     { k21A, k21B, k21C, k21D, k21E, k21F, k21G, k21H }, \
//     { k22A, k22B, k22C, k22D, k22E, k22F, k22G, k22H }, \
//     { k23A, k23B, k23C, k23D, k23E, k23F, k23G, k23H }, \
//     { k24A, k24B, k24C, k24D, k24E, k24F, k24G, k24H }, \
//     { k25A, k25B, k25C, k25D, k25E, k25F, k25G, k25H }, \
//     { k26A, k26B, k26C, k26D, k26E, k26F, k26G, k26H }, \
//     { k27A, k27B, k27C, k27D, k27E, k27F, k27G, k27H }, \
//     { k28A, k28B, k28C, k28D, k28E, k28F, k28G, k28H }, \
//     { k29A, k29B, k29C, k29D, k29E, k29F, k29G, k29H }, \
//     { k30A, k30B, k30C, k30D, k30E, k30F, k30G, k30H }, \
//     { k31A, k31B, k31C, k31D, k31E, k31F, k31G, k31H }, \
//     { k32A, k32B, k32C, k32D, k32E, k32F, k32G, k32H }, \
//     { k33A, k33B, k33C, k33D, k33E, k33F, k33G, k33H }, \
//     { k34A, k34B, k34C, k34D, k34E, k34F, k34G, k34H }, \
//     { k35A, k35B, k35C, k35D, k35E, k35F, k35G, k35H }, \
//     { k36A, k36B, k36C, k36D, k36E, k36F, k36G, k36H }, \
//     { k37A, k37B, k37C, k37D, k37E, k37F, k37G, k37H }, \
//     { k38A, k38B, k38C, k38D, k38E, k38F, k38G, k38H }, \
//     { k39A, k39B, k39C, k39D, k39E, k39F, k39G, k39H }, \
//     { k40A, k40B, k40C, k40D, k40E, k40F, k40G, k40H }, \
//     { k41A, k41B, k41C, k41D, k41E, k41F, k41G, k41H }, \
//     { k42A, k42B, k42C, k42D, k42E, k42F, k42G, k42H }, \
//     { k43A, k43B, k43C, k43D, k43E, k43F, k43G, k43H }, \
//     { k44A, k44B, k44C, k44D, k44E, k44F, k44G, k44H }, \
//     { k45A, k45B, k45C, k45D, k45E, k45F, k45G, k45H }, \
//     { k46A, k46B, k46C, k46D, k46E, k46F, k46G, k46H }, \
//     { k47A, k47B, k47C, k47D, k47E, k47F, k47G, k47H }, \
//     { k48A, k48B, k48C, k48D, k48E, k48F, k48G, k48H }, \
//     { k49A, k49B, k49C, k49D, k49E, k49F, k49G, k49H }, \
//     { k50A, k50B, k50C, k50D, k50E, k50F, k50G, k50H }, \
//     { k51A, k51B, k51C, k51D, k51E, k51F, k51G, k51H }, \
//     { k52A, k52B, k52C, k52D, k52E, k52F, k52G, k52H }, \
//     { k53A, k53B, k53C, k53D, k53E, k53F, k53G, k53H }, \
//     { k54A, k54B, k54C, k54D, k54E, k54F, k54G, k54H }, \
//     { k55A, k55B, k55C, k55D, k55E, k55F, k55G, k55H }, \
//     { k56A, k56B, k56C, k56D, k56E, k56F, k56G, k56H }, \
//     { k57A, k57B, k57C, k57D, k57E, k57F, k57G, k57H }, \
//     { k58A, k58B, k58C, k58D, k58E, k58F, k58G, k58H }, \
//     { k59A, k59B, k59C, k59D, k59E, k59F, k59G, k59H }, \
//     { k60A, k60B, k60C, k60D, k60E, k60F, k60G, k60H }, \
//     { k61A, k61B, k61C, k61D, k61E, k61F, k61G, k61H }, \
//     { k62A, k62B, k62C, k62D, k62E, k62F, k62G, k62H }, \
//     { k63A, k63B, k63C, k63D, k63E, k63F, k63G, k63H }, \
//     { k64A, k64B, k64C, k64D, k64E, k64F, k64G, k64H }, \
//     { k65A, k65B, k65C, k65D, k65E, k65F, k65G, k65H }, \
//     { k66A, k66B, k66C, k66D, k66E, k66F, k66G, k66H }, \
//     { k67A, k67B, k67C, k67D, k67E, k67F, k67G, k67H }, \
//     { k68A, k68B, k68C, k68D, k68E, k68F, k68G, k68H }, \
//     { k69A, k69B, k69C, k69D, k69E, k69F, k69G, k69H }, \
//     { k70A, k70B, k70C, k70D, k70E, k70F, k70G, k70H }, \
//     { k71A, k71B, k71C, k71D, k71E, k71F, k71G, k71H }  \
// } 

void * matrix_init_user(void);
void * matrix_scan_user(void);



#endif
