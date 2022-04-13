/*
 * LCR_Data.c
 *
 *  Created on: 29.09.2021
 *      Author: Tim Goll
 */

#include "LCR_Data.h"

uint8_t data[LCR_DATA_SIZE] = {0};
uint8_t initial[LCR_DATA_SIZE] = {0};

void LCR_Data_Initialize() {
	// first read data from flash and put it into the data array
	for (uint8_t i = 0; i < LCR_DATA_SIZE / 4; i++) {
		__LCR_Data_SetWord(LCR_DATA_REG_DATA, Flash_ReadWord(LCR_DATA_FLASH_ADDRESS + i * 4), i * 4);
	}

	// only set default values to main memory if not already initialized
	if (LCR_Data_IsInitialized() == 1) {
		return;
	}

	LCR_Data_Reset();
}

void LCR_Data_Reset() {
	for (uint16_t i = 0; i < LCR_DATA_SIZE; i++) {
		data[i] = initial[i];
	}
}

void LCR_Data_Store() {
	Flash_ClearSector(LCR_DATA_FLASH_ADDRESS, 1);

	// one flash word has the size of 256 bits, we have a memory size of 256 bytes here
	// this means that our memory has to be divided into 8 flash words
	for (uint8_t i = 0; i < LCR_DATA_SIZE / FLASH_WORD_SIZE; i++) {
		Flash_SafeWriteFlashWord(LCR_DATA_FLASH_ADDRESS + i * FLASH_WORD_SIZE, (uint32_t *) &data[i * FLASH_WORD_SIZE]);
	}
}

void LCR_Data_HandleData() {
	// check if a new command byte was set in the register
	uint8_t command_byte = __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_COMMAND);

	// reset the command byte to 0x00, this should happen before the commands
	// itself are used so that the command itself is never stored to memory
	__LCR_Data_SetByte(LCR_DATA_REG_DATA, 0x00, LCR_DATA_REG_COMMAND);

	switch(command_byte) {
		case LCR_DATA_RESET:
			LCR_Data_Reset();
		case LCR_DATA_STORE:
			LCR_Data_Store();
		default:
			return;
	}

	// reset the command byte to 0x00
	__LCR_Data_SetByte(LCR_DATA_REG_DATA, 0x00, LCR_DATA_REG_COMMAND);
}

uint8_t *LCR_Data_GetDataArrayReference() {
	return &data[0];
}

/* Shortcut functions to directly access the data */

// INITIALIZED //

uint8_t LCR_Data_SetInitialized(uint8_t initialized) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, initialized, LCR_DATA_REG_INITIALIZED);
}

uint8_t LCR_Data_SetInitialInitialized(uint8_t initialized) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, initialized, LCR_DATA_REG_INITIALIZED);
}

uint8_t LCR_Data_IsInitialized() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_INITIALIZED);
}

uint8_t *LCR_Data_GetInitializedReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_INITIALIZED);
}

// DEVELOPER ID //

uint8_t LCR_Data_SetDevID(uint8_t device_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, device_id, LCR_DATA_REG_DEVID);
}

uint8_t LCR_Data_SetInitialDevID(uint8_t device_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, device_id, LCR_DATA_REG_DEVID);
}

uint8_t LCR_Data_GetDevID() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_DEVID);
}

uint8_t *LCR_Data_GetDevIDReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DEVID);
}

// MEMS ID //

uint8_t LCR_Data_SetMemsID(uint8_t mems_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, mems_id, LCR_DATA_REG_MEMSID);
}

uint8_t LCR_Data_SetInitialMemsID(uint8_t mems_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, mems_id, LCR_DATA_REG_MEMSID);
}

uint8_t LCR_Data_GetMemsID() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEMSID);
}

uint8_t *LCR_Data_GetMemsIDReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEMSID);
}

// PART ID //

uint8_t LCR_Data_SetPartID(uint8_t part_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, part_id, LCR_DATA_REG_PARTID);
}

uint8_t LCR_Data_SetInitialPartID(uint8_t part_id) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, part_id, LCR_DATA_REG_PARTID);
}

uint8_t LCR_Data_GetPartID() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_PARTID);
}

uint8_t *LCR_Data_GetPartIDReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_PARTID);
}

// MEMORY ADDRESS //

uint8_t LCR_Data_SetMemoryAddress(uint8_t mem_address) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, mem_address, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t LCR_Data_SetInitialMemoryAddress(uint8_t mem_address) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, mem_address, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t LCR_Data_GetMemoryAddress() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t *LCR_Data_GetMemoryAddressReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS);
}

// STARTING MEMORY ADDRESS //

