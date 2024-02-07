// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "info_config.h"
#include "default_keyboard.h"
#include "features/achordion.h"

enum layers {
  QBASE, // QWERTY Base Layer
  CBASE, // COLEMAK-DH Base Layer
  SYM,   // Symbol Layer
  NAV,   // Navigation Layer
  MOU,   // Mouse Layer
  ADJ,   // Adjust Layer
};

enum custom_keycodes {
  EXIT = SAFE_RANGE,
};

// Home row mods for QWERTY layer.
#define QHOME_A LT(SYM, KC_A)
#define QHOME_S LALT_T(KC_S)
#define QHOME_D LSFT_T(KC_D)
#define QHOME_F LCTL_T(KC_F)
#define QHOME_J RCTL_T(KC_J)
#define QHOME_K RSFT_T(KC_K)
#define QHOME_L LALT_T(KC_L)
#define QHOME_SC LT(SYM, KC_SCLN)
#define QHOME_Z LGUI_T(KC_Z)
#define QHOME_SL RGUI_T(KC_SLSH)
// Experimental: Home row mod for NAV layer.
#define QHOME_V LT(NAV, KC_V)

// Home row mods for COLEMAK-DH layer.
#define CHOME_A LT(SYM, KC_A)
#define CHOME_R LALT_T(KC_R)
#define CHOME_S LSFT_T(KC_S)
#define CHOME_T LCTL_T(KC_T)
#define CHOME_N RCTL_T(KC_N)
#define CHOME_E RSFT_T(KC_E)
#define CHOME_I LALT_T(KC_I)
#define CHOME_O LT(SYM, KC_O)
#define CHOME_Z LGUI_T(KC_Z)
#define CHOME_SL RGUI_T(KC_SLSH)
// Experimental: Home row mod for NAV layer.
#define CHOME_D LT(NAV, KC_D)

/*
    DF(layer) - switches the default layer. The default layer is the 
      always-active base layer that other layers stack on top of. See below for 
      more about the default layer. This might be used to switch from QWERTY to 
      Dvorak layout. (Note that this is a temporary switch that only persists 
      until the keyboard loses power. To modify the default layer in a 
      persistent way requires deeper customization, such as calling the 
      set_single_persistent_default_layer function inside of 
      process_record_user.)

    MO(layer) - momentarily activates layer. As soon as you let go of the key, 
      the layer is deactivated.

    LM(layer, mod) - Momentarily activates layer (like MO), but with modifier(s)
      mod active. Only supports layers 0-15. The modifiers this keycode accept 
      are prefixed with MOD_, not KC_. These modifiers can be combined using 
      bitwise OR, e.g. LM(_RAISE, MOD_LCTL | MOD_LALT).

    LT(layer, kc) - momentarily activates layer when held, and sends kc when 
      tapped. Only supports layers 0-15.

    OSL(layer) - momentarily activates layer until the next key is pressed. 
      See One Shot Keys for details and additional functionality.

    TG(layer) - toggles layer, activating it if it's inactive and vice versa

    TO(layer) - activates layer and de-activates all other layers (except your 
      default layer). This function is special, because instead of just 
      adding/removing one layer to your active layer stack, it will completely 
      replace your current active layers, uniquely allowing you to replace 
      higher layers with a lower one. This is activated on keydown (as soon as 
      the key is pressed).

    TT(layer) - Layer Tap-Toggle. If you hold the key down, layer is activated, 
      and then is de-activated when you let go (like MO). If you repeatedly tap 
      it, the layer will be toggled on or off (like TG). It needs 5 taps by 
      default, but you can change this by defining TAPPING_TOGGLE -- for 
      example, #define TAPPING_TOGGLE 2 to toggle on just two taps.
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QBASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, QHOME_A, QHOME_S, QHOME_D, QHOME_F, KC_G,                               KC_H,    QHOME_J, QHOME_K, QHOME_L, QHOME_SC,KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, QHOME_Z, KC_X,    KC_C,    QHOME_V, KC_B,    KC_SLSH,          KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  QHOME_SL,KC_RGUI,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_ESC,  KC_ENT,                    KC_SPC,  KC_BSPC, KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [CBASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, CHOME_A, CHOME_R, CHOME_S, CHOME_T, KC_G,                               KC_M,    CHOME_N, CHOME_E, CHOME_I, CHOME_O, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, CHOME_Z, KC_X,    KC_C,    CHOME_D, KC_V,    KC_SLSH,          KC_BSLS, KC_K,    KC_H,    KC_COMM, KC_DOT,  CHOME_SL,KC_RGUI,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, KC_ESC,  KC_ENT,                    KC_SPC,  KC_BSPC, KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_GRV,  KC_LABK, KC_RABK, KC_AT,   KC_DOT,                             KC_AMPR, KC_BSLS, KC_LBRC, KC_RBRC, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_PLUS, KC_MINS, KC_EQL,  KC_UNDS,                            KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC, TO(ADJ),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_CIRC, KC_ASTR, KC_HASH, _______, _______,          _______, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______,  _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_LSFT, KC_LCTL, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [MOU] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_MOD, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                            KC_EQL,  KC_HOME, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_END,  RGB_HUD, RGB_SAD, RGB_VAD, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [ADJ] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     EXIT,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXIT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     EXIT,    XXXXXXX, XXXXXXX, XXXXXXX, DF(QBASE),DF(CBASE),                      DF(CBASE),DF(QBASE), XXXXXXX, XXXXXXX, XXXXXXX, EXIT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     EXIT,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXIT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    // Increase the tapping term a little for slower ring and pinky fingers.
    case CHOME_A:
    case CHOME_R:
    case CHOME_I:
    case CHOME_O:
    // case QHOME_A: // Same as `CHOME_A`
    case QHOME_S:
    case QHOME_L:
    case QHOME_SC:
      return TAPPING_TERM + 15;

    default:
      return TAPPING_TERM;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case CHOME_N:
    case CHOME_E:
    case CHOME_I:
    // Repeating is useful for Vim navigation keys.
    case QHOME_J:
    case QHOME_K:
    case QHOME_L:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

///////////////////////////////////////////////////////////////////////////////
#define ACHORDION_STREAK
uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode){
   if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
      return 0; // Disable streak detection on layer-tap keys.
   }

   // Otherwise, tap_hold_keycode is a mod-tap key.
   uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
   if ((mod & MOD_LSFT) != 0) {
      return 0;  // Disable for Shift mod-tap keys.
   } else {
      return 100;
   }
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  return 800;  // Use a timeout of 800 ms.
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand in Magic Sturdy.
  //   switch (tap_hold_keycode) {
  //     case HOME_X:  // X + D and X + G.
  //       if (other_keycode == HOME_D || other_keycode == KC_G) {
  //         return true;
  //       }
  //       break;
  //   }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) {
    return true;
  }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

///////////////////////////////////////////////////////////////////////////////

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }
  switch (keycode) {
    case EXIT:
      if (record->event.pressed) {
         layer_and(((layer_state_t)1 << CBASE) | ((layer_state_t)1 << QBASE));
         return false;
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  achordion_task();
//   orbital_mouse_task();
//   select_word_task();
//   sentence_case_task();
}
