#include "cmsis_os.h"

#include "../Logic/AnaRP.h"

typedef struct {
	ADC_HandleTypeDef *hadc_1;
	ADC_HandleTypeDef *hadc_2;
	ADC_HandleTypeDef *hadc_3;
	TIM_HandleTypeDef *htim;
} AnalogIn_Parameter_t;
