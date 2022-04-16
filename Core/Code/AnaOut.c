#include "AnaOut.h"

// define struct for analog output
AnaOut_t anaOut;

void Display_StartThread(void *argument) {
	AnaOut_Parameter_t *params = (AnaOut_Parameter_t *) argument;
}

void AnaOut_Initialize(AnaOut *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac) {
	dev->hdac = hdac;
	dev->size = ANAOUT_BUFFER_SIZE;

	__AnaOut_SetupSine(dev->buffer);

	HAL_DAC_Start_DMA(hdac, DAC_CHANNEL_1, (uint32_t *) dev->buffer, dev->size, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start(tmr);
}

void __AnaOut_SetupSine(uint16_t *buffer) {
	for (uint16_t i = 0; i < ANAOUT_BUFFER_SIZE; i++) {
		buffer[i] = ((sin(i * 2 * PI / ANAOUT_BUFFER_SIZE) + 1) * (4096 / 2));
	}
}

// CALLBACKS