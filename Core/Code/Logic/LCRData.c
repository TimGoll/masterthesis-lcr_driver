#include "LCRData.h"

uint8_t data[LCR_DATA_SIZE] = {0};
uint8_t initial[LCR_DATA_SIZE] = {0};

void LCRData_Initialize() {
	// first read data from flash and put it into the data array
	for (uint8_t i = 0; i < LCR_DATA_SIZE / 4; i++) {
		__LCRData_SetWord(LCR_DATA_REG_DATA, Flash_ReadWord(LCR_DATA_FLASH_ADDRESS + i * 4), i * 4);
	}

	// only set default values to main memory if not already initialized
	if (LCRData_IsInitialized() == 1) {
		return;
	}

	LCRData_Reset();
}

void LCRData_Reset() {
	for (uint16_t i = 0; i < LCR_DATA_SIZE; i++) {
		data[i] = initial[i];
	}
}

void LCRData_Store() {
	Flash_ClearSector(LCR_DATA_FLASH_ADDRESS, 1);

	// one flash word has the size of 256 bits, we have a memory size of 256 bytes here
	// this means that our memory has to be divided into 8 flash words
	for (uint8_t i = 0; i < LCR_DATA_SIZE / FLASH_WORD_SIZE; i++) {
		Flash_SafeWriteFlashWord(LCR_DATA_FLASH_ADDRESS + i * FLASH_WORD_SIZE, (uint32_t *) &data[i * FLASH_WORD_SIZE]);
	}
}

void LCRData_HandleData() {
	// check if a new command byte was set in the register
	uint8_t command_byte = __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_COMMAND);

	// reset the command byte to 0x00, this should happen before the commands
	// itself are used so that the command itself is never stored to memory
	__LCRData_SetByte(LCR_DATA_REG_DATA, 0x00, LCR_DATA_REG_COMMAND);

	switch(command_byte) {
		case LCR_DATA_RESET:
			LCRData_Reset();
		case LCR_DATA_STORE:
			LCRData_Store();
		default:
			return;
	}

	// reset the command byte to 0x00
	__LCRData_SetByte(LCR_DATA_REG_DATA, 0x00, LCR_DATA_REG_COMMAND);
}

uint8_t *LCRData_GetDataArrayReference() {
	return &data[0];
}

/* Shortcut functions to directly access the data */

// INITIALIZED //

uint8_t LCRData_SetInitialized(uint8_t initialized) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, initialized, LCR_DATA_REG_INITIALIZED);
}

uint8_t LCRData_SetInitialInitialized(uint8_t initialized) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, initialized, LCR_DATA_REG_INITIALIZED);
}

uint8_t LCRData_IsInitialized() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_INITIALIZED);
}

uint8_t *LCRData_GetInitializedReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_INITIALIZED);
}

// DEVELOPER ID //

uint8_t LCRData_SetDevID(uint8_t device_id) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, device_id, LCR_DATA_REG_DEVID);
}

uint8_t LCRData_SetInitialDevID(uint8_t device_id) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, device_id, LCR_DATA_REG_DEVID);
}

uint8_t LCRData_GetDevID() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_DEVID);
}

uint8_t *LCRData_GetDevIDReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DEVID);
}

// MEMS ID //

uint8_t LCRData_SetMemsID(uint8_t mems_id) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, mems_id, LCR_DATA_REG_MEMSID);
}

uint8_t LCRData_SetInitialMemsID(uint8_t mems_id) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, mems_id, LCR_DATA_REG_MEMSID);
}

uint8_t LCRData_GetMemsID() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEMSID);
}

uint8_t *LCRData_GetMemsIDReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEMSID);
}

// PART ID //

uint8_t LCRData_SetPartID(uint8_t part_id) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, part_id, LCR_DATA_REG_PARTID);
}

uint8_t LCRData_SetInitialPartID(uint8_t part_id) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, part_id, LCR_DATA_REG_PARTID);
}

