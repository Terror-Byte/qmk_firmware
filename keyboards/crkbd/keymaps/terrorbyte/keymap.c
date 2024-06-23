/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _SYMBOL,
    _NAVIGATION,
    _LED
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------.                    ,-------------------------------------------------------------.
       KC_ESC,        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,           KC_P,  KC_NUHS,
  //|--------+-------------+-------------+-------+--------+--------|                    |--------+--------+--------+--------+----------------+--------|
      KC_BSPC,        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,        KC_SCLN,  KC_QUOT,
  //|--------+-------------+-------------+-------+--------+--------|                    |--------+--------+--------+--------+----------------+--------|
      KC_LSFT, LCTL_T(KC_Z), LALT_T(KC_X),   KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, RCTL_T(KC_SLSH), KC_RSFT,
  //|--------+-------------+-------------+-------+--------+--------+--------|  |--------+--------+--------+--------+--------+----------------+--------|
                                          KC_TAB,   MO(_NAVIGATION),  KC_SPC,     KC_ENT,   MO(_SYMBOL), KC_LGUI
                                      //`-----------------------------------'  `--------------------------------'

    ),

    [_SYMBOL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                        KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_GRAVE,
  //|--------+--------+--------+--------+--------+--------|                    |----------+---------+--------+--------+--------+-----------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_NUBS, KC_MINUS,  KC_EQL, KC_LBRC, KC_RBRC, S(KC_NUBS),
  //|--------+--------+--------+--------+--------+--------|                    |----------+---------+--------+--------+--------+-----------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                        XXXXXXX,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,   _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+----------+---------+--------+--------+--------+-----------|
                                          _______, _______, _______,   _______,   _______, _______
                                      //`--------------------------'  `--------------------------'
    ),

    [_NAVIGATION] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,------------------------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_PGUP, KC_HOME,   KC_UP,   KC_END,             XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------------------+--------|
       KC_DEL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MEDIA_PLAY_PAUSE, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------------------+--------|
      _______, KC_LCTL,   KC_NO,   KC_NO,  KC_F11,  KC_F12,                      XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,             XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------------------+--------|
                                          _______, _______, _______,   _______,   _______, _______
                                      //`--------------------------'  `--------------------------'
    ),

    [_LED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMBOL, _NAVIGATION, _LED);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master())
        return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
    else
        return OLED_ROTATION_180;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char* read_layer_state(void);
const char* read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t* record);
const char* read_keylog(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_P(PSTR("-----"), false);
        switch (get_highest_layer(layer_state|default_layer_state))
        {
            case _QWERTY:
                oled_write_ln_P(PSTR("Base"), false);
                break;

            case _COLEMAK:
                oled_write_ln_P(PSTR("CLMK"), false);
                break;

            case _SYMBOL:
                oled_write_ln_P(PSTR("Symb"), false);
                break;

            case _NAVIGATION:
                oled_write_ln_P(PSTR("Nav"), false);
                break;

            case _LED:
                oled_write_P(PSTR("LED"), false);
                break;
        }
        oled_write_P(PSTR("-----"), false);
        oled_write_ln(read_keylog(), false);
    } else {
        oled_write_P(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
    }
    return true;
}
