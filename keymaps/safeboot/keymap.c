/* Diagnostic keymap: unambiguous "is the board alive?" test.
 *
 * - Bootmagic OFF: a stuck top-left key can't force the bootloader.
 * - OLED OFF: I2C is out of the boot path.
 * - Console ON: `qmk console` can see it.
 * - Forces all 9 RGB LEDs GREEN at boot.
 *
 * After flashing, UNPLUG/REPLUG (don't touch the reset button):
 *   All LEDs GREEN + console shows "Yampad" -> board is 100% alive.
 *   Still nothing                           -> genuine hardware/USB fault.
 */

#include QMK_KEYBOARD_H
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,   KC_P2,   KC_P3,
    KC_P0,   KC_P0,   KC_PDOT, KC_PENT
  ),
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(85, 255, 255);  // green = booted and running
    print("\n[safeboot] ALIVE: bootmagic+OLED disabled, RGB forced green.\n");
}
