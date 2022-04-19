#include "MainThread.h"

// define struct for LCR slave handler
I2CSlave_t i2cSlave;

void MainThread_StartThread(void *argument) {
	// set initial values first
	LCRData_SetInitialDevID(0xAB);
	LCRData_SetInitialMemsID(0x61);
	LCRData_SetInitialPartID(0xFF);
	LCRData_SetInitialMeasurementFrequency(10000); // 10kHz

	// Set this to true so that initializing the data always sets it to true
	// in the data array. This is only used to detect if the storage in the
	// flash was initialized.
	LCRData_SetInitialInitialized(1);

	// then initialize the memory
	LCRData_Initialize();

	// set up LCR slave
	I2CSlave_Initialize(&i2cSlave, (I2C_HandleTypeDef *) argument, GPIOB, GPIO_PIN_7);

	while(1) {
		LCRData_HandleData();

		Flash_HandleData();

		I2CSlave_HandleData(&i2cSlave);

		osDelay(100);
	}
}
