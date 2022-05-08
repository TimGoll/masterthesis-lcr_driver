#include "AnalogOut.h"

// define struct for analog output
SineGen_t sineGen_measurement;

// define struct for external DAC
MCP4725_t extDAC_resistance;

void AnalogOut_StartThread(void *argument) {
	AnalogOut_Parameter_t *params = (AnalogOut_Parameter_t *) argument;

	// initialize the analog output that sets the analog out
	MCP4725_Initialize(&extDAC_resistance, params->i2c_handle, MCP4725_ADDRESS_RESISTANCE);

	// pause this thread for a moment so that the lcr data thread is initialized first
	osDelay(10);

	// initialize the analog output for the measurement signal generation
	SineGen_Initialize(&sineGen_measurement, params->tmr, params->hdac_1, DAC_CHANNEL_1);

	// generate the sine wave with the current parameters
	SineGen_SetupSine(&sineGen_measurement, CoreData_GetMinMeasurementVoltage(), CoreData_GetMaxMeasurementVoltage(), CoreData_GetMeasurementFrequency());

	// output the sine wave
	SineGen_OutputSine(&sineGen_measurement);

	while(1) {
		uint32_t resistance = CoreData_GetDEResistance();
		float voltage = ((float) resistance) / 4294967295.0f * 3.3f;

		MCP4725_SetVoltage(&extDAC_resistance, voltage, MCP4725_DAC_ONLY);

		osDelay(100); //update analog output 10 times per second
	}
}
