#include "FFT.h"

void FFT_Initialize(FFT_t *dev, uint16_t fft_size, uint32_t sample_freq) {
	dev->fft_size = fft_size;
	dev->sample_freq = sample_freq;

	dev->data.fft_in = malloc(dev->fft_size * sizeof(float32_t));
	dev->data.fft_out = malloc(dev->fft_size * sizeof(float32_t));
	dev->data.fft_mag = malloc(dev->fft_size * sizeof(float32_t) / 2);

	// According to application note AN4841 floating point DSP is faster than integer based
	// DSP on M4 and M7 based MCUs. Therefore we're using a floating point based DSP here.
	// If the MCU is changed at some point in the future, this might have to be changed.

	// docs: https://www.keil.com/pack/doc/CMSIS/DSP/html/group__RealFFT.html

	// initialize the FFT instance
	arm_rfft_fast_init_f32(&dev->fft_inst, dev->fft_size);
}

void FFT_Compute(FFT_t *dev, uint16_t *data) {
	// first the data is converted from int to float
	for (uint16_t i = 0; i < dev->fft_size; i++) {
		// copy the currently selected buffer and move the data to the FFT in array
		uint16_t tmp_buffer = data[i];

		dev->data.fft_in[i] = (float32_t) tmp_buffer;
	}

	// perform forward direction 32-bit FFT
	// note: this function modifies the content of the input array
	arm_rfft_fast_f32(&dev->fft_inst, dev->data.fft_in, dev->data.fft_out, 0); // 0: RFFT, 1: RIFFT

	// calculate magnitude (buffer size is half because real + imag parts are merged)
	arm_cmplx_mag_f32(dev->data.fft_out, dev->data.fft_mag, dev->fft_size / 2);

	// calculate the magnitude (squared real and imaginary); first entry is ignored because it is the DC offset
	arm_max_f32(&(dev->data.fft_mag[1]), dev->fft_size / 2 - 1, &dev->results.magnitude, &dev->data.fft_max_mag_idx);

	// increase the index by 1 because we omitted the first magnitude value
	dev->data.fft_max_mag_idx++;

	// the DC offset, normed to one sample
	dev->results.dc_offset = dev->data.fft_out[0] / dev->fft_size;

	// the magnitude has to be normed as well
	dev->results.magnitude /= dev->fft_size;

	// atan2(Imag, Real)
	dev->results.phase = atan2f(dev->data.fft_out[2 * dev->data.fft_max_mag_idx + 1], dev->data.fft_out[2 * dev->data.fft_max_mag_idx]);

	// the frequency is calculated by the sample index and a constant factor
	dev->results.frequency = dev->sample_freq / dev->fft_size * (dev->data.fft_max_mag_idx);
}
