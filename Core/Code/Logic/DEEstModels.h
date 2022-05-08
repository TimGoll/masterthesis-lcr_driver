#pragma once

#include "DEEstHandler.h"

#include <math.h>
#include <stdio.h>

#define ARM_MATH_CM7 // cortex m7 based MCU

#include "../../Libs/CMSIS_DSP/arm_math.h"
#include "../../Libs/FFT/FFT.h"

#include "CoreData.h"

void DEEstModels_Initialize();

void DEEstModels_FFTRCModel_Init();

void DEEstModels_FFTRCModel_Process(AnaRP_t *voltage_data, AnaRP_t *current_data);
