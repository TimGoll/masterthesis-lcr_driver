#include "MainThread.h"

// define struct for LCR slave handler
I2CSlave_t i2cSlave;

void MainThread_StartThread(void *argument) {
	// set initial values first
	CoreData_SetInitialDevID(0xAB);
	CoreData_SetInitialMemsID(0x61);
	CoreData_SetInitialPartID(0xFF);
	CoreData_SetInitialMinMeasurementVoltage(124); // 0.1V
	CoreData_SetInitialMaxMeasurementVoltage(3970); // 3.2V
	CoreData_SetInitialMeasurementFrequency(10000); // 10kHz
	CoreData_SetInitialDEModel(2); // 2

	// Set this to true so that initializing the data always sets it to true
	// in the data array. This is only used to detect if the storage in the
	// flash was initialized.
	CoreData_SetInitialInitialized(1);

	// then initialize the memory
	CoreData_Initialize();

	// TODO remove this again, only for debugging to ignore flash
	CoreData_Reset();

	// set up LCR slave
	I2CSlave_Initialize(&i2cSlave, (I2C_HandleTypeDef *) argument, GPIOB, GPIO_PIN_7);

	while(1) {
		CoreData_HandleData();

		Flash_HandleData();

		I2CSlave_HandleData(&i2cSlave);

		osDelay(100);
	}
}
