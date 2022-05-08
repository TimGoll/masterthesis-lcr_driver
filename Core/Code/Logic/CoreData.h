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

#define COREDATA_FLASH_ADDRESS 0x081E0000

// define the address range (8-bit)
#define COREDATA_SIZE 256

// define addresses
#define COREDATA_REG_INITIALIZED 0 ///< size: 1 byte
#define COREDATA_REG_DEVID 1 ///< size: 1 byte
#define COREDATA_REG_MEMSID 2 ///< size: 1 byte
#define COREDATA_REG_PARTID 3 ///< size: 1 byte
#define COREDATA_REG_MEM_ADDRESS 4 ///< size: 1 byte
#define COREDATA_REG_MEM_ADDRESS_START 5 ///< size: 1 byte
#define COREDATA_REG_MES_VOLT_MIN 6 ///< size: 2 bytes
#define COREDATA_REG_MES_VOLT_MAX 8 ///< size: 2 bytes
#define COREDATA_REG_MES_FREQ 10 ///< size: 2 bytes
#define COREDATA_REG_DE_MODEL 12 ///< size: 1 byte

#define COREDATA_REG_DE_RESISTANCE 127 ///< size: 4 bytes
#define COREDATA_REG_DE_CAPACITANCE 131 ///< size: 4 bytes

#define COREDATA_REG_COMMAND COREDATA_SIZE - 5 ///< size: 1 byte command followed by 4 bytes of data

/**
 * @brief An enum that handles the register type.
 *
 * The system consists of two parallel registers. One for the current data, one for the initial data.
 */
typedef enum {
	COREDATA_REG_DATA = 0x00, ///< The register that contains the live data
	COREDATA_REG_INITIAL = 0x01 ///< The register that contains the initial data, it is unchanged on runtime
} CoreData_RegisterTypeDef;

/**
 * @brief An enum that contains all available commands that can be issued inside the command register.
 */
typedef enum {
	COREDATA_RESET = 0x01, ///< resets the live data register to the initial data register
	COREDATA_STORE = 0x02 ///< stores the live data register to the flash memory
} CoreData_CommandTypeDef;

extern uint8_t data[COREDATA_SIZE]; ///< the live data
extern uint8_t initial[COREDATA_SIZE]; ///< the initial data

void CoreData_Initialize();
void CoreData_Reset();
void CoreData_Store();
void CoreData_HandleData();

uint8_t *CoreData_GetDataArrayReference();

uint8_t CoreData_SetInitialized(uint8_t initialized);
uint8_t CoreData_SetInitialInitialized(uint8_t initialized);
uint8_t CoreData_IsInitialized();
uint8_t *CoreData_GetInitializedReference();

uint8_t CoreData_SetDevID(uint8_t device_id);
uint8_t CoreData_SetInitialDevID(uint8_t device_id);
uint8_t CoreData_GetDevID();
uint8_t *CoreData_GetDevIDReference();
uint8_t CoreData_SetMemsID(uint8_t mems_id);
uint8_t CoreData_SetInitialMemsID(uint8_t device_id);
uint8_t CoreData_GetMemsID();
uint8_t *CoreData_GetMemsIDReference();
uint8_t CoreData_SetPartID(uint8_t part_id);
uint8_t CoreData_SetInitialPartID(uint8_t part_id);
uint8_t CoreData_GetPartID();
uint8_t *CoreData_GetPartIDReference();
uint8_t CoreData_SetMemoryAddress(uint8_t mem_address);
uint8_t CoreData_SetInitialMemoryAddress(uint8_t mem_address);
uint8_t CoreData_GetMemoryAddress();
uint8_t *CoreData_GetMemoryAddressReference();
uint8_t CoreData_SetStartingMemoryAddress(uint8_t mem_address);
uint8_t CoreData_SetInitialStartingMemoryAddress(uint8_t mem_address);
uint8_t CoreData_GetStartingMemoryAddress();
uint8_t *CoreData_GetStartingMemoryAddressReference();
uint8_t CoreData_SetMinMeasurementVoltage(uint16_t voltage);
uint8_t CoreData_SetInitialMinMeasurementVoltage(uint16_t voltage);
uint16_t CoreData_GetMinMeasurementVoltage();
uint16_t *CoreData_GetMinMeasurementVoltageReference();
uint8_t CoreData_SetMaxMeasurementVoltage(uint16_t voltage);
uint8_t CoreData_SetInitialMaxMeasurementVoltage(uint16_t voltage);
uint16_t CoreData_GetMaxMeasurementVoltage();
uint16_t *CoreData_GetMaxMeasurementVoltageReference();
uint8_t CoreData_SetMeasurementFrequency(uint16_t frequency);
uint8_t CoreData_SetInitialMeasurementFrequency(uint16_t frequency);
uint16_t CoreData_GetMeasurementFrequency();
uint16_t *CoreData_GetMeasurementFrequencyReference();
uint8_t CoreData_SetDEModel(uint8_t model);
uint8_t CoreData_SetInitialDEModel(uint8_t model);
uint8_t CoreData_GetDEModel();
uint8_t *CoreData_GetDEModelReference();

uint8_t CoreData_SetDEResistance(uint32_t resistance);
uint8_t CoreData_SetInitialDEResistance(uint32_t resistance);
uint32_t CoreData_GetDEResistance();
uint32_t *CoreData_GetDEResistanceReference();
uint8_t CoreData_SetDECapacitance(uint32_t capacitance);
uint8_t CoreData_SetInitialDECapacitance(uint32_t capacitance);
uint32_t CoreData_GetDECapacitance();
uint32_t *CoreData_GetDECapacitanceReference();

void * __CoreData_GetDataReference(CoreData_RegisterTypeDef reg_type, uint8_t address);
uint32_t *__CoreData_GetWordReference(CoreData_RegisterTypeDef reg_type, uint8_t address);
uint16_t *__CoreData_GetHalfWordReference(CoreData_RegisterTypeDef reg_type, uint8_t address);
uint8_t *__CoreData_GetByteReference(CoreData_RegisterTypeDef reg_type, uint8_t address);

uint32_t __CoreData_GetWord(CoreData_RegisterTypeDef reg_type, uint8_t address);
uint16_t __CoreData_GetHalfWord(CoreData_RegisterTypeDef reg_type, uint8_t address);
uint8_t __CoreData_GetByte(CoreData_RegisterTypeDef reg_type, uint8_t address);

uint8_t __CoreData_SetData(CoreData_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address);
uint8_t __CoreData_SetWord(CoreData_RegisterTypeDef reg_type, uint32_t value, uint8_t address);
uint8_t __CoreData_SetHalfWord(CoreData_RegisterTypeDef reg_type, uint16_t value, uint8_t address);
uint8_t __CoreData_SetByte(CoreData_RegisterTypeDef reg_type, uint8_t value, uint8_t address);
