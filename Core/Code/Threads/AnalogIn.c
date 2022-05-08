#include "AnalogIn.h"

AnaRP_t analogData_voltage;
AnaRP_t analogData_current;
AnaRP_t analogData_temperature;

void AnalogIn_StartThread(void *argument) {
	AnalogIn_Parameter_t *params = (AnalogIn_Parameter_t *) argument;

	DEEstModels_Initialize();

	AnaRP_Initialize(&analogData_voltage, params->hadc_1);
	AnaRP_Initialize(&analogData_current, params->hadc_2);
	//AnaRP_Initialize(&analogData_temperature, params->hadc_3);

	HAL_TIM_OC_Start(params->htim, TIM_CHANNEL_1); // TODO debugging pin out

	while(1) {
		// attempt to process data
		if (AnaRP_FinishedReading(&analogData_voltage) && AnaRP_FinishedReading(&analogData_current)) {
			DEEstHandler_RunModel(&analogData_voltage, &analogData_current);

			// after the processing of the data, the state is reset
			AnaRP_ResetState(&analogData_voltage);
			AnaRP_ResetState(&analogData_current);
		}

		// only restart a new ADC read if both ADCs are ready
		if (AnaRP_IsReady(&analogData_voltage) && AnaRP_IsReady(&analogData_current)) {
			// stop the timer so that it can be restarted after a new DMA
			// conversion is triggered; this is important to have both conversion
			// perfectly in sync
			HAL_TIM_Base_Stop(params->htim);

			// start the HAL conversion; it starts on the first timer tick
			AnaRP_StartDMA(&analogData_voltage);
			AnaRP_StartDMA(&analogData_current);

			// now start the timer
			HAL_TIM_Base_Start(params->htim);
		}

		osDelay(1);
	}
}