uint8_t LCRData_GetPartID() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_PARTID);
}

uint8_t *LCRData_GetPartIDReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_PARTID);
}

// MEMORY ADDRESS //

uint8_t LCRData_SetMemoryAddress(uint8_t mem_address) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, mem_address, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t LCRData_SetInitialMemoryAddress(uint8_t mem_address) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, mem_address, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t LCRData_GetMemoryAddress() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS);
}

uint8_t *LCRData_GetMemoryAddressReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS);
}

// STARTING MEMORY ADDRESS //

uint8_t LCRData_SetStartingMemoryAddress(uint8_t mem_address) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, mem_address, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t LCRData_SetInitialStartingMemoryAddress(uint8_t mem_address) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, mem_address, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t LCRData_GetStartingMemoryAddress() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS_START);
}

uint8_t *LCRData_GetStartingMemoryAddressReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MEM_ADDRESS_START);
}

// MEASUREMENT SIGNAL MIN VOLTAGE //

uint8_t LCRData_SetMinMeasurementVoltage(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, voltage, LCR_DATA_REG_MES_VOLT_MIN);
}

uint8_t LCRData_SetInitialMinMeasurementVoltage(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, voltage, LCR_DATA_REG_MES_VOLT_MIN);
}

uint16_t LCRData_GetMinMeasurementVoltage() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MIN);
}

uint16_t *LCRData_GetMinMeasurementVoltageReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MIN);
}

// MEASUREMENT SIGNAL MAX VOLTAGE //

uint8_t LCRData_SetMaxMeasurementVoltage(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, voltage, LCR_DATA_REG_MES_VOLT_MAX);
}

uint8_t LCRData_SetInitialMaxMeasurementVoltage(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, voltage, LCR_DATA_REG_MES_VOLT_MAX);
}

uint16_t LCRData_GetMaxMeasurementVoltage() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MAX);
}

uint16_t *LCRData_GetMaxMeasurementVoltageReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_VOLT_MAX);
}

// MEASUREMENT SIGNAL FREQUENCY //

uint8_t LCRData_SetMeasurementFrequency(uint16_t frequency) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, frequency, LCR_DATA_REG_MES_FREQ);
}

uint8_t LCRData_SetInitialMeasurementFrequency(uint16_t frequency) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, frequency, LCR_DATA_REG_MES_FREQ);
}

uint16_t LCRData_GetMeasurementFrequency() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_FREQ);
}

uint16_t *LCRData_GetMeasurementFrequencyReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_MES_FREQ);
}

// DE MODEL //

uint8_t LCRData_SetDEModel(uint8_t model) {
	return __LCRData_SetByte(LCR_DATA_REG_DATA, model, LCR_DATA_REG_DE_MODEL);
}

uint8_t LCRData_SetInitialDEModel(uint8_t model) {
	return __LCRData_SetByte(LCR_DATA_REG_INITIAL, model, LCR_DATA_REG_DE_MODEL);
}

uint8_t LCRData_GetDEModel() {
	return __LCRData_GetByte(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_MODEL);
}

uint8_t *LCRData_GetDEModelReference() {
	return __LCRData_GetByteReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_MODEL);
}





// DE RESISTANCE //

uint8_t LCRData_SetDEResistance(uint16_t resistance) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, resistance, LCR_DATA_REG_DE_RESISTANCE);
}

uint8_t LCRData_SetInitialDEResistance(uint16_t resistance) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, resistance, LCR_DATA_REG_DE_RESISTANCE);
}

uint16_t LCRData_GetDEResistance() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_RESISTANCE);
}

uint16_t *LCRData_GetDEResistanceReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_RESISTANCE);
}

// DE CAPACITANCE //

uint8_t LCRData_SetDECapacitance(uint16_t capacitance) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, capacitance, LCR_DATA_REG_DE_CAPACITANCE);
}

