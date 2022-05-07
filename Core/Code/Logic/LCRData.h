/**
  ******************************************************************************
  * @file           LCRData.h
  * @author         Tim Goll
  * @date           29.09.2021
  * @brief          Handles the core data of the LCR meter that can be accessed from the outside.
  ******************************************************************************
  * LCR Data is the core system of the project. It consists of 128 bytes of storage
  * that can be accessed via helper functions and should contain the measurement
  * data as well as configuration parameters.
  * This addressable data array is also exposed to the outside through an I2C interface.
  *
  ******************************************************************************
  */

#pragma once

#include "stm32h7xx_hal.h"
#include "Flash.h"

#define LCR_DATA_FLASH_ADDRESS 0x081E0000

// define the address range (8-bit)
#define LCR_DATA_SIZE 256

// define addresses
#define LCR_DATA_REG_INITIALIZED 0 ///< size: 1 byte
#define LCR_DATA_REG_DEVID 1 ///< size: 1 byte
#define LCR_DATA_REG_MEMSID 2 ///< size: 1 byte
#define LCR_DATA_REG_PARTID 3 ///< size: 1 byte
#define LCR_DATA_REG_MEM_ADDRESS 4 ///< size: 1 byte
#define LCR_DATA_REG_MEM_ADDRESS_START 5 ///< size: 1 byte
#define LCR_DATA_REG_MES_VOLT_MIN 6 ///< size: 2 bytes
#define LCR_DATA_REG_MES_VOLT_MAX 8 ///< size: 2 bytes
#define LCR_DATA_REG_MES_FREQ 10 ///< size: 2 bytes
#define LCR_DATA_REG_DE_MODEL 12 ///< size: 1 byte

#define LCR_DATA_REG_DE_RESISTANCE 127 ///< size: 2 bytes
#define LCR_DATA_REG_DE_CAPACITANCE 129 ///< size: 2 bytes
#define LCR_DATA_REG_DE_PHASE 131 ///< size: 2 bytes
#define LCR_DATA_REG_DE_VOLTAGE_MAG 133 ///< size: 2 bytes
#define LCR_DATA_REG_DE_CURRENT_MAG 135 ///< size: 2 bytes

#define LCR_DATA_REG_COMMAND LCR_DATA_SIZE - 5 ///< size: 1 byte command followed by 4 bytes of data

/**
 * @brief An enum that handles the register type.
 *
 * The system consists of two parallel registers. One for the current data, one for the initial data.
 */
typedef enum {
	LCR_DATA_REG_DATA = 0x00, ///< The register that contains the live data
	LCR_DATA_REG_INITIAL = 0x01 ///< The register that contains the initial data, it is unchanged on runtime
} LCRData_RegisterTypeDef;

/**
 * @brief An enum that contains all available commands that can be issued inside the command register.
 */
typedef enum {
	LCR_DATA_RESET = 0x01, ///< resets the live data register to the initial data register
	LCR_DATA_STORE = 0x02 ///< stores the live data register to the flash memory
} LCRData_CommandTypeDef;

extern uint8_t data[LCR_DATA_SIZE]; ///< the live data
extern uint8_t initial[LCR_DATA_SIZE]; ///< the initial data

void LCRData_Initialize();
void LCRData_Reset();
void LCRData_Store();
void LCRData_HandleData();

uint8_t *LCRData_GetDataArrayReference();

uint8_t LCRData_SetInitialized(uint8_t initialized);
uint8_t LCRData_SetInitialInitialized(uint8_t initialized);
uint8_t LCRData_IsInitialized();
uint8_t *LCRData_GetInitializedReference();

