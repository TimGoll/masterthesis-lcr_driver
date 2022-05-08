#include "AnaRP.h"

AnaRP_t *__ADCList[3]; // 3 ADCs available on MCU
uint8_t __ADCListSize = 0;

void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc) {
	dev->hadc = hadc;
	dev->size = ADC_SAMPLE_SIZE;
	dev->next_measurement = HAL_GetTick() + 1000 / ADC_PROCESS_FREQ;
	dev->process_data_flag = 0;

	// add ADC to list of ADCs
	__ADCList[__ADCListSize] = dev;

	__ADCListSize++;
}

void AnaRP_StartDMA(AnaRP_t *dev) {
	// The data is sampled at a rate of 2MHz. This means there are 200 samples per
	// sine if the sine has a frequency of 10kHz. However a 4x hardware oversampling
	// is used here which results in an effective sampling rate of 50kHz. This increases
	// the signal to noise ratio.
	HAL_ADC_Start_DMA(dev->hadc, (uint32_t *) dev->buffer, dev->size);
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

uint8_t AnaRP_FinishedReading(AnaRP_t *dev) {
	return dev->process_data_flag;
}

void AnaRP_ResetState(AnaRP_t *dev) {
	dev->process_data_flag = 0;
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
