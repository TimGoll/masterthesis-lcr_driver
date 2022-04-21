# LCR Meter Software

This is the software for my master thesis project: creating a LCR meter based measurement device that can be used to measure the capacity of DEs.

## Libraries

### SSD1306

A library that controls SSD1306 based OLED displays: https://github.com/TimGoll/stm32-ssd1306

### MCP4725



### CMSIS_DSP

A math and digital signal processing library created by ARM. The installation for this one is a bit more complicated as it comes with a precompiled file. Check out [this video](https://www.youtube.com/watch?v=vCcALaGNlyw) to see how to set up the library.

The files can be found in this repository: https://github.com/STMicroelectronics/STM32CubeH7

- `Drivers/CMSIS/DSP/Include/arm_math.h`: This file contains the defenitions of the functions, types etc
- `Drivers/CMSIS/DSP/Lib/GCC/libarm_cortexM7lfsp_math.a`: This is the precompiled source file; info on the selection [can be found here](https://github.com/STMicroelectronics/STM32CubeH7/blob/master/Drivers/CMSIS/DSP/Include/arm_math.h#L53-L58)

Docs: https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html
