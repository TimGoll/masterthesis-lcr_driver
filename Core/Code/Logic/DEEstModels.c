#include "DEEstModels.h"

void DEEstModels_Initialize() {
	DEEstHandler_Register("FFT RC", &DEEstModels_FFTRCModel_Init, &DEEstModels_FFTRCModel_Process);
	DEEstHandler_Register("IQ RC", &DEEstModels_IQRCModel_Init, &DEEstModels_IQRCModel_Process);
	DEEstHandler_Register("Rizzello", &DEEstModels_RizzelloModel_Init, &DEEstModels_RizzelloModel_Process);
}

// ESTIMATION MODEL FUNCTIONS HERE

// FFT RC Model
FFT_t fft_voltage;
FFT_t fft_current;

void DEEstModels_FFTRCModel_Init() {
	FFT_Initialize(&fft_voltage, ADC_SAMPLE_SIZE, ADC_SAMPLE_FREQ);
	FFT_Initialize(&fft_current, ADC_SAMPLE_SIZE, ADC_SAMPLE_FREQ);
}

void DEEstModels_FFTRCModel_Process(AnaRP_t *voltage_data, AnaRP_t *current_data) {
	FFT_Compute(&fft_voltage, voltage_data->buffer);
	FFT_Compute(&fft_current, current_data->buffer);

	float32_t voltage = fft_voltage.results.magnitude; // V
	float32_t current = fft_current.results.magnitude * ADC_UAMPS_PER_VOLT; // uA
	float32_t phase =  fmod((fft_voltage.results.phase - fft_current.results.phase), 2 * CONF_PI);

	float32_t impedance = voltage / current * 1000000.0; // Ohm
	float32_t impedance_real = impedance * cosf(phase);
	float32_t impedance_imag = impedance * sinf(phase);

	float32_t capacitance = 1000000000000000.0 / (-1 * impedance_imag * 2 * CONF_PI * fft_voltage.results.frequency); // fF
	float32_t resistance = -1 * impedance_real * 1000 - FIXED_DE_SERIES_RESISTANCE * 1000; // mOhm

	CoreData_SetDEResistance((uint32_t) resistance);
	CoreData_SetDECapacitance((uint32_t) capacitance);
}

void DEEstModels_IQRCModel_Init() {

}

void DEEstModels_IQRCModel_Process(AnaRP_t *voltage_data, AnaRP_t *current_data) {

}

void DEEstModels_RizzelloModel_Init() {

}

void DEEstModels_RizzelloModel_Process(AnaRP_t *voltage_data, AnaRP_t *current_data) {

}
