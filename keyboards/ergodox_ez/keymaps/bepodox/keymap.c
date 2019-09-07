// An Ergodox EZ keymap meant to be used with a bépo layout (FR ergonomic
// layout, dvorak style). The overall design is slightly inspired by the
// TypeMatrix keyboard. Switching between a TypeMatrix and an Ergodox with this
// layout should be relatively easy.
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

// The layers that we are defining for this keyboards.
#define BASE 0 // default layer
#define FN 1 // fn layer
#define NUMS 2 // numeric layer
#define DEV 3 // development layer

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
#define TAP_MACRO 0

#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

// custom keycodes
enum {
  // SAFE_RANGE must be used to tag the first element of the enum.
  // DYNAMIC_MACRO_RANGE must always be the last element of the enum if other
  // values are added (as its value is used to create a couple of other keycodes
  // after it).
  DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

// This file must be included after DYNAMIC_MACRO_RANGE is defined...
#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Escape |   "  |   «  |   »  |   (  |   )  |  $   |           |  %   |   @  |   +  |   -  |   /  |   *  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |   W    |   B  |   É  |   P  |   O  |   È  | BkSp |           | Tab  |   ^  |   V  |   D  |   L  |   J  |   Ç    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |   Z    |   A  |   S  |   D  |   F  |   G  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
     * |--------+------+------+------+------+------| Enter|           |Suppr |------+------+------+------+------+--------|
     * |  Ctrl  |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  | Ctrl   |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |home  |pgUp  |pgDown| end  |TMP L2|                                       |TMP L2| Left |  Up  | Down | Right |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |TMP L1| Alt  |       | L2   | TMP L1|
     *                                 ,------|------|------|       |------+--------+------.
     *                                 |      |      |ctAlt |       |CtAlt |        |      |
     *                                 | Space|LShift|------|       |------| RShift | AltGr|
     *                                 |      |      |LGUI  |       |LGUI  |        |      |
     *                                 `--------------------'       `----------------------'
     */
    // If it accepts an argument (i.e, is a function), it doesn't need KC_.
    // Otherwise, it needs KC_*
    [BASE] = LAYOUT_ergodox(  // layer 0 : default
            // left hand
            KC_ESC,         BP_DQOT,      BP_LGIL,BP_RGIL,BP_LPRN,BP_RPRN,BP_DLR,
            BP_W,           BP_B,         BP_ECUT,BP_P,   BP_O,   BP_EGRV,KC_BSPC,
            BP_Z,           BP_A,         BP_U,   BP_I,   BP_E,   BP_COMM,
            KC_LCTL,        BP_AGRV,      BP_Y,   BP_X,   BP_DOT, BP_K,   KC_ENT,
            KC_HOME,        KC_PGUP,      KC_PGDN,KC_END, MO(NUMS),
            MO(FN),  KC_LALT,
            LCTL(KC_LALT),
            KC_SPC, KC_LSFT, KC_LGUI,
            // right hand
            BP_PERC,     BP_AT,  BP_PLUS,BP_MINS,BP_SLSH,BP_ASTR,BP_EQL,
            KC_TAB,      BP_DCRC,BP_V,   BP_D,   BP_L,   BP_J,   BP_CCED,
                         BP_C,   BP_T,   BP_S,   BP_R,   BP_N,   BP_M,
            KC_DEL,      BP_APOS,BP_Q,   BP_G,   BP_H,   BP_F,   KC_RCTL,
                                  MO(DEV),KC_LEFT, KC_UP, KC_DOWN,KC_RIGHT,
            TG(NUMS),     MO(FN),
            LCTL(KC_LALT),
            KC_LGUI, KC_RSFT, KC_RALT
            ),
    /* Keymap 1: Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Power  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           | Caps |      |      |      |      |      |Impr Écr|
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Sleep  |  F7  |  F8  |  F9  | F10  |  F11 | F12  |           |      |      | home |  up  | end  |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Wake   |  RW  | Play | FW   | STOP |      |------|           |------|      | left | down | right|      |        |
     * |--------+------+------+------+------+------|      |           | Ins  |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |RESET | VolDn|VolUp | Mute |      |                                       |      | Home | pgup | pgdn | End   |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      | BRWS |
     *                                 |      |      |      |       |      |      | BACK |
     *                                 `--------------------'       `--------------------'
     */
    // Space Fn layer
    [FN] = LAYOUT_ergodox(
            // left hand
            KC_PWR ,KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,  KC_F6,
            KC_SLEP,KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11, KC_F12,
            KC_WAKE,KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_MSTP,   ___,
            ___,___,   ___,   ___,   ___,   ___,___,
            RESET,  KC_VOLD,   KC_VOLU,   KC_MUTE,   ___,
            ___,___,
            ___,
            ___,___,___,
            // right hand
            KC_CAPS, ___, ___,___, ___, ___, KC_PSCR,
            ___, ___, KC_HOME,KC_UP,   KC_END,  ___, ___,
                     ___, KC_LEFT,KC_DOWN, KC_RIGHT,___, ___,
            KC_INS, ___,  ___,___, ___, ___, ___,
                              ___,KC_HOME, KC_PGUP, KC_PGDN, KC_END,
            ___, ___,
            ___,
            ___, ___, KC_WBAK
            ),
    /* Keymap 2: Numeric Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |N.LOCK|  +   |  -   |  /   |  *   |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |  7   |  8   |  9   |  :   |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------|--------|
     * |        |      |      |      |      |      |------|           |------|      |  4   |  5   |  6   |  ,   |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        | undo | save | paste| copy | cut  |      |           |      |   0  |  1   |  2   |  3   |  .   |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // numeric layer
    [NUMS] = LAYOUT_ergodox(
            // left hand
            ___,___,   ___,   ___,   ___,   ___,   ___,
            ___, ___,   ___,   ___,   ___,   ___,    ___,
            ___, ___,   ___,   ___,   ___,   ___,
            ___,LCTL(BP_Z),LCTL(BP_S),MK_PASTE,MK_COPY,MK_CUT,   ___,
            ___,___,   ___,   ___,   ___,
            ___,___,
            ___,
            ___,___,___,
            // right hand
            ___, KC_NLCK, KC_PPLS,KC_PMNS, KC_PSLS, KC_PAST, ___,
            ___, ___,     KC_P7,    KC_P8,   KC_P9, BP_COLN, ___,
                 ___,     KC_P4,    KC_P5,   KC_P6, BP_COMM, ___,
            ___, KC_P0,   KC_P1,    KC_P2,   KC_P3, KC_PDOT, ___,
                ___, ___, KC_P0,   ___, ___,
            ___, ___,
            ___,
            ___, ___, ___
            ),
    /* Keymap 3: Development Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   (  |   )  |  <   |   >  |  *   |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------|--------|
     * |    "   |   {  |   }  |  [   |   ]  |  =   |------|           |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   %  |   #  |  $   |   `  |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // numeric layer
    [DEV] = LAYOUT_ergodox(
            // left hand
                ___,     ___,     ___,     ___,     ___, ___, ___,
                ___, BP_LPRN, BP_RPRN, BP_LESS, BP_GRTR, BP_ASTR,  ___,
            BP_DQOT, BP_LCBR, BP_RCBR, BP_LBRC, BP_RBRC, BP_EQL,
                ___, BP_PERC, BP_HASH, BP_DLR,  BP_GRV,  ___, ___,
                ___, ___,         ___,    ___,     ___,
            ___,___,
            ___,
            ___,___,___,
            // right hand
            ___, ___, ___, ___, ___, ___, ___,
            ___, ___, ___,  ___,   ___,   ___, ___,
                     ___, ___,  ___,   ___,   ___, ___,
            ___, ___,   ___,  ___,   ___,   ___, ___,
                     ___, ___,___,   ___, ___,
            ___, ___,
            ___,
            ___, ___, ___
            ),
};

// Whether the macro 1 is currently being recorded.
static bool is_macro1_recording = false;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static uint32_t current_layer_state = 0;
uint32_t layer_state_set_user(uint32_t state);

// Method called at the end of the tap dance on the TAP_MACRO key. That key is
// used to start recording a macro (double tap or more), to stop recording (any
// number of tap), or to play the recorded macro (1 tap).
void macro_tapdance_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DYN_REC_STOP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DYN_MACRO_PLAY1;
  } else {
    keycode = DYN_REC_START1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_record_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_record_dynamic_macro(keycode, &record);
}

// The definition of the tap dance actions:
qk_tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
};

// Runs for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode != TD(TAP_MACRO)) {
    // That key is processed by the macro_tapdance_fn. Not ignoring it here is
    // mostly a no-op except that it is recorded in the macros (and uses space).
    // We can't just return false when the key is a tap dance, because
    // process_record_user, is called before the tap dance processing (and
    // returning false would eat the tap dance).
    if (!process_record_dynamic_macro(keycode, record)) {
      return false;
    }
  }

  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

