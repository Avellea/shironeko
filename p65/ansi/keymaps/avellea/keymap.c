/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.


/*
  Layer 1 is your traditional typing layout for this keyboard.
  Layer 2 is a function layer that includes media keys, print screen, and the bootloader shortcut. (fn+space).
  Media keys are aligned to the right edge.
  Layer 3 is currently not used. I don't know how to access it :p
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),

[1] = LAYOUT(
   KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,  KC_MPLY,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,   _______,  KC_MNXT,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             KC_VOLU,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             KC_VOLD,
  _______,  _______,  _______,                                RESET,                                  _______,  _______,  _______,  _______,  _______),

[2] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,                                _______,                                _______,  _______,  _______,   _______,  _______)
};

/*
  Disable all matrix effects except solid color on startup.
  TODO: Disable other effects in `config.h`. I would do this now
  but I have not tested functionality yet.
*/
void keyboard_post_init_user(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv_noeeprom(HSV_OFF);
}


void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

  /*
    Set the backlight color based on the current layer.
    i.e. Layer 0 = light blue, Layer 1 = purple.
  */
  switch(get_highest_layer(layer_state)) {
    case 0:
      rgb_matrix_set_color_all(118, 181, 216);        /* #76b5d8 */
      break;
    case 1:
      rgb_matrix_set_color_all(105, 0, 255);          /* #6900ff */
      break;
    default:
      break;
    break;
  }

  /*
    If caps lock is on, set the left light bar to pink.
    This does not. overrides the layer colors.
  */
  if(host_keyboard_led_state().caps_lock) {

    /* 
      The following for loop sets LED's 77 to 86 to pink. 
      These LED's correspond to the left "light bar" on the GMMK V2 keyboard.
    */
    for (int i = 77; i <= 86; i++) {
      RGB_MATRIX_INDICATOR_SET_COLOR(i, 255, 0, 255); /* #ff00ff */
    }
  } else {
    /*
      If caps lock is off, set the keyboard color based on the current layer.
    */
    if(get_highest_layer(layer_state) == 0) {
      rgb_matrix_set_color_all(118, 181, 216);        /* #76b5d8 */
    } else if(get_highest_layer(layer_state) == 1) {
      rgb_matrix_set_color_all(105, 0, 255);          /* #6900ff */
    }
  }
}