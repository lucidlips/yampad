/* Yampad "cat" keymap: Bongo Cat playing the bongos on the OLED.
 *
 * Idle  = tail swishes. Type = paws slap the bongo drums (alternating),
 * driven directly by keypresses so it always reacts. Rotary encoder = volume.
 *
 * NOTE: Bongo Cat is a horizontal 128x32 animation and this screen is mounted
 * vertically, so the cat renders sideways. View the pad turned 90 degrees.
 * (Frame art: j-inc / community, via lily58_bongocat; bongos added.)
 */

#include QMK_KEYBOARD_H
#include "bongoframes.h"

#define TAP_HOLD_MS         350   // keep "playing" this long after a keypress
#define ANIM_FRAME_DURATION 130   // ms per frame

enum layers { _BL, _NV, _FN };
enum custom_keycodes { KC_DBL0 = SAFE_RANGE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
             TG(_NV),  KC_PSLS,  KC_PAST,   LT(_FN, KC_PMNS),
             KC_P7,    KC_P8,    KC_P9,
    KC_MPLY, KC_P4,    KC_P5,    KC_P6,     KC_PPLS,
             KC_P1,    KC_P2,    KC_P3,
             KC_DBL0,  KC_P0,    KC_PDOT,   KC_PENT
  ),
  [_NV] = LAYOUT(
             KC_INS,   KC_HOME,  KC_PGUP,   TG(_NV),
             KC_DEL,   KC_END,   KC_PGDN,
    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
             XXXXXXX,  KC_UP,    XXXXXXX,
             KC_LEFT,  KC_DOWN,  KC_RGHT,   XXXXXXX
  ),
  [_FN] = LAYOUT(
             RGB_MOD,  RGB_M_P,  RGB_TOG,   _______,
             RGB_HUD,  RGB_HUI,  XXXXXXX,
    XXXXXXX, RGB_SAD,  RGB_SAI,  XXXXXXX,   XXXXXXX,
             RGB_VAD,  RGB_VAI,  XXXXXXX,
             QK_BOOT,  XXXXXXX,  XXXXXXX,   XXXXXXX
  ),
};

static uint32_t last_key = 0;

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(191, 255, 255);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_key = timer_read32();
    }
    switch (keycode) {
        case KC_DBL0:
            if (record->event.pressed) SEND_STRING("00");
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code_delay(KC_VOLU, 10);
    } else {
        tap_code_delay(KC_VOLD, 10);
    }
    return true;
}
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    static uint32_t anim_timer = 0;
    static uint8_t  idle_frame = 0;
    static uint8_t  tap_frame  = 0;

    if (timer_elapsed32(anim_timer) < ANIM_FRAME_DURATION) {
        return false;
    }
    anim_timer = timer_read32();

    if (timer_elapsed32(last_key) < TAP_HOLD_MS) {
        // typing: alternate paws slapping the drums
        tap_frame = (tap_frame + 1) % TAP_FRAMES;
        oled_write_raw_P(tap[tap_frame], ANIM_SIZE);
    } else {
        // idle: tail swish
        idle_frame = (idle_frame + 1) % IDLE_FRAMES;
        oled_write_raw_P(idle[idle_frame], ANIM_SIZE);
    }
    return false;
}

#endif
