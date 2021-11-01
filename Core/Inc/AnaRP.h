/*
 * AnaRP.h
 * Analog Read and Process data
 *
 *  Created on: 28.09.2021
 *      Author: Tim Goll
 */

#ifndef INC_ANARP_H
#define INC_ANARP_H

#include "stm32h7xx_hal.h"

//size should be set so that size/2 is enough to reconstruct sine wave
#define ANARP_BUFFER_SIZE 4096

typedef struct {
	ADC_HandleTypeDef *hadc;
	uint16_t size;
	uint16_t buffer[ANARP_BUFFER_SIZE];
} AnaRP;

void AnaRP_Initialize(AnaRP *dev, ADC_HandleTypeDef *hadc);
void AnaRP_HandleData(AnaRP *dev);

#endif /* INC_ANARP_H */
