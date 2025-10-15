/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H



/*
  Unicode map for special characters I use.
*/
enum unicode_names {
  JP_YEN,
  JP_CMA,
  JP_STP,
  JP_OBR,
  JP_CBR,
};


const uint32_t PROGMEM unicode_map[] = {
  [JP_YEN] = 0x00A5,  // ¥
  [JP_CMA] = 0x3001,  // 、
  [JP_STP] = 0x3002,  // 。
  [JP_OBR] = 0x3010,  //【
  [JP_CBR] = 0x3011,  // 】
};


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    BASE,
    FUNC,
    SYMB
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap BASE: Base Layer (Default Layer)
   */
[BASE] = LAYOUT_65_ansi_blocker(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* Keymap FUNC: Function Layer
   */
[FUNC] = LAYOUT_65_ansi_blocker(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_DEL,  KC_MPLY,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,   _______,  KC_MNXT,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             KC_VOLU,
    MO(2),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  KC_VOLD,
  _______,  _______,  _______,                                QK_BOOT,                                _______,  _______,  _______,   _______,  _______
  ),

  /* Keymap SYMB: Symbol Layer
   */
[SYMB] = LAYOUT_65_ansi_blocker(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, UM(JP_OBR), UM(JP_CBR), UM(JP_YEN), _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  UM(JP_CMA),  UM(JP_STP),  _______,  _______,             _______,  _______,
  _______,  _______,  _______,                                QK_BOOT,                                _______,  _______,  _______,   _______,  _______
  )
};


void keyboard_post_init_user(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv_noeeprom(HSV_OFF);
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  switch(get_highest_layer(layer_state)) {
    case BASE:
      rgb_matrix_set_color_all(118, 181, 216);        /* #76b5d8 */
      break;
    case FUNC:
      rgb_matrix_set_color_all(105, 0, 255);          /* #6900ff */
      break;
    case SYMB:
      rgb_matrix_set_color_all(255, 255, 255);        /* #ffffff */
      break;
    default:
      break;
    break;
  }

  if(host_keyboard_led_state().caps_lock) {
    for(int i = 77; i <= 86; i++) {
      RGB_MATRIX_INDICATOR_SET_COLOR(i, 255, 0, 255); /* #ff00ff */
    }
  } else {
    switch(get_highest_layer(layer_state)) {
      case BASE:
        rgb_matrix_set_color_all(118, 181, 216);        /* #76b5d8 */
        break;
      case FUNC:
        rgb_matrix_set_color_all(105, 0, 255);          /* #6900ff */
        break;
      case SYMB:
        rgb_matrix_set_color_all(255, 255, 255);        /* #ffffff */
        break;
      default:
        break;
      break;
    }
  }
  return false;
}