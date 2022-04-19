#include "Flash.h"

Flash_CacheElement flashCache[32];
uint8_t flashCounter = 0;

HAL_StatusTypeDef Flash_ClearSector(uint32_t startingAddress, uint8_t amount) {
	FLASH_EraseInitTypeDef eraseInit;

	eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	eraseInit.NbSectors = amount;
	eraseInit.Banks = __Flash_GetBank(startingAddress);
	eraseInit.Sector = __Flash_GetSector(startingAddress);

	HAL_FLASH_Unlock();

	HAL_StatusTypeDef status = HAL_FLASHEx_Erase_IT(&eraseInit);

	HAL_FLASH_Lock();

	return status;
}

HAL_StatusTypeDef Flash_WriteFlashWord(uint32_t startingAddress, uint32_t *pData) {
	HAL_FLASH_Unlock();

	HAL_StatusTypeDef status = HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_FLASHWORD, startingAddress, (uint32_t) pData);

	HAL_FLASH_Lock();

	return status;
}

void Flash_SafeWriteFlashWord(uint32_t startingAddress, uint32_t *pData) {
	if (flashCounter == FLASH_CACHE_SIZE) {
		return;
	}

	flashCache[flashCounter].address = startingAddress;
	flashCache[flashCounter].pData = pData;

	flashCounter++;
}

void Flash_HandleData() {
	// only do anything if there is something in cache
	if (flashCounter == 0) {
		return;
	}

	// do nothing if the flash is still busy
	if (Flash_WriteFlashWord(flashCache[0].address, flashCache[0].pData) != HAL_OK) {
		return;
	}

	// if writing to the cache was successful, the whole cache is shifted by one
	for (uint8_t i = 1; i < flashCounter; i++) {
		flashCache[i - 1].address = flashCache[i].address;
		flashCache[i - 1].pData = flashCache[i].pData;
	}

	flashCounter--;
}


uint8_t Flash_ReadByte(uint32_t startingAddress) {
	return * (__IO uint8_t *) startingAddress;
}

uint16_t Flash_ReadHalfWord(uint32_t startingAddress) {
	return * (__IO uint16_t *) startingAddress;
}

uint32_t Flash_ReadWord(uint32_t startingAddress) {
	return * (__IO uint32_t *) startingAddress;
}

uint8_t __Flash_GetBank(uint32_t address) {
	if (address < 0x08100000) {
		return FLASH_BANK_1;
	} else {
		return FLASH_BANK_2;
	}
}

uint8_t __Flash_GetSector(uint32_t address) {
	// bank two is shifted by a certain fixed value, therefore this is substracted
	if (__Flash_GetBank(address) == FLASH_BANK_2) {
		address -= 0x00100000;
	}

	return address / 0x00020000;
}

// CALLBACKS

void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue) {
	//if (ReturnValue == 0xFFFFFFFF) {
	//	char usb_buf[64];
	//	uint16_t usb_buf_len = snprintf(usb_buf, 64,
	//			"Clearing Contents from flash.\r\n");
	//	HAL_UART_Transmit(&huart3, (uint8_t*) usb_buf, usb_buf_len,
	//			HAL_MAX_DELAY);

	//	return;
	//}

	//char usb_buf[64];
	//uint16_t usb_buf_len = snprintf(usb_buf, 64,
	//		"Reading two Bytes from Flash: 0x%04X.\r\n",
	//		Flash_ReadHalfWord(ReturnValue));
	//HAL_UART_Transmit(&huart3, (uint8_t*) usb_buf, usb_buf_len, HAL_MAX_DELAY);
}
