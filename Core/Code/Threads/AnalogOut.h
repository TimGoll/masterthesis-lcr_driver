#pragma once

#include "cmsis_os.h"

#include "../Logic/SineGen.h"
#include "../Logic/CoreData.h"

#include "../Libs/MCP4725/MCP4725.h"
#include "../Libs/Common/Common.h"

#define MCP4725_ADDRESS_RESISTANCE 0x62

typedef struct {
	TIM_HandleTypeDef *tmr;
	DAC_HandleTypeDef *hdac_1;
	I2C_HandleTypeDef *i2c_handle;
} AnalogOut_Parameter_t;

void AnalogOut_StartThread(void *argument);
