#include "AnalogIn.h"

AnaRP_t analogData_voltage;
AnaRP_t analogData_current;
AnaRP_t analogData_temperature;

void AnalogIn_StartThread(void *argument) {
	AnalogIn_Parameter_t *params = (AnalogIn_Parameter_t *) argument;

	AnaRP_Initialize(&analogData_voltage, params->hadc_1);
	AnaRP_Initialize(&analogData_current, params->hadc_2);
	//AnaRP_Initialize(&analogData_temperature, params->hadc_3);

	HAL_TIM_OC_Start(params->htim, TIM_CHANNEL_1); // TODO debugging pin out

	while(1) {
		// attempt to process data
		AnaRP_ProcessData(&analogData_voltage);
		AnaRP_ProcessData(&analogData_current);

		if (AnaRP_ResultsAvailable(&analogData_voltage) && AnaRP_ResultsAvailable(&analogData_current)) {
			DEModel_ProcessData(AnaRP_GetResults(&analogData_voltage), AnaRP_GetResults(&analogData_current));
		}

		// only restart a new ADC read if both ADCs are ready
		if (AnaRP_IsReady(&analogData_voltage) && AnaRP_IsReady(&analogData_current)) {
			// stop the timer so that it can be restarted after a new DMA
			// conversion is triggered; this is important to have both conversion
			// perfectly in sync
			HAL_TIM_Base_Stop(params->htim);

			osDelay(1);

			// start the HAL conversion; it starts on the first timer tick
			AnaRP_StartDMA(&analogData_voltage);
			AnaRP_StartDMA(&analogData_current);

			// now start the timer
			HAL_TIM_Base_Start(params->htim);
		}

		osDelay(1);
	}
}
