#include "CoreData.h"

uint8_t data[COREDATA_SIZE] = {0};
uint8_t initial[COREDATA_SIZE] = {0};

void CoreData_Initialize() {
	// first read data from flash and put it into the data array
	for (uint8_t i = 0; i < COREDATA_SIZE / 4; i++) {
		__CoreData_SetWord(COREDATA_REG_DATA, Flash_ReadWord(COREDATA_FLASH_ADDRESS + i * 4), i * 4);
	}

	// only set default values to main memory if not already initialized
	if (CoreData_IsInitialized() == 1) {
		return;
	}

	CoreData_Reset();
}

void CoreData_Reset() {
	for (uint16_t i = 0; i < COREDATA_SIZE; i++) {
		data[i] = initial[i];
	}
}

void CoreData_Store() {
	Flash_ClearSector(COREDATA_FLASH_ADDRESS, 1);

	// one flash word has the size of 256 bits, we have a memory size of 256 bytes here
	// this means that our memory has to be divided into 8 flash words
	for (uint8_t i = 0; i < COREDATA_SIZE / FLASH_WORD_SIZE; i++) {
		Flash_SafeWriteFlashWord(COREDATA_FLASH_ADDRESS + i * FLASH_WORD_SIZE, (uint32_t *) &data[i * FLASH_WORD_SIZE]);
	}
}

void CoreData_HandleData() {
	// check if a new command byte was set in the register
	uint8_t command_byte = __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_COMMAND);

	// reset the command byte to 0x00, this should happen before the commands
	// itself are used so that the command itself is never stored to memory
	__CoreData_SetByte(COREDATA_REG_DATA, 0x00, COREDATA_REG_COMMAND);

	switch(command_byte) {
		case COREDATA_RESET:
			CoreData_Reset();
		case COREDATA_STORE:
			CoreData_Store();
		default:
			return;
	}

	// reset the command byte to 0x00
	__CoreData_SetByte(COREDATA_REG_DATA, 0x00, COREDATA_REG_COMMAND);
}

uint8_t *CoreData_GetDataArrayReference() {
	return &data[0];
}

/* Shortcut functions to directly access the data */

// INITIALIZED //

uint8_t CoreData_SetInitialized(uint8_t initialized) {
	return __CoreData_SetByte(COREDATA_REG_DATA, initialized, COREDATA_REG_INITIALIZED);
}

uint8_t CoreData_SetInitialInitialized(uint8_t initialized) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, initialized, COREDATA_REG_INITIALIZED);
}

uint8_t CoreData_IsInitialized() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_INITIALIZED);
}

uint8_t *CoreData_GetInitializedReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_INITIALIZED);
}

// DEVELOPER ID //

uint8_t CoreData_SetDevID(uint8_t device_id) {
	return __CoreData_SetByte(COREDATA_REG_DATA, device_id, COREDATA_REG_DEVID);
}

uint8_t CoreData_SetInitialDevID(uint8_t device_id) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, device_id, COREDATA_REG_DEVID);
}

uint8_t CoreData_GetDevID() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_DEVID);
}

uint8_t *CoreData_GetDevIDReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_DEVID);
}

// MEMS ID //

uint8_t CoreData_SetMemsID(uint8_t mems_id) {
	return __CoreData_SetByte(COREDATA_REG_DATA, mems_id, COREDATA_REG_MEMSID);
}

uint8_t CoreData_SetInitialMemsID(uint8_t mems_id) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, mems_id, COREDATA_REG_MEMSID);
}

uint8_t CoreData_GetMemsID() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_MEMSID);
}

uint8_t *CoreData_GetMemsIDReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_MEMSID);
}

// PART ID //

uint8_t CoreData_SetPartID(uint8_t part_id) {
	return __CoreData_SetByte(COREDATA_REG_DATA, part_id, COREDATA_REG_PARTID);
}

uint8_t CoreData_SetInitialPartID(uint8_t part_id) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, part_id, COREDATA_REG_PARTID);
}

uint8_t CoreData_GetPartID() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_PARTID);
}

uint8_t *CoreData_GetPartIDReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_PARTID);
}

// MEMORY ADDRESS //

uint8_t CoreData_SetMemoryAddress(uint8_t mem_address) {
	return __CoreData_SetByte(COREDATA_REG_DATA, mem_address, COREDATA_REG_MEM_ADDRESS);
}

