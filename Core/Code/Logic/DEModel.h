#pragma once

#include <math.h>

#include "../config.h"

#include "AnaRP.h"
#include "LCRData.h"

void DEModel_ProcessData(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data);

void DEModel_Calculate_RCModel(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data, uint16_t *resistance, uint16_t *capacitance);
