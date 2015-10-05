## MicroPython on Altera De0 Nano SoC Bare-metal

This is a port of micropython for the Altera De0 Nano SoC board. This port runs on bare-metal, without the support of the on-board Linux OS.

### Build process

To build this port, you need Altera's SoC EDS. I'm using version 15.0.

Open "Altera Embedded Command Shell" in this directory and type `make`.

Then, in the `build` directory you can find two files: `firmware.elf` and `firmware.raw`. We need to load `firmware.raw` on bare-metal.

Copy `firmware.raw` to the FAT partition of the SD card.

Connect the USB serial port and power on the board. Normally the board would boot into Linux, but we need to stop it. In the booting process you would see the instruction like "Hit any key to stop autoboot:  5".

By stopping the booting process, you would enter a command prompt of u-boot which looks like this:

```
SOCFPGA_CYCLONE5 #
```

In the prompt, type

```
fatls mmc 0:1
```

and you should see the file `firmware.raw` you just copied.

Then type

```
fatload mmc 0:1 0x00100040 firmware.raw
```

and then

```
go 0x00100040
```

and MicroPython starts running!
