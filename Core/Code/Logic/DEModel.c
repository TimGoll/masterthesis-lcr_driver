#include "DEModel.h"

void DEModel_ProcessData(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data) {
	LCRData_SetDEVoltageMagnitude((uint16_t) voltage_data->magnitude);
	LCRData_SetDECurrentMagnitude((uint16_t) current_data->magnitude);

	float32_t phase = fmod((voltage_data->phase - current_data->phase) * 180.0 / CONF_PI, 360.0);

	LCRData_SetDEPhase((uint16_t) (phase * 65536 / 360));

	switch (LCRData_GetDEModel()) {
		case 0:
			DEModel_Calculate_RCModel(voltage_data, current_data);
			break;
		default:
			DEModel_Calculate_RCModel(voltage_data, current_data);
			break;
	}
}

void DEModel_Calculate_RCModel(AnaRP_FFTResults_t *voltage_data, AnaRP_FFTResults_t *current_data) {
	float32_t voltage = voltage_data->magnitude; // V
	float32_t current = current_data->magnitude * DEMODEL_UAMPS_PER_VOLT; // uA
	float32_t phase =  fmod((voltage_data->phase - current_data->phase), 2 * CONF_PI);
	float32_t frequency = voltage_data->frequency;

	float32_t impedance = voltage / current * 1000000.0; // Ohm
	float32_t impedance_real = impedance * cosf(phase);
	float32_t impedance_imag = impedance * sinf(phase);

	float32_t capacitance = 1000000000000.0 / (-1 * impedance_imag * 2 * CONF_PI * frequency); // pF
	float32_t resistance = -1 * impedance_real; // Ohm

	LCRData_SetDEResistance((uint16_t) resistance);
	LCRData_SetDECapacitance((uint16_t) capacitance);
}
