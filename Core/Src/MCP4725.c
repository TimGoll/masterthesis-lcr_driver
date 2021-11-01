/*
 * MCP4725.c
 *
 *  Created on: 23.09.2021
 *      Author: Tim Goll
 */

#include "MCP4725.h"

HAL_StatusTypeDef MCP4725_Initialize(MCP4725 *dev, I2C_HandleTypeDef *i2cHandle, uint16_t address) {
	dev->i2cHandle = i2cHandle;
	dev->address = address << 1; // shift by one to make room for read/write bit
	dev->mode = MCP4725_MODE_NORMAL;
	dev->output_voltage = MCP4725_MAX_VOLTAGE / 2;
	dev->output_voltage_int = 2047;

	// now set the initial data to the data that is set on the chip
	dev->i2cState = MCP4725_GetDataFromChip(dev);

	return dev->i2cState;
}

HAL_StatusTypeDef MCP4725_SetMode(MCP4725 *dev, MCP4725_ModeTypeDef mode, MCP4725_DataModeTypeDef eeprom_or_dac) {
	dev->mode = mode;

	return MCP4725_WriteData(dev, eeprom_or_dac);
}

HAL_StatusTypeDef MCP4725_SetVoltage(MCP4725 *dev, float voltage, MCP4725_DataModeTypeDef eeprom_or_dac) {
	dev->output_voltage = voltage;
	dev->output_voltage_int = voltage / MCP4725_MAX_VOLTAGE * 4095;

	return MCP4725_WriteData(dev, eeprom_or_dac);
}

HAL_StatusTypeDef MCP4725_GetDataFromChip(MCP4725 *dev) {
	uint8_t data[3];

	HAL_StatusTypeDef status = MCP4725_ReadData(dev, data, 3);

	// an error occurred, don't proceed with parsing
	if (status != HAL_OK) {
		return status;
	}

	dev->mode = (MCP4725_ModeTypeDef) (data[0] << 5) & 0b11000000;
	dev->output_voltage_int = (uint16_t) ((data[1] << 4) | (data[2] >> 4)) & 0b0000111111111111;

	dev->output_voltage = ((float) dev->output_voltage_int) * ((float) MCP4725_MAX_VOLTAGE) / 4095.0f;

	return status;
}

HAL_StatusTypeDef MCP4725_ReadData(MCP4725 *dev, uint8_t *data, uint8_t length) {
	return HAL_I2C_Master_Receive(dev->i2cHandle, dev->address, data, length, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MCP4725_WriteData(MCP4725 *dev, MCP4725_DataModeTypeDef eeprom_or_dac) {
	if (eeprom_or_dac == MCP4725_DAC_AND_EEPROM) {
		uint8_t data[3];

		data[0] = (uint8_t) 0b01100000 | ((((uint8_t) dev->mode) >> 5) & 0b00000110);
		data[1] = (uint8_t) dev->output_voltage_int >> 4;
		data[2] = (uint8_t) (dev->output_voltage_int << 4) & 0b11110000;

		return HAL_I2C_Master_Transmit(dev->i2cHandle, dev->address, data, 3, HAL_MAX_DELAY);
	} else if (eeprom_or_dac == MCP4725_DAC_ONLY) {
		uint8_t data[2];

		data[0] = (uint8_t) ((((uint8_t) dev->mode) >> 2) & 0b00110000) | ((dev->output_voltage_int >> 8) & 0b00001111);
		data[1] = (uint8_t) dev->output_voltage_int;

		return HAL_I2C_Master_Transmit(dev->i2cHandle, dev->address, data, 2, HAL_MAX_DELAY);
	}

	// return HAL_ERROR if the mode is not defined
	return HAL_ERROR;
}
