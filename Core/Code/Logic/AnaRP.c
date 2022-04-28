#include "AnaRP.h"

AnaRP_t *__ADCList[3]; // 3 ADCs available on MCU
uint8_t __ADCListSize = 0;

void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc) {
	dev->hadc = hadc;
	dev->size = ADC_FFT_SIZE;
	dev->next_measurement = HAL_GetTick() + 1000 / ADC_PROCESS_FREQ;
	dev->process_data_flag = 0;

	// add ADC to list of ADCs
	__ADCList[__ADCListSize] = dev;

	__ADCListSize++;

	// According to application note AN4841 floating point DSP is faster than integer based
	// DSP on M4 and M7 based MCUs. Therefore we're using a floating point based DSP here.
	// If the MCU is changed at some point in the future, this might have to be changed.

	// docs: https://www.keil.com/pack/doc/CMSIS/DSP/html/group__RealFFT.html

	// initialize the FFT instance
	arm_rfft_fast_init_f32(&dev->fft_inst, ADC_FFT_SIZE);
}

void AnaRP_StartDMA(AnaRP_t *dev) {
	// The data is sampled at a rate of 2MHz. This means there are 200 samples per
	// sine if the sine has a frequency of 10kHz. However a 4x hardware oversampling
	// is used here which results in an effective sampling rate of 50kHz. This increases
	// the signal to noise ratio.
	HAL_ADC_Start_DMA(dev->hadc, (uint32_t *) dev->buffer, dev->size);
}

void AnaRP_ProcessData(AnaRP_t *dev) {
	if (!dev->process_data_flag) {
		return;
	}

	// first the data is converted from int to float
	for (uint16_t i = 0; i < dev->size; i++) {
		// copy the currently selected buffer and move the data to the FFT in array
		uint16_t tmp_buffer = dev->buffer[i];

		dev->fft_data.fft_in[i] = (float32_t) tmp_buffer;
	}

	// perform forward direction 32-bit FFT
	// note: this function modifies the content of the input array
	arm_rfft_fast_f32(&dev->fft_inst, dev->fft_data.fft_in, dev->fft_data.fft_out, 0); // 0: RFFT, 1: RIFFT

	// calculate magnitude (buffer size is half because real + imag parts are merged)
	arm_cmplx_mag_f32(dev->fft_data.fft_out, dev->fft_data.fft_mag, ADC_FFT_SIZE / 2);

	// calculate the magnitude (squared real and imaginary); first entry is ignored because it is the DC offset
	arm_max_f32(&(dev->fft_data.fft_mag[1]), ADC_FFT_SIZE / 2 - 1, &dev->fft_results.magnitude, &dev->fft_data.fft_max_mag_idx);

	// the DC offset, normed to one sample
	dev->fft_results.dc_offset = dev->fft_data.fft_out[0] / ADC_FFT_SIZE;

	// the magnitude has to be normed as well
	dev->fft_results.magnitude /= ADC_FFT_SIZE;

	// atan2(Imag, Real)
	dev->fft_results.phase = atan2f(dev->fft_data.fft_out[2 * dev->fft_data.fft_max_mag_idx + 1], dev->fft_data.fft_out[2 * dev->fft_data.fft_max_mag_idx]);

	// the frequency is calculated by the sample index and a constant factor
	dev->fft_results.frequency = ADC_SAMPLE_FREQ / ADC_FFT_SIZE * (dev->fft_data.fft_max_mag_idx + 1);

	// set the flag that the processing is done
	dev->process_data_flag = 0;
}

uint8_t AnaRP_IsReady(AnaRP_t *dev) {
	// check the time, if enough has passed, the buffers have to
	// be changed and a new calculation is triggered
	if (HAL_GetTick() < dev->next_measurement) {
		return 0;
	}

	// if data is still not finished processing, it should be skipped as well
	if (dev->process_data_flag) {
		return 0;
	}

	return 1;
}

uint8_t __AnaRP_FindADC(ADC_HandleTypeDef *hadc, AnaRP_t **adc) {
	for (uint8_t i = 0; i < __ADCListSize; i++) {
		if (__ADCList[i]->hadc->Instance == hadc->Instance) {
			*adc = __ADCList[i];

			return 1;
		}
	}

	return 0;
}

// CALLBACKS

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13); //TODO

	// try to find the ADC struct reference
	AnaRP_t *dev;

	if (!__AnaRP_FindADC(hadc, &dev)) {
		return;
	}

	// set the next processing time
	dev->next_measurement = HAL_GetTick() + 1000 / ADC_PROCESS_FREQ;

	// set flag to process data
	dev->process_data_flag = 1;
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {

}
