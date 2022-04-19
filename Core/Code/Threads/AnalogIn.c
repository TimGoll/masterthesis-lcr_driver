#include "AnalogIn.h"

AnaRP_t analogData_voltage;
AnaRP_t analogData_current;
AnaRP_t analogData_temperature;

void AnalogIn_StartThread(void *argument) {
	AnalogIn_Parameter_t *params = (AnalogIn_Parameter_t *) argument;

	AnaRP_Initialize(&analogData_voltage, params->hadc_1);
	AnaRP_Initialize(&analogData_current, params->hadc_2);
	AnaRP_Initialize(&analogData_temperature, params->hadc_3);

	while(1) {
		osDelay(100);
	}
}
