/*
 * LCR_Slave.c
 *
 *  Created on: 27.09.2021
 *      Author: Tim Goll
 */

#include "LCR_Slave.h"

LCR_Slave *__LCRSlaveList[4]; //4 I2C ports available
uint8_t __LCRSlaveListSize = 0;

void LCR_Slave_Initialize(LCR_Slave *dev, I2C_HandleTypeDef *i2cHandle, GPIO_TypeDef *gpio_bank, uint16_t gpio_pin) {
	dev->i2cHandle = i2cHandle;
	dev->start_address = LCR_Data_GetStartingMemoryAddressReference();
	dev->last_address = LCR_Data_GetMemoryAddressReference();
	dev->state = LCR_SLAVE_READY;
	dev->gpio_bank = gpio_bank;
	dev->gpio_pin = gpio_pin;
	dev->__found_address = 0;
	dev->memory = LCR_Data_GetDataArrayReference();

	// add slave to list of slaves
	__LCRSlaveList[__LCRSlaveListSize] = dev;

	__LCRSlaveListSize++;

	// set up interrupt for I2C slave after i2c is set up and running
	HAL_I2C_EnableListen_IT(i2cHandle);
}

LCR_Slave_StateTypeDef LCR_Slave_HandleData(LCR_Slave *dev) {
	// the bus is still busy, check next time
	if (dev->state == LCR_SLAVE_BUSY) {
		return LCR_SLAVE_BUSY;
	}

	// nothing new available, check next time
	if (dev->state == LCR_SLAVE_READY) {
		return LCR_SLAVE_READY;
	}

	dev->state = LCR_SLAVE_READY;

	return LCR_SLAVE_DATA_AVAILABLE;
}

uint8_t __LCR_Slave_FindSlave(I2C_HandleTypeDef *i2cHandle, LCR_Slave **lcr_slave) {
	for (uint8_t i = 0; i < __LCRSlaveListSize; i++) {
		if (__LCRSlaveList[i]->i2cHandle->Instance == i2cHandle->Instance) {
			*lcr_slave = __LCRSlaveList[i];

			return 1;
		}
	}

	return 0;
}

// I2C BUS CALLBACKS
// no major calculations are done here!

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c) {
	LCR_Slave *dev;

	// check if slave is valid, stop if it is invalid
	if (!__LCR_Slave_FindSlave(hi2c, &dev)) {
		return;
	}

	// disable status LED once transmission is done
	HAL_GPIO_WritePin(dev->gpio_bank, dev->gpio_pin, GPIO_PIN_RESET);

	if (dev->state == LCR_SLAVE_BUSY_RX) {
		dev->state = LCR_SLAVE_DATA_AVAILABLE;
	} else {
		dev->state = LCR_SLAVE_READY;
	}

	dev->__found_address = 0;

	// this flag has to be force-set to null to prevent the next array entry being filled
	// again with the same value once a new transmission starts
	hi2c->pBuffPtr = NULL;

	HAL_I2C_EnableListen_IT(hi2c); // slave is ready again
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode) {
	LCR_Slave *dev;

	// check if slave is valid, stop if it is invalid
	if (!__LCR_Slave_FindSlave(hi2c, &dev)) {
		return;
	}

	dev->state = LCR_SLAVE_BUSY;

	// enable status LED while transmission is active
	HAL_GPIO_WritePin(dev->gpio_bank, dev->gpio_pin, GPIO_PIN_SET);

	// Transmit direction is from the master's point of view
	// This part is called for both reading and writing. While it is not strictly required to
	// send an address prior to requesting data, it is probably useful in most cases since one would
	// want to receive a specific set of data.
	if (TransferDirection == I2C_DIRECTION_TRANSMIT) {
		// no address found as of yet -> this byte is the address
		// dev->__found_address is updated once the first byte is received in HAL_I2C_SlaveRxCpltCallback

		HAL_I2C_Slave_Seq_Receive_IT(hi2c, dev->last_address, 1, I2C_NEXT_FRAME);
	} else {
		// reading data request, send one byte
		// further bytes are then handled in the HAL_I2C_SlaveTxCpltCallback callback
		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &dev->memory[*dev->last_address], 1, I2C_NEXT_FRAME);
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	LCR_Slave *dev;

	// check if slave is valid, stop if it is invalid
	if (!__LCR_Slave_FindSlave(hi2c, &dev)) {
		return;
	}

	if (!dev->__found_address) {
		// if the address wasn't yet set, the previously received byte is the address
		// therefore the flag has to be set, while also copying the value in the
		// starting address register
		dev->__found_address = 1;

		*dev->start_address = *dev->last_address;
	} else {
		// if the last byte was data, the address has to be increased by one
		// but only if in normal master write mode
		(*dev->last_address)++;

		// receive data mode
		dev->state = LCR_SLAVE_BUSY_RX;
	}

	// write mode: master sends data
	// if no further data is sent, this function does nothing and the transmission is ended
	HAL_I2C_Slave_Seq_Receive_IT(hi2c, &dev->memory[*dev->last_address], 1, I2C_NEXT_FRAME);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	LCR_Slave *dev;

	// check if slave is valid, stop if it is invalid
	if (!__LCR_Slave_FindSlave(hi2c, &dev)) {
		return;
	}

	(*dev->last_address)++;

	HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &dev->memory[*dev->last_address], 1, I2C_NEXT_FRAME);

	// transmit data mode
	dev->state = LCR_SLAVE_BUSY_TX;
}
