#include "AnaRP.h"

void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc) {
	dev->hadc = hadc;
	dev->size = ANARP_BUFFER_SIZE;

	HAL_ADC_Start_DMA(hadc, (uint32_t *) dev->buffer, ANARP_BUFFER_SIZE);
}

// CALLBACKS

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {
	// called when conversion is half finished
	//char usb_buf[128];

	//uint16_t usb_buf_len = snprintf(usb_buf, 128, "ADC - SysTick (Half Complete): %lu\r\n", HAL_GetTick());
	//HAL_UART_Transmit(&huart3, (uint8_t *) usb_buf, usb_buf_len, HAL_MAX_DELAY);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	// called when conversion is fully finished
	//char usb_buf[128];

	//uint16_t usb_buf_len = snprintf(usb_buf, 128, "ADC - SysTick (Complete): %lu\r\n", HAL_GetTick());
	//HAL_UART_Transmit(&huart3, (uint8_t *) usb_buf, usb_buf_len, HAL_MAX_DELAY);
}
