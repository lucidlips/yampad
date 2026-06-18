/* Diagnostic keymap: confirm the OLED actually renders at address 0x3C.
 *
 * The i2cscan keymap proved the panel ACKs at 0x3C, so the bus + panel are
 * healthy. This drives the SSD1306 driver and writes an unmistakable pattern.
 *
 *   Screen shows text  -> display fully works; the bug was OLED_DISPLAY_ADDRESS
 *                         0x3D in the daily config. Use 0x3C.
 *   Garbled / offset    -> panel is an SH1106, not SSD1306 (needs different driver).
 *   Still blank         -> init issue; check console log below.
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
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    print("[oledtest] oled_init_user called -> driver is initialising\n");
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("OLED\n"), false);
    oled_write_P(PSTR(" OK\n"), false);
    oled_write_P(PSTR("0x3C\n"), false);
    oled_write_P(PSTR("-----\n"), false);
    oled_write_P(PSTR("YAM\n"), false);
    oled_write_P(PSTR("PAD\n"), false);
    return false;
}
