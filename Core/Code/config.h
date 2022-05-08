#pragma once

#define VERSION "v0.9"

#define CONF_PI 3.14159265358979323846f

// ANALOG OUT
#define DAC_SAMPLE_FREQ 1000000 // STM H7 has 1MSample/s

// ANALOG IN PROCESSING
#define ADC_SAMPLE_FREQ 1280000 // this is the resulting frequency, hardware oversampling is ignored
#define ADC_PROCESS_FREQ 100 // process the data 100 times per second
#define ADC_SAMPLE_SIZE 256
#define ADC_UAMPS_PER_VOLT 91 //TODO refine

#define DEESTIMATION_MODEL_COUNT 3
