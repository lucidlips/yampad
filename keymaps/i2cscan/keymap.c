/* Diagnostic keymap for the Yampad: I2C bus scanner.
 *
 * Flash this, then run `qmk console` (or open QMK Toolbox's console).
 * Every 3 seconds it probes I2C addresses 0x08..0x77 and reports which
 * (if any) acknowledge. A standard SSD1306/SH1106 OLED answers at 0x3C
 * (sometimes 0x3D).
 *
 *   ACK at 0x3C  -> panel is alive on the bus; problem is driver/config
 *   ACK at 0x3D  -> alive, but at the alternate address
 *   no devices   -> nothing is talking: dead panel, missing pull-ups,
 *                   wrong MCU pins, or a solder joint that fails under load
 */

#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
             KC_NO,   KC_PSLS, KC_PAST, KC_PMNS,
             KC_P7,   KC_P8,   KC_P9,
    KC_MPLY, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
             KC_P1,   KC_P2,   KC_P3,
             KC_P0,   KC_P0,   KC_PDOT, KC_PENT
  ),
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    i2c_init();
    print("\n[i2cscan] firmware up. Scanning I2C every 3s...\n");
}

void housekeeping_task_user(void) {
    static uint32_t last = 0;
    if (timer_elapsed32(last) < 3000) {
        return;
    }
    last = timer_read32();

    uint8_t found = 0;
    print("[i2cscan] scanning 0x08..0x77 ...\n");
    for (uint8_t addr = 0x08; addr < 0x78; addr++) {
        if (i2c_start((addr << 1) | I2C_WRITE, 50) == I2C_STATUS_SUCCESS) {
            uprintf("  ACK at 0x%02X\n", addr);
            found++;
        }
        i2c_stop();
    }
    if (found == 0) {
        print("  no devices responded\n");
    }
}
