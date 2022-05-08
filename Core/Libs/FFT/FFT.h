#pragma once

#include <math.h>
#include <stdlib.h>

#define ARM_MATH_CM7 // cortex m7 based MCU

#include "../CMSIS_DSP/arm_math.h"

typedef struct {
	float32_t *fft_in; ///< the input array for the FFT (converted ADC buffer)
	float32_t *fft_out; ///< the output of the FFT (complex numbers: real(0), imag(0), real(1), ...)
	float32_t *fft_mag; ///< the magnitude, only real numbers, therefore half the output size
	uint32_t fft_max_mag_idx; ///< the index of the biggest magnitude
} FFT_Data_t;

typedef struct {
	float32_t dc_offset;
	float32_t magnitude;
	float32_t phase;
	float32_t frequency;
} FFT_Results_t;

typedef struct {
	arm_rfft_fast_instance_f32 fft_inst; ///< The FFT instance

	uint16_t fft_size;
	uint32_t sample_freq;

	FFT_Data_t data;
	FFT_Results_t results;
} FFT_t;

void FFT_Initialize(FFT_t *dev, uint16_t fft_size, uint32_t sample_freq);

void FFT_Compute(FFT_t *dev, uint16_t *data);
