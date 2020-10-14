/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include QMK_KEYBOARD_H

// Define layer names
#define _NORMAL 0
#define _FNONE 1
#define _FNTWO 2

// Highly Modified by Xydane
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NORMAL] = LAYOUT_seventy_iso(
	KC_END, KC_TRNS, KC_MINUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSHIFT, KC_M, KC_V, KC_X, KC_C, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, \
	KC_RIGHT, KC_ENTER, KC_UP, KC_NO, KC_TRNS, KC_INSERT, KC_LSHIFT, KC_N, KC_B, KC_Z, KC_SPACE, KC_LALT, KC_DOWN, KC_TRNS, KC_LGUI, \
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F8, KC_F7, KC_TRNS, KC_TRNS, KC_G, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_LCTRL, KC_TRNS, \
	KC_PSCREEN, KC_NUMLOCK, KC_F12, KC_TRNS, KC_F9, KC_F6, KC_TRNS, KC_Y, KC_T, KC_F1, KC_F4, KC_TRNS, KC_F11, KC_TAB, KC_TRNS, \
	KC_DELETE, KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_F5, KC_TRNS, KC_6, KC_5, KC_ESCAPE, KC_CAPSLOCK, KC_TRNS, KC_F10, KC_TRNS, KC_TRNS, \
	KC_HOME, KC_BSPACE, KC_P, KC_TRNS, KC_TRNS, KC_8, KC_TRNS, KC_7, KC_4, KC_2, KC_3, KC_TRNS, KC_9, KC_1, KC_TRNS, \
	KC_PGDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, KC_I, KC_TRNS, KC_U, KC_R, KC_W, KC_E, KC_TRNS, KC_O, KC_Q, KC_TRNS, \
	KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_K, KC_TRNS, KC_J, KC_F, KC_TRNS, KC_TRNS, KC_TRNS, KC_L, KC_A, KC_TRNS), 

  [_FNONE] = LAYOUT_seventy_iso(
	KC_END, KC_TRNS, KC_MINUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSHIFT, KC_M, KC_V, KC_X, KC_C, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, \
	KC_RIGHT, KC_ENTER, KC_UP, KC_NO, KC_TRNS, KC_INSERT, KC_LSHIFT, KC_N, KC_B, KC_Z, KC_SPACE, KC_LALT, KC_DOWN, KC_TRNS, KC_LGUI, \
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F8, KC_F7, KC_TRNS, KC_TRNS, KC_G, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_LCTRL, KC_TRNS, \
	KC_PSCREEN, KC_NUMLOCK, KC_F12, KC_TRNS, KC_F9, KC_F6, KC_TRNS, KC_Y, KC_T, KC_F1, KC_F4, KC_TRNS, KC_F11, KC_TAB, KC_TRNS, \
	KC_DELETE, KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_F5, KC_TRNS, KC_6, KC_5, KC_ESCAPE, KC_CAPSLOCK, KC_TRNS, KC_F10, KC_TRNS, KC_TRNS, \
	KC_HOME, KC_BSPACE, KC_P, KC_TRNS, KC_TRNS, KC_8, KC_TRNS, KC_7, KC_4, KC_2, KC_3, KC_TRNS, KC_9, KC_1, KC_TRNS, \
	KC_PGDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, KC_I, KC_TRNS, KC_U, KC_R, KC_W, KC_E, KC_TRNS, KC_O, KC_Q, KC_TRNS, \
	KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_K, KC_TRNS, KC_J, KC_F, KC_TRNS, KC_TRNS, KC_TRNS, KC_L, KC_A, KC_TRNS), 

  [_FNTWO] = LAYOUT_seventy_iso(
	KC_END, KC_TRNS, KC_MINUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSHIFT, KC_M, KC_V, KC_X, KC_C, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, \
	KC_RIGHT, KC_ENTER, KC_UP, KC_NO, KC_TRNS, KC_INSERT, KC_LSHIFT, KC_N, KC_B, KC_Z, KC_SPACE, KC_LALT, KC_DOWN, KC_TRNS, KC_LGUI, \
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F8, KC_F7, KC_TRNS, KC_TRNS, KC_G, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_LCTRL, KC_TRNS, \
	KC_PSCREEN, KC_NUMLOCK, KC_F12, KC_TRNS, KC_F9, KC_F6, KC_TRNS, KC_Y, KC_T, KC_F1, KC_F4, KC_TRNS, KC_F11, KC_TAB, KC_TRNS, \
	KC_DELETE, KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_F5, KC_TRNS, KC_6, KC_5, KC_ESCAPE, KC_CAPSLOCK, KC_TRNS, KC_F10, KC_TRNS, KC_TRNS, \
	KC_HOME, KC_BSPACE, KC_P, KC_TRNS, KC_TRNS, KC_8, KC_TRNS, KC_7, KC_4, KC_2, KC_3, KC_TRNS, KC_9, KC_1, KC_TRNS, \
	KC_PGDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, KC_I, KC_TRNS, KC_U, KC_R, KC_W, KC_E, KC_TRNS, KC_O, KC_Q, KC_TRNS, \
	KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_K, KC_TRNS, KC_J, KC_F, KC_TRNS, KC_TRNS, KC_TRNS, KC_L, KC_A, KC_TRNS), 	

};

/* Layer based ilumination, just binary */
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
  case _FNONE:
    palSetPad(GPIOB, 0);  //OFF Color A
    palClearPad(GPIOB, 1); //ON Color B
    break;
  case _FNTWO:
    palClearPad(GPIOB, 0); //ON Color A
    palClearPad(GPIOB, 1);  //ON Color B
    break;
  default: //  for any other layers, or the default layer
    palClearPad(GPIOB, 0); //ON Color A
    palSetPad(GPIOB, 1);  //OFF Color B
    break;
    }
  return state;
}