uint8_t LCRData_SetInitialDECapacitance(uint16_t capacitance) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, capacitance, LCR_DATA_REG_DE_CAPACITANCE);
}

uint16_t LCRData_GetDECapacitance() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_CAPACITANCE);
}

uint16_t *LCRData_GetDECapacitanceReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_CAPACITANCE);
}

// DE PHASE //

uint8_t LCRData_SetDEPhase(uint16_t phase) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, phase, LCR_DATA_REG_DE_PHASE);
}

uint8_t LCRData_SetInitialDEPhase(uint16_t phase) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, phase, LCR_DATA_REG_DE_PHASE);
}

uint16_t LCRData_GetDEPhase() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_PHASE);
}

uint16_t *CurrentMagnitude() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_PHASE);
}

// DE VOLTAGE MAGNITUDE //

uint8_t LCRData_SetDEVoltageMagnitude(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, voltage, LCR_DATA_REG_DE_VOLTAGE_MAG);
}

uint8_t LCRData_SetInitialDEVoltageMagnitude(uint16_t voltage) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, voltage, LCR_DATA_REG_DE_VOLTAGE_MAG);
}

uint16_t LCRData_GetDEVoltageMagnitude() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_VOLTAGE_MAG);
}

uint16_t *LCRData_GetDEVoltageMagnitudeReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_VOLTAGE_MAG);
}

// DE CURRENT MAGNITUDE //

uint8_t LCRData_SetDECurrentMagnitude(uint16_t current) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_DATA, current, LCR_DATA_REG_DE_CURRENT_MAG);
}

uint8_t LCRData_SetInitialDECurrentMagnitude(uint16_t current) {
	return __LCRData_SetHalfWord(LCR_DATA_REG_INITIAL, current, LCR_DATA_REG_DE_CURRENT_MAG);
}

uint16_t LCRData_GetDECurrentMagnitude() {
	return __LCRData_GetHalfWord(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_CURRENT_MAG);
}

uint16_t *LCRData_GetDECurrentMagnitudeReference() {
	return __LCRData_GetHalfWordReference(LCR_DATA_REG_DATA, LCR_DATA_REG_DE_CURRENT_MAG);
}





/* Internal functions that do the byte-work */

void * __LCRData_GetDataReference(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	if (reg_type == LCR_DATA_REG_DATA) {
		return (void *) &data[address];
	} else if (reg_type == LCR_DATA_REG_INITIAL) {
		return (void *) &initial[address];
	} else {
		return NULL;
	}
}

uint32_t *__LCRData_GetWordReference(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint32_t *) __LCRData_GetDataReference(reg_type, address);
}

uint16_t *__LCRData_GetHalfWordReference(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint16_t *) __LCRData_GetDataReference(reg_type, address);
}

uint8_t *__LCRData_GetByteReference(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint8_t *) __LCRData_GetDataReference(reg_type, address);
}

uint32_t __LCRData_GetWord(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCRData_GetWordReference(reg_type, address);
}

uint16_t __LCRData_GetHalfWord(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCRData_GetHalfWordReference(reg_type, address);
}

uint8_t __LCRData_GetByte(LCRData_RegisterTypeDef reg_type, uint8_t address) {
	return *__LCRData_GetByteReference(reg_type, address);
}

uint8_t __LCRData_SetData(LCRData_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address) {
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

uint8_t __LCRData_SetWord(LCRData_RegisterTypeDef reg_type, uint32_t value, uint8_t address) {
	return __LCRData_SetData(reg_type, (void *) &value, 4, address);
}

uint8_t __LCRData_SetHalfWord(LCRData_RegisterTypeDef reg_type, uint16_t value, uint8_t address) {
	return __LCRData_SetData(reg_type, (void *) &value, 2, address);
}

uint8_t __LCRData_SetByte(LCRData_RegisterTypeDef reg_type, uint8_t value, uint8_t address) {
	return __LCRData_SetData(reg_type, (void *) &value, 1, address);
}
