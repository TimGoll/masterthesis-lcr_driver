/*
 * MCP4725.h
 *
 *  Created on: 23.09.2021
 *      Author: Tim Goll
 */

#ifndef INC_MCP4725_H
#define INC_MCP4725_H

#include "stm32h7xx_hal.h" // Needed for I2C

#define MCP4725_MAX_VOLTAGE 3.3f

typedef enum {
	MCP4725_MODE_NORMAL = 0b00000000,
	MCP4725_MODE_1k = 0b01000000,
	MCP4725_MODE_100k = 0b10000000,
	MCP4725_MODE_500k = 0b11000000
} MCP4725_ModeTypeDef;

typedef enum {
	MCP4725_DAC_AND_EEPROM = 0,
	MCP4725_DAC_ONLY = 1
} MCP4725_DataModeTypeDef;

// SENSOR STRUCT
typedef struct {
	/* I2C handle */
	I2C_HandleTypeDef *i2cHandle;

	/* Store the state of the i2c state here */
	HAL_StatusTypeDef i2cState;

	/* the address of the specific i2c device */
	uint16_t address;

	/* the current shutdown mode */
	MCP4725_ModeTypeDef mode;

	/* the output voltage in volt */
	float output_voltage;

	/* the output voltage as an integer */
	uint16_t output_voltage_int;
} MCP4725;

HAL_StatusTypeDef MCP4725_Initialize(MCP4725 *dev, I2C_HandleTypeDef *i2cHandle, uint16_t address);

HAL_StatusTypeDef MCP4725_SetMode(MCP4725 *dev, MCP4725_ModeTypeDef mode, MCP4725_DataModeTypeDef eeprom_or_dac);
HAL_StatusTypeDef MCP4725_SetVoltage(MCP4725 *dev, float voltage, MCP4725_DataModeTypeDef eeprom_or_dac);
HAL_StatusTypeDef MCP4725_GetDataFromChip(MCP4725 *dev);

HAL_StatusTypeDef MCP4725_ReadData(MCP4725 *dev, uint8_t *data, uint8_t length);
HAL_StatusTypeDef MCP4725_WriteData(MCP4725 *dev, MCP4725_DataModeTypeDef eeprom_or_dac);

#endif /* INC_MCP4725_H */
