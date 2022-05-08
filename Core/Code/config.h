#pragma once

#define VERSION "v0.9"

#define CONF_PI 3.14159265358979323846f

// ANALOG OUT
#define DAC_SAMPLE_FREQ 1000000 // STM H7 has 1MSample/s

#define DAC_RESISTANCE_LOWER_LIMIT 0 // mOhm
#define DAC_RESISTANCE_UPPER_LIMIT 50000000 // mOhm = 50kOhm´

#define DAC_I2C_ADDRESS_RESISTANCE 0x62

// ANALOG IN PROCESSING
#define ADC_SAMPLE_FREQ 1280000 // this is the resulting frequency, hardware oversampling is ignored
#define ADC_PROCESS_FREQ 100 // process the data 100 times per second
#define ADC_SAMPLE_SIZE 256
#define ADC_UAMPS_PER_VOLT 100.05993264732983f

// DE ESTIMATION MODELS
#define DEESTIMATION_MODEL_COUNT 3

// DISPLAY
#define DISPLAY_I2C_ADDRESS 0x3C

