/*
 * LCR_Slave.h
 *
 *  Created on: 27.09.2021
 *      Author: Tim Goll
 */

#ifndef INC_LCR_SLAVE_H
#define INC_LCR_SLAVE_H

#include "LCR_Data.h"
#include "stm32h7xx_hal.h" // Needed for I2C

#include <stdio.h>
#include <string.h>

typedef enum {
	LCR_SLAVE_READY = 0,
	LCR_SLAVE_BUSY = 1,
	LCR_SLAVE_BUSY_TX = 2,
	LCR_SLAVE_BUSY_RX = 3,
	LCR_SLAVE_DATA_AVAILABLE = 4
} LCR_Slave_StateTypeDef;

// LCR Slave STRUCT
typedef struct {
	/* I2C handle */
	I2C_HandleTypeDef *i2cHandle;

	/* the memory that can be set from the outside */
	uint8_t *memory;

	/* the starting address in the memory when the transmission started */
	uint8_t *start_address;

	/* the current address in the memory */
	uint8_t *last_address;

	/* the current state of the data reader */
	LCR_Slave_StateTypeDef state;

	/* the bank of the status LED */
	GPIO_TypeDef *gpio_bank;

	/* the status led pin */
	uint16_t gpio_pin;

	/* internal variable that tracks if address is set */
	uint8_t __found_address;
} LCR_Slave;

extern LCR_Slave *__LCRSlaveList[4];
extern uint8_t __LCRSlaveListSize;

void LCR_Slave_Initialize(LCR_Slave *dev, I2C_HandleTypeDef *i2cHandle, GPIO_TypeDef *gpio_bank, uint16_t gpio_pin);
LCR_Slave_StateTypeDef LCR_Slave_HandleData(LCR_Slave *dev);

uint8_t __LCR_Slave_FindSlave(I2C_HandleTypeDef *i2cHandle, LCR_Slave **lcr_slave);

#endif /* INC_LCR_SLAVE_H */
