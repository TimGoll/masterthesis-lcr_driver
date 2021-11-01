/*
 * LCR_Data.h
 *
 * LCR Data is the core system of the project. It consists of 128 bytes of storage
 * that can be accessed via helper functions and should contain the measurement
 * data as well as configuration parameters.
 * This addressable data array is also exposed to the outside through an I2C interface.
 *
 *
 * Created on: 29.09.2021
 * Author: Tim Goll
 */

#ifndef INC_LCR_DATA_H
#define INC_LCR_DATA_H

#include "stm32h7xx_hal.h"
#include "Flash.h"

#define LCR_DATA_FLASH_ADDRESS 0x081E0000

// define the address range (8-bit)
#define LCR_DATA_SIZE 256

// define addresses
#define LCR_DATA_REG_INITIALIZED 0 // 1 byte
#define LCR_DATA_REG_DEVID 1 // 1 byte
#define LCR_DATA_REG_MEMSID 2 // 1 byte
#define LCR_DATA_REG_PARTID 3 // 1 byte
#define LCR_DATA_REG_MEM_ADDRESS 4 // 1 byte
#define LCR_DATA_REG_MEM_ADDRESS_START 5 // 1 byte
#define LCR_DATA_REG_RESISTANCE 6 // 4 bytes
#define LCR_DATA_REG_CAPACITANCE 10 // 4 bytes
#define LCR_DATA_REG_MES_VOLT_MIN 14 // 2 bytes
#define LCR_DATA_REG_MES_VOLT_MAX 16 // 2 bytes
#define LCR_DATA_REG_MES_FREQ 18 // 2 bytes

#define LCR_DATA_REG_COMMAND LCR_DATA_SIZE - 5 // 1 byte command followed by 4 bytes of data

typedef enum {
	LCR_DATA_REG_DATA = 0x00,
	LCR_DATA_REG_INITIAL = 0x01
} LCR_Data_RegisterTypeDef;

typedef enum {
	LCR_DATA_RESET = 0x01,
	LCR_DATA_STORE = 0x02
} LCR_Data_CommandTypeDef;

extern uint8_t data[LCR_DATA_SIZE];
extern uint8_t initial[LCR_DATA_SIZE];

void LCR_Data_Initialize();
void LCR_Data_Reset();
void LCR_Data_Store();
void LCR_Data_HandleData();

uint8_t *LCR_Data_GetDataArrayReference();

uint8_t LCR_Data_SetInitialized(uint8_t initialized);
uint8_t LCR_Data_SetInitialInitialized(uint8_t initialized);
uint8_t LCR_Data_IsInitialized();
uint8_t *LCR_Data_GetInitializedReference();

uint8_t LCR_Data_SetDevID(uint8_t device_id);
uint8_t LCR_Data_SetInitialDevID(uint8_t device_id);
uint8_t LCR_Data_GetDevID();
uint8_t *LCR_Data_GetDevIDReference();
uint8_t LCR_Data_SetMemsID(uint8_t mems_id);
uint8_t LCR_Data_SetInitialMemsID(uint8_t device_id);
uint8_t LCR_Data_GetMemsID();
uint8_t *LCR_Data_GetMemsIDReference();
uint8_t LCR_Data_SetPartID(uint8_t part_id);
uint8_t LCR_Data_SetInitialPartID(uint8_t part_id);
uint8_t LCR_Data_GetPartID();
uint8_t *LCR_Data_GetPartIDReference();
uint8_t LCR_Data_SetMemoryAddress(uint8_t mem_address);
uint8_t LCR_Data_SetInitialMemoryAddress(uint8_t mem_address);
uint8_t LCR_Data_GetMemoryAddress();
uint8_t *LCR_Data_GetMemoryAddressReference();
uint8_t LCR_Data_SetStartingMemoryAddress(uint8_t mem_address);
uint8_t LCR_Data_SetInitialStartingMemoryAddress(uint8_t mem_address);
uint8_t LCR_Data_GetStartingMemoryAddress();
uint8_t *LCR_Data_GetStartingMemoryAddressReference();
uint8_t LCR_Data_SetDEResistance(uint32_t resistance);
uint8_t LCR_Data_SetInitialDEResistance(uint32_t resistance);
uint32_t LCR_Data_GetDEResistance();
uint32_t *LCR_Data_GetDEResistanceReference();
uint8_t LCR_Data_SetDECapacitance(uint32_t capacitance);
uint8_t LCR_Data_SetInitialDECapacitance(uint32_t capacitance);
uint32_t LCR_Data_GetDECapacitance();
uint32_t *LCR_Data_GetDECapacitanceReference();
uint8_t LCR_Data_SetMinMeasurementVoltage(uint16_t voltage);
uint8_t LCR_Data_SetInitialMinMeasurementVoltage(uint16_t voltage);
uint16_t LCR_Data_GetMinMeasurementVoltage();
uint16_t *LCR_Data_GetMinMeasurementVoltageReference();
uint8_t LCR_Data_SetMaxMeasurementVoltage(uint16_t voltage);
uint8_t LCR_Data_SetInitialMaxMeasurementVoltage(uint16_t voltage);
uint16_t LCR_Data_GetMaxMeasurementVoltage();
uint16_t *LCR_Data_GetMaxMeasurementVoltageReference();
uint8_t LCR_Data_SetMeasurementFrequency(uint16_t frequency);
uint8_t LCR_Data_SetInitialMeasurementFrequency(uint16_t frequency);
uint16_t LCR_Data_GetMeasurementFrequency();
uint16_t *LCR_Data_GetMeasurementFrequencyReference();

void * __LCR_Data_GetDataReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address);
uint32_t *__LCR_Data_GetWordReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address);
uint16_t *__LCR_Data_GetHalfWordReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address);
uint8_t *__LCR_Data_GetByteReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address);

uint32_t __LCR_Data_GetWord(LCR_Data_RegisterTypeDef reg_type, uint8_t address);
uint16_t __LCR_Data_GetHalfWord(LCR_Data_RegisterTypeDef reg_type, uint8_t address);
uint8_t __LCR_Data_GetByte(LCR_Data_RegisterTypeDef reg_type, uint8_t address);

uint8_t __LCR_Data_SetData(LCR_Data_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address);
uint8_t __LCR_Data_SetWord(LCR_Data_RegisterTypeDef reg_type, uint32_t value, uint8_t address);
uint8_t __LCR_Data_SetHalfWord(LCR_Data_RegisterTypeDef reg_type, uint16_t value, uint8_t address);
uint8_t __LCR_Data_SetByte(LCR_Data_RegisterTypeDef reg_type, uint8_t value, uint8_t address);

#endif /* INC_LCR_DATA_H */
