#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QW 0
#define _L1 1
#define _L2 2
#define _L3 3
#define _L4 4

// Macro name shortcuts
#define QWERTY M(_QW)

// Curly braces have their own keys. These are defined to make them not mess up
// the grid in layer 2.
#define L_CURBR LSFT(KC_LBRC)
#define R_CURBR LSFT(KC_RBRC)
// all braces have their own keys
#define L_PRN LSFT(KC_9)
#define R_PRN LSFT(KC_0)

// Fillers to make layering more clear
#define _______ KC_TRNS

// tap dance macro
enum {
  PRN = 0,
  CURBR,
  BRC
};

qk_tap_dance_action_t tap_dance_actions[] = {
   [PRN] = ACTION_TAP_DANCE_DOUBLE(L_PRN, R_PRN),
   [CURBR] = ACTION_TAP_DANCE_DOUBLE(L_CURBR, R_CURBR),
   [BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
 };

// vertical has its own key
#define KC_VERT LSFT(KC_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = KEYMAP( /* Qwerty */
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MO(_L1),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_GRV),
    MO(_L2), KC_LGUI, KC_ESC,                   KC_ENT,  KC_SPC,                    KC_RALT, MO(_L4),  TG(_L3)
  ),
  [_L1] = KEYMAP( /* LAYER 1 */
    KC_QUOT, KC_EXLM , KC_AT,  KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL, KC_DEL,
    _______, KC_1    , KC_2 ,  KC_3   , KC_4  ,  KC_5   , KC_6   , KC_7   , KC_8   ,   KC_9 , KC_0  , _______,
    _______, TD(PRN) , TD(CURBR), TD(BRC) , _______, _______, _______, KC_VERT, KC_BSLS, _______, _______, _______,
    _______, _______ , _______,                   _______, _______,                   _______, _______, _______
  ),
  [_L2] = KEYMAP( /* LAYER 2 */
    _______, KC_1   ,  KC_2  ,  KC_3  , KC_4   , KC_5   , KC_6   , KC_7 ,    KC_8,    KC_9,    KC_0,  _______,
    _______, KC_SLSH, KC_ASTR, KC_MINS, KC_PLUS, L_PRN, R_PRN, KC_4,    KC_5,    KC_6,    _______, KC_ENT,
    _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    _______, _______,
    _______, _______, _______,                   _______, _______,                   _______, _______, _______
  ),
  
  [_L3] = KEYMAP( /* LAYER 3 */
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,
    KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
    KC_LCTL, KC_LSFT, KC_B,                      KC_SPC,  KC_C,                      _______, _______, _______
  ),
  [_L4] = KEYMAP( /* LAYER 4 */
    _______, _______, KC_UP  , _______, _______, _______, _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   _______,
    KC_ESC,  KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, KC_F5,  KC_F6,   KC_F7,   KC_F8,   _______,
    KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    _______, KC_LSFT, KC_B,                      KC_SPC,  RESET,                     _______, _______, _______
  )
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {        
      }
    return MACRO_NONE;
};
