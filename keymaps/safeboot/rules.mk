# Diagnostic: rule out software-triggered DFU entry.
# Bootmagic off  -> a stuck top-left key can no longer force the bootloader.
# OLED off       -> takes the I2C bus out of the boot path entirely.
# Forces RGB green at boot as an unmistakable "I booted and stayed up" signal.
BOOTMAGIC_ENABLE = no
OLED_ENABLE      = no
ENCODER_ENABLE   = no
CONSOLE_ENABLE   = yes
RGBLIGHT_ENABLE  = yes