uint8_t CoreData_SetInitialMemoryAddress(uint8_t mem_address) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, mem_address, COREDATA_REG_MEM_ADDRESS);
}

uint8_t CoreData_GetMemoryAddress() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_MEM_ADDRESS);
}

uint8_t *CoreData_GetMemoryAddressReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_MEM_ADDRESS);
}

// STARTING MEMORY ADDRESS //

uint8_t CoreData_SetStartingMemoryAddress(uint8_t mem_address) {
	return __CoreData_SetByte(COREDATA_REG_DATA, mem_address, COREDATA_REG_MEM_ADDRESS_START);
}

uint8_t CoreData_SetInitialStartingMemoryAddress(uint8_t mem_address) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, mem_address, COREDATA_REG_MEM_ADDRESS_START);
}

uint8_t CoreData_GetStartingMemoryAddress() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_MEM_ADDRESS_START);
}

uint8_t *CoreData_GetStartingMemoryAddressReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_MEM_ADDRESS_START);
}

// MEASUREMENT SIGNAL MIN VOLTAGE //

uint8_t CoreData_SetMinMeasurementVoltage(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, voltage, COREDATA_REG_MES_VOLT_MIN);
}

uint8_t CoreData_SetInitialMinMeasurementVoltage(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, voltage, COREDATA_REG_MES_VOLT_MIN);
}

uint16_t CoreData_GetMinMeasurementVoltage() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_MES_VOLT_MIN);
}

uint16_t *CoreData_GetMinMeasurementVoltageReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_MES_VOLT_MIN);
}

// MEASUREMENT SIGNAL MAX VOLTAGE //

uint8_t CoreData_SetMaxMeasurementVoltage(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, voltage, COREDATA_REG_MES_VOLT_MAX);
}

uint8_t CoreData_SetInitialMaxMeasurementVoltage(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, voltage, COREDATA_REG_MES_VOLT_MAX);
}

uint16_t CoreData_GetMaxMeasurementVoltage() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_MES_VOLT_MAX);
}

uint16_t *CoreData_GetMaxMeasurementVoltageReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_MES_VOLT_MAX);
}

// MEASUREMENT SIGNAL FREQUENCY //

uint8_t CoreData_SetMeasurementFrequency(uint16_t frequency) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, frequency, COREDATA_REG_MES_FREQ);
}

uint8_t CoreData_SetInitialMeasurementFrequency(uint16_t frequency) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, frequency, COREDATA_REG_MES_FREQ);
}

uint16_t CoreData_GetMeasurementFrequency() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_MES_FREQ);
}

uint16_t *CoreData_GetMeasurementFrequencyReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_MES_FREQ);
}

// DE MODEL //

uint8_t CoreData_SetDEModel(uint8_t model) {
	return __CoreData_SetByte(COREDATA_REG_DATA, model, COREDATA_REG_DE_MODEL);
}

uint8_t CoreData_SetInitialDEModel(uint8_t model) {
	return __CoreData_SetByte(COREDATA_REG_INITIAL, model, COREDATA_REG_DE_MODEL);
}

uint8_t CoreData_GetDEModel() {
	return __CoreData_GetByte(COREDATA_REG_DATA, COREDATA_REG_DE_MODEL);
}

uint8_t *CoreData_GetDEModelReference() {
	return __CoreData_GetByteReference(COREDATA_REG_DATA, COREDATA_REG_DE_MODEL);
}





// DE RESISTANCE //

uint8_t CoreData_SetDEResistance(uint16_t resistance) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, resistance, COREDATA_REG_DE_RESISTANCE);
}

uint8_t CoreData_SetInitialDEResistance(uint16_t resistance) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, resistance, COREDATA_REG_DE_RESISTANCE);
}

uint16_t CoreData_GetDEResistance() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_DE_RESISTANCE);
}

uint16_t *CoreData_GetDEResistanceReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_DE_RESISTANCE);
}

// DE CAPACITANCE //

uint8_t CoreData_SetDECapacitance(uint16_t capacitance) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, capacitance, COREDATA_REG_DE_CAPACITANCE);
}

uint8_t CoreData_SetInitialDECapacitance(uint16_t capacitance) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, capacitance, COREDATA_REG_DE_CAPACITANCE);
}

uint16_t CoreData_GetDECapacitance() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_DE_CAPACITANCE);
}

