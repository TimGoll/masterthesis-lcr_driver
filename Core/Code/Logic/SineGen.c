#include "SineGen.h"

void SineGen_Initialize(SineGen_t *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac) {
	dev->hdac = hdac;
	dev->size = ANAOUT_BUFFER_SIZE;

	__SineGen_SetupSine(dev->buffer);

	HAL_DAC_Start_DMA(hdac, DAC_CHANNEL_1, (uint32_t *) dev->buffer, dev->size, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start(tmr);
}

void __SineGen_SetupSine(uint16_t *buffer) {
	for (uint16_t i = 0; i < ANAOUT_BUFFER_SIZE; i++) {
		buffer[i] = ((sin(i * 2 * PI / ANAOUT_BUFFER_SIZE) + 1) * (4096 / 2));
	}
}

// CALLBACKS

void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac) {
	// called when conversion is fully finished
	//char usb_buf[128];

	//uint16_t usb_buf_len = snprintf(usb_buf, 128, "DAC - SysTick (Half Complete): %lu\r\n", HAL_GetTick());
	//HAL_UART_Transmit(&huart3, (uint8_t *) usb_buf, usb_buf_len, HAL_MAX_DELAY);
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac) {
	// called when conversion is fully finished
	//char usb_buf[128];

	//uint16_t usb_buf_len = snprintf(usb_buf, 128, "DAC - SysTick (Complete): %lu\r\n", HAL_GetTick());
	//HAL_UART_Transmit(&huart3, (uint8_t *) usb_buf, usb_buf_len, HAL_MAX_DELAY);
}
