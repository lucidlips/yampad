# Flashing the Yampad

## ⚡ The command (don't forget the `-bl dfu` flag!)

```bash
cd ~/qmk_firmware
qmk flash -kb yampad -km default -bl dfu
```

**The `-bl dfu` flag is REQUIRED.** This board's `info.json` says the bootloader
is `caterina`, but the actual controller uses the **Atmel DFU** bootloader. Without
`-bl dfu`, qmk tries the wrong flasher (avrdude / double-tap reset) and fails.

When it prints `Detecting USB port...`, **reset the board into bootloader mode** —
it will enumerate as an Atmel DFU device, then flashing proceeds automatically.

Requires `dfu-programmer` (installed: `brew install dfu-programmer`).

## Branches in this repo

| Branch  | Contents                                                            |
|---------|---------------------------------------------------------------------|
| `main`  | **Working config** — OLED `0x3D`, RGB defaults + boot init, `LICENSE` |
| `stock` | Pristine upstream qmk yampad (OLED defaults to `0x3C`) for diagnostics |

### Flash your working config
```bash
cd ~/qmk_firmware/keyboards/yampad && git checkout main
cd ~/qmk_firmware && qmk flash -kb yampad -km default -bl dfu
```

### Flash stock (e.g. to test the OLED)
```bash
cd ~/qmk_firmware/keyboards/yampad && git checkout stock
cd ~/qmk_firmware && qmk flash -kb yampad -km default -bl dfu
```

## OLED note

The OLED not working is most likely the address: your working config forces
`#define OLED_DISPLAY_ADDRESS 0x3D`, while most SSD1306 panels (and stock) use
`0x3C`. If the OLED works on the `stock` branch, change that line to `0x3C`
(or delete it) on `main`.

## Remotes

- `origin`   → `git@github.com:lucidlips/yampad.git`  (your backup repo)
- `upstream` → `https://github.com/Thats-so-Mo/YampadV2-Updated.git`  (original fork)
