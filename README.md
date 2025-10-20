## GC9A01A

This is a driver for single chip TFT LCD GC9A01A with 240RGBx240 resolution. This repository contais the sensor driver files to be included, or linked directly as a git submodule.

To clone the content of this module, use the command line:

```bash
git clone https://github.com/STMicroelectronics/ais328dq-pid/
```

Some examples of driver usage can be found [here]()

Call display::register_driver(&gc9a01a_driver) function to register the drive gc9a01a_driver whish implement the interface defined by display_driver_t structure.