uint8_t LCRData_SetDevID(uint8_t device_id);
uint8_t LCRData_SetInitialDevID(uint8_t device_id);
uint8_t LCRData_GetDevID();
uint8_t *LCRData_GetDevIDReference();
uint8_t LCRData_SetMemsID(uint8_t mems_id);
uint8_t LCRData_SetInitialMemsID(uint8_t device_id);
uint8_t LCRData_GetMemsID();
uint8_t *LCRData_GetMemsIDReference();
uint8_t LCRData_SetPartID(uint8_t part_id);
uint8_t LCRData_SetInitialPartID(uint8_t part_id);
uint8_t LCRData_GetPartID();
uint8_t *LCRData_GetPartIDReference();
uint8_t LCRData_SetMemoryAddress(uint8_t mem_address);
uint8_t LCRData_SetInitialMemoryAddress(uint8_t mem_address);
uint8_t LCRData_GetMemoryAddress();
uint8_t *LCRData_GetMemoryAddressReference();
uint8_t LCRData_SetStartingMemoryAddress(uint8_t mem_address);
uint8_t LCRData_SetInitialStartingMemoryAddress(uint8_t mem_address);
uint8_t LCRData_GetStartingMemoryAddress();
uint8_t *LCRData_GetStartingMemoryAddressReference();
uint8_t LCRData_SetMinMeasurementVoltage(uint16_t voltage);
uint8_t LCRData_SetInitialMinMeasurementVoltage(uint16_t voltage);
uint16_t LCRData_GetMinMeasurementVoltage();
uint16_t *LCRData_GetMinMeasurementVoltageReference();
uint8_t LCRData_SetMaxMeasurementVoltage(uint16_t voltage);
uint8_t LCRData_SetInitialMaxMeasurementVoltage(uint16_t voltage);
uint16_t LCRData_GetMaxMeasurementVoltage();
uint16_t *LCRData_GetMaxMeasurementVoltageReference();
uint8_t LCRData_SetMeasurementFrequency(uint16_t frequency);
uint8_t LCRData_SetInitialMeasurementFrequency(uint16_t frequency);
uint16_t LCRData_GetMeasurementFrequency();
uint16_t *LCRData_GetMeasurementFrequencyReference();
uint8_t LCRData_SetDEModel(uint8_t model);
uint8_t LCRData_SetInitialDEModel(uint8_t model);
uint8_t LCRData_GetDEModel();
uint8_t *LCRData_GetDEModelReference();

uint8_t LCRData_SetDEResistance(uint16_t resistance);
uint8_t LCRData_SetInitialDEResistance(uint16_t resistance);
uint16_t LCRData_GetDEResistance();
uint16_t *LCRData_GetDEResistanceReference();
uint8_t LCRData_SetDECapacitance(uint16_t capacitance);
uint8_t LCRData_SetInitialDECapacitance(uint16_t capacitance);
uint16_t LCRData_GetDECapacitance();
uint16_t *LCRData_GetDECapacitanceReference();
uint8_t LCRData_SetDEPhase(uint16_t phase);
uint8_t LCRData_SetInitialDEPhase(uint16_t phase);
uint16_t LCRData_GetDEPhase();
uint16_t *CurrentMagnitude();
uint8_t LCRData_SetDEVoltageMagnitude(uint16_t voltage);
uint8_t LCRData_SetInitialDEVoltageMagnitude(uint16_t voltage);
uint16_t LCRData_GetDEVoltageMagnitude();
uint16_t *LCRData_GetDEVoltageMagnitudeReference();
uint8_t LCRData_SetDECurrentMagnitude(uint16_t current);
uint8_t LCRData_SetInitialDECurrentMagnitude(uint16_t current);
uint16_t LCRData_GetDECurrentMagnitude();
uint16_t *LCRData_GetDECurrentMagnitudeReference();

void * __LCRData_GetDataReference(LCRData_RegisterTypeDef reg_type, uint8_t address);
uint32_t *__LCRData_GetWordReference(LCRData_RegisterTypeDef reg_type, uint8_t address);
uint16_t *__LCRData_GetHalfWordReference(LCRData_RegisterTypeDef reg_type, uint8_t address);
uint8_t *__LCRData_GetByteReference(LCRData_RegisterTypeDef reg_type, uint8_t address);

uint32_t __LCRData_GetWord(LCRData_RegisterTypeDef reg_type, uint8_t address);
uint16_t __LCRData_GetHalfWord(LCRData_RegisterTypeDef reg_type, uint8_t address);
uint8_t __LCRData_GetByte(LCRData_RegisterTypeDef reg_type, uint8_t address);

uint8_t __LCRData_SetData(LCRData_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address);
uint8_t __LCRData_SetWord(LCRData_RegisterTypeDef reg_type, uint32_t value, uint8_t address);
uint8_t __LCRData_SetHalfWord(LCRData_RegisterTypeDef reg_type, uint16_t value, uint8_t address);
uint8_t __LCRData_SetByte(LCRData_RegisterTypeDef reg_type, uint8_t value, uint8_t address);
