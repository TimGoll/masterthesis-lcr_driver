#include "AnaRP.h"

AnaRP_t *__ADCList[3]; // 3 ADCs available
uint8_t __ADCListSize = 0;

uint32_t buffer_2[ADC_FFT_SIZE];

void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc) {
	dev->hadc = hadc;
	dev->size = ADC_FFT_SIZE;
	dev->filled_buffer = 0;
	dev->next_processing = HAL_GetTick() + 1000 / ADC_PROCESS_FREQ;

	HAL_ADC_Start_DMA(hadc, (uint32_t *) dev->buffer[0], dev->size);

	//HAL_ADC_Start_DMA(dev->hadc, buffer_2, dev->size);

	// add ADC to list of ADCs
	__ADCList[__ADCListSize] = dev;

	__ADCListSize++;
}

void AnaRP_ProcessData(AnaRP_t *dev) {
	if (!dev->process_data_flag) {
		return;
	}

	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

	// According to application note AN4841 floating point DSP is faster than integer based
	// DSP on M4 and M7 based MCUs. Therefore we're using a floating point based DSP here.
	// If the MCU is changed at some point in the future, this might has to be changed.

	// docs: https://www.keil.com/pack/doc/CMSIS/DSP/html/group__RealFFT.html

	// first the data is converted from int to float
	for (uint16_t i = 0; i < dev->size; i++) {
		// copy the currently selected buffer and move the data to the FFT in array
		dev->fft_in[i] = (float32_t) dev->buffer[dev->filled_buffer][i];
	}

	// now the FFT is initialized
	arm_rfft_fast_init_f32(&dev->fft_inst, ADC_FFT_SIZE);

	// perform forward direction 32-bit FFT
	arm_rfft_fast_f32(&dev->fft_inst, dev->fft_in, dev->fft_out, 0); // 0: RFFT, 1: RIFFT

	// calculate magnitude (buffer size is half because real + imag parts are merged)
	arm_cmplx_mag_f32(dev->fft_out, dev->fft_mag, ADC_FFT_SIZE / 2);

	arm_max_f32(dev->fft_mag, ADC_FFT_SIZE / 2, &dev->fft_max_amp, &dev->fft_max_amp_idx);

	// set the flag that the processing is done
	dev->process_data_flag = 0;

	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
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
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

	// try to find the ADC struct reference
	AnaRP_t *dev;

	if (!__AnaRP_FindADC(hadc, &dev)) {
		return;
	}

	// check the time, if enough has passed, the buffers have to be changed and a new calculation is triggered
	if (HAL_GetTick() < dev->next_processing) {
		return;
	}

	// if data is still not finished processing, it should be skipped as well
	if (dev->process_data_flag) {
		return;
	}

	// set the next processing time
	dev->next_processing = HAL_GetTick() + 1000 / ADC_PROCESS_FREQ;

	// switch buffers
	//HAL_ADC_Start_DMA(dev->hadc, (uint32_t *) dev->buffer[dev->filled_buffer], dev->size);

	//HAL_ADC_Start_DMA(dev->hadc, buffer_2, dev->size);

	dev->filled_buffer = !dev->filled_buffer; // switch between 0 and 1

	// set flag to process data
	dev->process_data_flag = 1;
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {

}
