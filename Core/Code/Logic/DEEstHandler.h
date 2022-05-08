#pragma once

#include <stdio.h>
#include <string.h>

#include "AnaRP.h"
#include "../config.h"
#include "CoreData.h"

typedef struct {
	char name[16];
	void (*process)(AnaRP_t *voltage_data, AnaRP_t *current_data);
} DEEstHandler_Model_t;

DEEstHandler_Model_t __DEEstList[DEESTIMATION_MODEL_COUNT]; ///< a list that contains all DE estimation models
uint8_t __DEEstListSize; ///< the amount of DE estimation models
uint8_t __DEEstSelected; ///< the id of the selected model

void DEEstHandler_Register(char* name, void (*init)(), void (*process)(AnaRP_t *voltage_data, AnaRP_t *current_data));

void DEEstHandler_RunModel(AnaRP_t *voltage_data, AnaRP_t *current_data);

char *DEEstHandler_GetModelName();