uint8_t LCR_Data_SetStartingMemoryAddress(uint8_t mem_address) {
	return __LCR_Data_SetByte(LCR_DATA_REG_DATA, mem_address, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t LCR_Data_SetInitialStartingMemoryAddress(uint8_t mem_address) {
	return __LCR_Data_SetByte(LCR_DATA_REG_INITIAL, mem_address, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t LCR_Data_GetStartingMemoryAddress() {
	return __LCR_Data_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t *LCR_Data_GetStartingMemoryAddressReference() {
	return __LCR_Data_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS_START);
}

// DE RESISTANCE //

uint8_t LCR_Data_SetDEResistance(uint32_t resistance) {
	return __LCR_Data_SetWord(LCR_DATA_REG_DATA, resistance, LCR_DATA_REG_RESISTANCE);
}

uint8_t LCR_Data_SetInitialDEResistance(uint32_t resistance) {
	return __LCR_Data_SetWord(LCR_DATA_REG_INITIAL, resistance, LCR_DATA_REG_RESISTANCE);
}

uint32_t LCR_Data_GetDEResistance() {
	return __LCR_Data_GetWord(LCR_DATA_REG_DATA, LCR_DATA_REG_RESISTANCE);
}

uint32_t *LCR_Data_GetDEResistanceReference() {
	return __LCR_Data_GetWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_RESISTANCE);
}

// DE CAPACITANCE //

uint8_t LCR_Data_SetDECapacitance(uint32_t capacitance) {
	return __LCR_Data_SetWord(LCR_DATA_REG_DATA, capacitance, LCR_DATA_REG_CAPACITANCE);
}

uint8_t LCR_Data_SetInitialDECapacitance(uint32_t capacitance) {
	return __LCR_Data_SetWord(LCR_DATA_REG_INITIAL, capacitance, LCR_DATA_REG_CAPACITANCE);
}

uint32_t LCR_Data_GetDECapacitance() {
	return __LCR_Data_GetWord(LCR_DATA_REG_DATA, LCR_DATA_REG_CAPACITANCE);
}

uint32_t *LCR_Data_GetDECapacitanceReference() {
	return __LCR_Data_GetWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_CAPACITANCE);
}

// MEASUREMENT SIGNAL MIN VOLTAGE //

uint8_t LCR_Data_SetMinMeasurementVoltage(uint16_t voltage) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_DATA, voltage, LCR_DATA_REG_MES_VOLT_MIN);
}

uint8_t LCR_Data_SetInitialMinMeasurementVoltage(uint16_t voltage) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_INITIAL, voltage, LCR_DATA_REG_MES_VOLT_MIN);
}

uint16_t LCR_Data_GetMinMeasurementVoltage() {
	return __LCR_Data_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MIN);
}

uint16_t *LCR_Data_GetMinMeasurementVoltageReference() {
	return __LCR_Data_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MIN);
}

// MEASUREMENT SIGNAL MAX VOLTAGE //

uint8_t LCR_Data_SetMaxMeasurementVoltage(uint16_t voltage) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_DATA, voltage, LCR_DATA_REG_MES_VOLT_MAX);
}

uint8_t LCR_Data_SetInitialMaxMeasurementVoltage(uint16_t voltage) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_INITIAL, voltage, LCR_DATA_REG_MES_VOLT_MAX);
}

uint16_t LCR_Data_GetMaxMeasurementVoltage() {
	return __LCR_Data_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MAX);
}

uint16_t *LCR_Data_GetMaxMeasurementVoltageReference() {
	return __LCR_Data_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MAX);
}

// MEASUREMENT SIGNAL FREQUENCY //

uint8_t LCR_Data_SetMeasurementFrequency(uint16_t frequency) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_DATA, frequency, LCR_DATA_REG_MES_FREQ);
}

uint8_t LCR_Data_SetInitialMeasurementFrequency(uint16_t frequency) {
	return __LCR_Data_SetHalfWord(LCR_DATA_REG_INITIAL, frequency, LCR_DATA_REG_MES_FREQ);
}

uint16_t LCR_Data_GetMeasurementFrequency() {
	return __LCR_Data_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_FREQ);
}

uint16_t *LCR_Data_GetMeasurementFrequencyReference() {
	return __LCR_Data_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_FREQ);
}






/* Internal functions that do the byte-work */

void * __LCR_Data_GetDataReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	if (reg_type == LCR_DATA_REG_DATA) {
		return (void *) &data[address];
	} else if (reg_type == LCR_DATA_REG_INITIAL) {
		return (void *) &initial[address];
	} else {
		return NULL;
	}
}

uint32_t *__LCR_Data_GetWordReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return (uint32_t *) __LCR_Data_GetDataReference(reg_type, address);
}

uint16_t *__LCR_Data_GetHalfWordReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return (uint16_t *) __LCR_Data_GetDataReference(reg_type, address);
}

uint8_t *__LCR_Data_GetByteReference(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return (uint8_t *) __LCR_Data_GetDataReference(reg_type, address);
}

uint32_t __LCR_Data_GetWord(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCR_Data_GetWordReference(reg_type, address);
}

uint16_t __LCR_Data_GetHalfWord(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCR_Data_GetHalfWordReference(reg_type, address);
}

uint8_t __LCR_Data_GetByte(LCR_Data_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCR_Data_GetByteReference(reg_type, address);
}

uint8_t __LCR_Data_SetData(LCR_Data_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address) {
	uint8_t *ref;

	if (reg_type == LCR_DATA_REG_DATA) {
		ref = data;
	} else if (reg_type == LCR_DATA_REG_INITIAL) {
		ref = initial;
	} else {
		return 0;
	}

	if (address + length > LCR_DATA_SIZE) {
		return 0;
	}

	uint8_t *byte_array = (uint8_t *) value;

	for (uint8_t i = 0; i < length; i++) {
		ref[address + i] = byte_array[i];
	}

	return 1;
}

uint8_t __LCR_Data_SetWord(LCR_Data_RegisterTypeDef reg_type, uint32_t value, uint8_t address) {
	return __LCR_Data_SetData(reg_type, (void *) &value, 4, address);
}

uint8_t __LCR_Data_SetHalfWord(LCR_Data_RegisterTypeDef reg_type, uint16_t value, uint8_t address) {
	return __LCR_Data_SetData(reg_type, (void *) &value, 2, address);
}

uint8_t __LCR_Data_SetByte(LCR_Data_RegisterTypeDef reg_type, uint8_t value, uint8_t address) {
	return __LCR_Data_SetData(reg_type, (void *) &value, 1, address);
}
