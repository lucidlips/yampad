# Diagnostic keymap: scans the I2C bus for the OLED and prints over USB console.
CONSOLE_ENABLE = yes          # so `qmk console` shows the scan results
OLED_ENABLE    = no           # take the OLED driver out of the picture
ENCODER_ENABLE = no
RGBLIGHT_ENABLE = yes         # leave RGB on as a "firmware is alive" indicator
QUANTUM_LIB_SRC += i2c_master.c   # force-link the I2C driver even with OLED off
