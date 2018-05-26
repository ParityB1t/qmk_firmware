#include "clueboard.h"

// Helpful defines
#define GRAVE_MODS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define _______ KC_TRNS
#define xxxxxxx KC_NO

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0 // BASE Layer
#define _FL 1 // Function Layer
#define _ME 2 // Media Layer
#define _CL 3 // Control Layer

#define TO_BASE TO(_BL)
#define MO_FUNC MO(_FL)
#define   MEDIA MO(_ME)
#define  MO_CTL MO(_CL)
#define ESC_FUN LT(_FL, KC_ESC)

#define ESC_GRV F(0)
#define RGB_RST F(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer) */
  [_BL] = KEYMAP(
    ESC_GRV,    KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0, KC_MINS,   KC_EQL, _______, KC_BSPC,          KC_INS,  \
    KC_TAB,    KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_LBRC,  KC_RBRC, KC_BSLS,                   KC_DEL,  \
    KC_LCTL,    KC_A,    KC_S,   KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,  KC_NUHS,  KC_ENT,                            \
    KC_LSFT, KC_NUBS,    KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT, KC_SLSH,  _______, KC_LALT,          KC_UP,            \
    KC_LCTL, _______, KC_LALT,_______,                    KC_SPC, KC_SPC,                    _______, KC_RALT,  _______, MO_FUNC, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer */
  [_FL] = KEYMAP(
     KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12, _______, _______,          BL_STEP, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   _______, \
    _______, _______,  MO_CTL, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______,   MEDIA, _______,  _______, _______,  _______, _______,          KC_PGUP,          \
    _______, _______, _______, _______,                   _______, _______,                    _______, _______,  _______, MO_FUNC, KC_HOME, KC_PGDN, KC_END),

  /* Keymap _ME: Media layer */
  [_ME] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, KC_MUTE,          KC_VOLU, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   KC_VOLD, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______,   MEDIA, _______,  _______, _______,  _______, _______,          _______,          \
    _______, _______, _______, _______,                   _______, _______,                    _______, _______,  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT),

  /* Keymap _CL: Control layer */
  [_CL] = KEYMAP(
    _______, RGB_RST, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, RGB_TOG,          RGB_VAI, \
    _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                   RGB_VAD, \
    _______, _______,  MO_CTL, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,                            \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______,          RGB_SAI,          \
    _______, _______, _______, _______,                   RGB_MOD, RGB_MOD,                    _______, _______,  _______, _______, RGB_HUD, RGB_SAD, RGB_HUI),

};

/* This is a list of user defined functions. F(N) corresponds to item N
   of this list.
 */
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(0),  // Calls action_function()
  [1] = ACTION_FUNCTION(1),  // Calls action_function()
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t mods_pressed;
  static bool mod_flag;

  switch (id) {
    case 0:
      /* Handle the combined Grave/Esc key
       */
      mods_pressed = get_mods()&GRAVE_MODS; // Check to see what mods are pressed

      if (record->event.pressed) {
        /* The key is being pressed.
         */
        if (mods_pressed) {
          mod_flag = true;
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        /* The key is being released.
         */
        if (mod_flag) {
          mod_flag = false;
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    case 1:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(206, 255, 255);
      }
  }
}

enum layer_id {
  LAYER_BASE,
  LAYER_FUNCTION,
  LAYER_MEDIA,
  LAYER_CONTROL,
};

void clueboard_set_led(uint8_t id, uint8_t val) {
  switch (id) {
    case LAYER_BASE:
      rgblight_sethsv_noeeprom(0, 0, val);
      break;
    case LAYER_FUNCTION:
      rgblight_sethsv_noeeprom(46, 255, val);
      break;
    case LAYER_MEDIA:
      rgblight_sethsv_noeeprom(86, 255, val);
      break;
    case LAYER_CONTROL:
      rgblight_sethsv_noeeprom(346, 255, val);
      break;
  }
};

void matrix_scan_user(void) {
    rgblight_config_t rgblight_config;
    rgblight_config.raw = eeconfig_read_rgblight();

    if (!rgblight_config.enable || rgblight_config.mode != 1) { return; }

    uint32_t layer = layer_state;
    uint8_t val = rgblight_config.val;

    if (layer & (1<<_FL)) {
      if (layer & (1<<_ME)) {
        clueboard_set_led(LAYER_MEDIA, val);
      } else if (layer & (1<<_CL)) {
        clueboard_set_led(LAYER_CONTROL, val);
      } else {
        clueboard_set_led(LAYER_FUNCTION, val);
      }
    } else {
        clueboard_set_led(LAYER_BASE, val);
    }
};