uint16_t *CoreData_GetDECapacitanceReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_DE_CAPACITANCE);
}

// DE PHASE //

uint8_t CoreData_SetDEPhase(uint16_t phase) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, phase, COREDATA_REG_DE_PHASE);
}

uint8_t CoreData_SetInitialDEPhase(uint16_t phase) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, phase, COREDATA_REG_DE_PHASE);
}

uint16_t CoreData_GetDEPhase() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_DE_PHASE);
}

uint16_t *CurrentMagnitude() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_DE_PHASE);
}

// DE VOLTAGE MAGNITUDE //

uint8_t CoreData_SetDEVoltageMagnitude(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, voltage, COREDATA_REG_DE_VOLTAGE_MAG);
}

uint8_t CoreData_SetInitialDEVoltageMagnitude(uint16_t voltage) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, voltage, COREDATA_REG_DE_VOLTAGE_MAG);
}

uint16_t CoreData_GetDEVoltageMagnitude() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_DE_VOLTAGE_MAG);
}

uint16_t *CoreData_GetDEVoltageMagnitudeReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_DE_VOLTAGE_MAG);
}

// DE CURRENT MAGNITUDE //

uint8_t CoreData_SetDECurrentMagnitude(uint16_t current) {
	return __CoreData_SetHalfWord(COREDATA_REG_DATA, current, COREDATA_REG_DE_CURRENT_MAG);
}

uint8_t CoreData_SetInitialDECurrentMagnitude(uint16_t current) {
	return __CoreData_SetHalfWord(COREDATA_REG_INITIAL, current, COREDATA_REG_DE_CURRENT_MAG);
}

uint16_t CoreData_GetDECurrentMagnitude() {
	return __CoreData_GetHalfWord(COREDATA_REG_DATA, COREDATA_REG_DE_CURRENT_MAG);
}

uint16_t *CoreData_GetDECurrentMagnitudeReference() {
	return __CoreData_GetHalfWordReference(COREDATA_REG_DATA, COREDATA_REG_DE_CURRENT_MAG);
}





/* Internal functions that do the byte-work */

void * __CoreData_GetDataReference(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	if (reg_type == COREDATA_REG_DATA) {
		return (void *) &data[address];
	} else if (reg_type == COREDATA_REG_INITIAL) {
		return (void *) &initial[address];
	} else {
		return NULL;
	}
}

uint32_t *__CoreData_GetWordReference(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint32_t *) __CoreData_GetDataReference(reg_type, address);
}

uint16_t *__CoreData_GetHalfWordReference(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint16_t *) __CoreData_GetDataReference(reg_type, address);
}

uint8_t *__CoreData_GetByteReference(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return (uint8_t *) __CoreData_GetDataReference(reg_type, address);
}

uint32_t __CoreData_GetWord(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return *__CoreData_GetWordReference(reg_type, address);
}

uint16_t __CoreData_GetHalfWord(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return *__CoreData_GetHalfWordReference(reg_type, address);
}

uint8_t __CoreData_GetByte(CoreData_RegisterTypeDef reg_type, uint8_t address) {
	return *__CoreData_GetByteReference(reg_type, address);
}

uint8_t __CoreData_SetData(CoreData_RegisterTypeDef reg_type, void *value, uint8_t length, uint8_t address) {
	uint8_t *ref;

	if (reg_type == COREDATA_REG_DATA) {
		ref = data;
	} else if (reg_type == COREDATA_REG_INITIAL) {
		ref = initial;
	} else {
		return 0;
	}

	if (address + length > COREDATA_SIZE) {
		return 0;
	}

	uint8_t *byte_array = (uint8_t *) value;

	for (uint8_t i = 0; i < length; i++) {
		ref[address + i] = byte_array[i];
	}

	return 1;
}

uint8_t __CoreData_SetWord(CoreData_RegisterTypeDef reg_type, uint32_t value, uint8_t address) {
	return __CoreData_SetData(reg_type, (void *) &value, 4, address);
}

uint8_t __CoreData_SetHalfWord(CoreData_RegisterTypeDef reg_type, uint16_t value, uint8_t address) {
	return __CoreData_SetData(reg_type, (void *) &value, 2, address);
}

uint8_t __CoreData_SetByte(CoreData_RegisterTypeDef reg_type, uint8_t value, uint8_t address) {
	return __CoreData_SetData(reg_type, (void *) &value, 1, address);
}
