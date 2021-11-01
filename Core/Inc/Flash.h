/*
 * Flash.h
 *
 * The flash library provides an easy to use interface of the flash of this very specific chip.
 *
 * The STM32H743ZI has two banks with each one megabyte of user memory. Each of those banks
 * is divided into 8 sectors with 128 kilobyte each. While writing data, only erased data can be
 * overwritten. Erased pData is all ones.
 * Therefore a complete sector has to be cleared before data can be written to flash.
 *
 * Code is inspired by: https://controllerstech.com/flash-programming-in-stm32/
 *
 * Created on: 25.10.2021
 * Author: Tim Goll
 */

#ifndef INC_FLASH_H
#define INC_FLASH_H

#define FLASH_CACHE_SIZE 32
#define FLASH_WORD_SIZE 0x20

#include "stm32h7xx_hal.h"

typedef struct {
	uint32_t *pData;
	uint32_t address;
} Flash_CacheElement;

extern Flash_CacheElement flashCache[FLASH_CACHE_SIZE];
extern uint8_t flashCounter;

/*
 * @brief  Clears a complete flash sector (128 kilobytes) of data.
 *
 * @param[in]  startingAddress The starting address of the memory
 * @param[in]  amount Amount of sectors that should be cleared
 *
 * @retval  HAL Status
 */
HAL_StatusTypeDef FlashClearSector(uint32_t startingAddress, uint8_t amount);

/*
 * @brief  Writes a whole flash word to the flash. A flash word contains 8 words (156 bytes).
 *
 * @param[in]  startingAddress The starting address of the memory
 * @param[in]  pData A pointer to the flash word array with eight words in it
 *
 * @retval  HAL Status
 */
HAL_StatusTypeDef Flash_WriteFlashWord(uint32_t startingAddress, uint32_t *pData);

/*
 * @brief  Writes a whole flash word to the flash. A flash word contains 8 words (156 bytes).
 * However this doesn't write it directly to the flash. It is added to an internal cache instead
 * and written to the flash as soon as it is no longer busy.
 *
 * @param[in]  startingAddress The starting address of the memory
 * @param[in]  pData A pointer to the flash word array with eight words in it
 */
void Flash_SafeWriteFlashWord(uint32_t startingAddress, uint32_t *pData);

/*
 * @brief  A handled that is repeatedly called that handles writing data to the flash.
 */
void Flash_HandleData();

uint8_t Flash_ReadByte(uint32_t startingAddress);
uint16_t Flash_ReadHalfWord(uint32_t startingAddress);
uint32_t Flash_ReadWord(uint32_t startingAddress);

uint8_t __Flash_GetBank(uint32_t address);
uint8_t __Flash_GetSector(uint32_t address);

#endif /* INC_FLASH_H */
