#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Keymap 0: Basic layer
[BASE] = KEYMAP(
    // Teensy
    KC_0,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_1,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_2,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_3,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_4,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_5,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_6,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_7,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    
    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,

    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O  

    // // MCP23018 chip 3
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 4
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 5
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 6
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 7
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 8
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7
),
// Keymap 1: Symbol Layer
[SYMB] = KEYMAP(
    // Teensy
    KC_0,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_1,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_2,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_3,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_4,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_5,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_6,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_7,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    
    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,

    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O 

    // // MCP23018 chip 3
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 4
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 5
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 6
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 7
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 8
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7
),
// Keymap 2: Media and mouse keys
[MDIA] = KEYMAP(
    // Teensy
    KC_0,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_1,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_2,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_3,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_4,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_5,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_6,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    KC_7,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,
    
    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,

    // MCP23018 chip 1
    KC_8,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_9,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_A,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_W,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_X,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Y,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_Z,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    KC_EQL,  KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O
     
    // // MCP23018 chip 3
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 4
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 5
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 6
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 7
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,

    // // MCP23018 chip 8
    // KC_I,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_J,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_K,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_L,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_M,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_N,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_O,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // KC_P,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7
)
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
