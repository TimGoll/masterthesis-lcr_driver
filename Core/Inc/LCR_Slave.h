/**
  ******************************************************************************
  * @file           LCR_Slave.h
  * @author         Tim Goll
  * @date           27.10.2021
  * @brief          Handles the LCR slaves on the MCU.
  ******************************************************************************
  * The MCU can be accessed as a slave from any other device. The communication
  * protocol is via I2C. This makes it possible to communicate with this device
  * and exchange digital data. Be it the current measurement data or config parameters.
  *
  ******************************************************************************
  */

#ifndef INC_LCR_SLAVE_H
#define INC_LCR_SLAVE_H

#include "LCR_Data.h"
#include "stm32h7xx_hal.h" // Needed for I2C

#include <stdio.h>
#include <string.h>

/**
 * @brief An enum that describes the current availability state of the LCR slave.
 */
typedef enum {
	LCR_SLAVE_READY = 0, ///< The slave idles and is ready to receive or transmit data
	LCR_SLAVE_BUSY = 1, ///< The slave is currently busy
	LCR_SLAVE_BUSY_TX = 2, ///< The slave is currently busy with transmitting data
	LCR_SLAVE_BUSY_RX = 3, ///< The slave is currently busy with receiving data
	LCR_SLAVE_DATA_AVAILABLE = 4 ///< A transmission is finished and new data is available
} LCR_Slave_StateTypeDef;

// LCR Slave STRUCT
typedef struct {
	I2C_HandleTypeDef *i2cHandle; ///< I2C handle

	uint8_t *memory; ///< The memory that can be set from the outside

	uint8_t *start_address; ///< The starting address in the memory when the transmission started

	uint8_t *last_address; ///< The current address in the memory

	LCR_Slave_StateTypeDef state; ///< The current state of the data reader

	GPIO_TypeDef *gpio_bank; ///< The bank of the status LED

	uint16_t gpio_pin; ///< The status led pin

	uint8_t __found_address; ///< Internal variable that tracks if address is set
} LCR_Slave;

extern LCR_Slave *__LCRSlaveList[4]; ///< A list that contains all LCR slave objects. There is probably only one slave, but it is possible to have multiple seperate slaves on the same MCU.
extern uint8_t __LCRSlaveListSize; ///< The amount of slaves on the MCU.

/**
 * Initializes a new slave instance. Adds all necessary data to the slave data object and adds said object to the array of available slaves.
 *
 * @param [in] *dev The slave data struct that contains everything regarding the specific slave instance
 * @param [in] *i2cHandle The handle to the i2c port used by the slave
 * @param [in] *gpio_bank The GPIO port bank where the status LED is located
 * @param [in] gpio_pin The GPIO pin number on the previously mentioned bank
 */
void LCR_Slave_Initialize(LCR_Slave *dev, I2C_HandleTypeDef *i2cHandle, GPIO_TypeDef *gpio_bank, uint16_t gpio_pin);

/**
 * Repeatedly checks the busy flag of the data struct. If there is data available, a data availability flag is returned.
 *
 * @param [in] *dev The slave data struct that contains everything regarding the specific slave instance
 *
 * @retval LCR_Slave_StateTypeDef The data availability
 */
LCR_Slave_StateTypeDef LCR_Slave_HandleData(LCR_Slave *dev);

/**
 * An internal function that is used to find the LCR slave in the list of available slaves. If data is received,
 * it is handled in the I2C callback. To reassociate the arriving data with the available slaves, the I2C instances are checked.
 *
 * @intfunction
 *
 * @param [in] *i2cHandle The handle to the i2c port that received data
 * @param [out] **lcr_slave The pointer to the lcr slave pointer that is set if the slave is found
 *
 * @retval uint8_t The result of the search. 1 if a slave was found.
 */
uint8_t __LCR_Slave_FindSlave(I2C_HandleTypeDef *i2cHandle, LCR_Slave **lcr_slave);

#endif /* INC_LCR_SLAVE_H */
