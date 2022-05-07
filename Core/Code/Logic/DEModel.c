#include "DEModel.h"

void DEModel_ProcessData(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data) {
	LCRData_SetDEVoltageMagnitude((uint16_t) voltage_data->magnitude);
	LCRData_SetDECurrentMagnitude((uint16_t) current_data->magnitude);

	float32_t phase = fmod((voltage_data->phase - current_data->phase) * 180.0 / CONF_PI, 360.0);

	LCRData_SetDEPhase((uint16_t) (phase * 65536 / 360));

	switch (LCRData_GetDEModel()) {
		case 0:
			DEModel_Calculate_RCModel(voltage_data, current_data, LCRData_GetDEResistanceReference(), LCRData_GetDECapacitanceReference());
			break;
		default:
			DEModel_Calculate_RCModel(voltage_data, current_data, LCRData_GetDEResistanceReference(), LCRData_GetDECapacitanceReference());
			break;
	}
}

void DEModel_Calculate_RCModel(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data, uint16_t *resistance, uint16_t *capacitance) {
	float32_t voltage = voltage_data->magnitude;
	float32_t current = current_data->magnitude * DEMODEL_UAMPS_PER_VOLT;
	float32_t phase =  fmod((voltage_data->phase - current_data->phase), 2 * CONF_PI);
	float32_t frequency = voltage_data->frequency;

	float32_t impedance = voltage / current * 1000000.0; // Ohm
	float32_t impedance_real = impedance * cosf(phase);
	float32_t impedance_imag = impedance * sinf(phase);

	float32_t cap = 1000000000 / (-1 * impedance_imag * 2 * CONF_PI * frequency);

	//*resistance = impedance_real;
}
