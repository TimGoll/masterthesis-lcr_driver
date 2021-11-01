/*
 * AnaRP.c
 *
 *  Created on: 28.09.2021
 *      Author: Tim Goll
 */

#include "AnaRP.h"

void AnaRP_Initialize(AnaRP *dev, ADC_HandleTypeDef *hadc) {
	dev->hadc = hadc;
	dev->size = ANARP_BUFFER_SIZE;

	HAL_ADC_Start_DMA(hadc, (uint32_t *) dev->buffer, ANARP_BUFFER_SIZE);
}

// CALLBACKS

