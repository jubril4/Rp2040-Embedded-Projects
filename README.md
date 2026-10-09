# RP2040 Embedded Systems Projects

Embedded C and ARM Cortex-M0+ assembly projects for the Raspberry Pi Pico (RP2040), written for Microprocessors and Microcontroller System Design coursework at Capitol Technology University using the Pico C/C++ SDK.

| Project | What it does | Concepts |
|---|---|---|
| `motion-sensor-light/` | Turns an LED on for 10 seconds when a PIR motion sensor detects movement | GPIO input and output, pull down resistors, polling and debounce |
| `servo-latch-countdown/` | Button triggers a 5 second countdown, then opens or closes a servo driven latch; pressing again cancels | PWM servo control, state flags, button debouncing |
| `bme280-environmental-sensor/` | Communicates with a Bosch BME280 temperature, pressure, and humidity sensor over I2C, verifying the chip ID before reading registers | I2C bus, register reads and writes, device driver integration |
| `arm-assembly/` | Hello World and an LED blink counter written in Thumb assembly, configuring GPIO through the SIO, pads, and IO bank registers directly | ARM Thumb instructions, memory mapped I/O, delay loops |

## Building
Requires the [Pico SDK](https://github.com/raspberrypi/pico-sdk). From a project folder:

```bash
mkdir build && cd build
cmake .. && make
```
Copy the generated `.uf2` file to the Pico in BOOTSEL mode.

## Credits
`bme280.c` and its headers are the Bosch Sensortec BME280 driver (BSD 3 Clause license); the integration code in `Project1.c` is my own.
