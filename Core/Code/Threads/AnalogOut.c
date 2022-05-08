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
		uint32_t test = CoreData_GetDEResistance();

		uint16_t resistance = (uint16_t) Common_Map(CoreData_GetDEResistance(), DAC_RESISTANCE_LOWER_LIMIT, DAC_RESISTANCE_UPPER_LIMIT, 0, 4095);

		MCP4725_SetVoltage(&extDAC_resistance, resistance, MCP4725_DAC_ONLY);

		osDelay(100); //update analog output 10 times per second
	}
}
