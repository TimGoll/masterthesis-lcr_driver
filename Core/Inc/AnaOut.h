/*
 * AnaOut.h
 *
 *  Created on: Oct 18, 2021
 *      Author: Tim
 */

#ifndef INC_ANAOUT_H
#define INC_ANAOUT_H

#include "math.h"
#include "stm32h7xx_hal.h"

#define ANAOUT_BUFFER_SIZE 128
#define PI 3.1415926

typedef struct {
	DAC_HandleTypeDef *hdac;
	uint16_t size;
	uint16_t buffer[ANAOUT_BUFFER_SIZE];
} AnaOut;

void AnaOut_Initialize(AnaOut *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac);

void __AnaOut_SetupSine(uint16_t *buffer);

#endif /* INC_ANAOUT_H */
