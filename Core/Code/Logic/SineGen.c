#include "SineGen.h"

void SineGen_Initialize(SineGen_t *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac, uint32_t dac_channel) {
	dev->hdac = hdac;
	dev->dac_channel = dac_channel;

	HAL_TIM_Base_Start(tmr);
}

void SineGen_SetupSine(SineGen_t *dev, uint16_t min, uint16_t max, uint16_t frequency) {
	uint16_t sample_count = SAMPLE_FREQ / frequency;

	// in the first step, the existing buffer should be freed in case the sample size has changed
	// if no buffer was created so far, nothing will happen here
	free(dev->buffer);

	// then a new buffer is created with the appropriate size for the calculated sample size
	dev->buffer = (uint16_t *) malloc(sample_count * sizeof(uint16_t));

	// store the buffer size as well
	dev->buffer_size = sample_count;

	for (uint16_t i = 0; i < sample_count; i++) {
		dev->buffer[i] = (sin(i * 2 * SINEGEN_PI / sample_count) + 1) * ((max - min) / 2) + min;
	}
}

void SineGen_OutputSine(SineGen_t *dev) {
	HAL_DAC_Start_DMA(dev->hdac, dev->dac_channel, (uint32_t *) dev->buffer, dev->buffer_size, DAC_ALIGN_12B_R);
}

// CALLBACKS

void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac) {

}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac) {

}
