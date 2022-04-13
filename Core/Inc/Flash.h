/**
  ******************************************************************************
  * @file           Flash.h
  * @author         Tim Goll
  * @date           25.10.2021
  * @brief          The flash library provides an easy to use interface of the flash of this very specific chip.
  ******************************************************************************
  * The STM32H743ZI has two banks with each one megabyte of user memory. Each of those banks
  * is divided into 8 sectors with 128 kilobyte each. While writing data, only erased data can be
  * overwritten. Erased pData is all ones.
  * Therefore a complete sector has to be cleared before data can be written to flash.
  *
  * Code is inspired by: https://controllerstech.com/flash-programming-in-stm32/
  *
  ******************************************************************************
  */

#ifndef INC_FLASH_H
#define INC_FLASH_H

#define FLASH_CACHE_SIZE 32
#define FLASH_WORD_SIZE 0x20

#include "stm32h7xx_hal.h"

/**
 * @brief The flash cache structure.
 *
 * The flash structure consists of a pointer to an external data array that is assigned.
 * Additionally the address to the flash sector is set there.
 *
 * It is used to cache the data that should be written to flash. Since writing to flash
 * may block the process for a while, interrupt based writing is used here. When writing
 * to flash it could happen that the flash is still busy. To prevent this from happening
 * the data is cached until it is pushed out via an interrupt callback.
 */
typedef struct {
	uint32_t *pData; ///< Pointer to the data array
	uint32_t address; ///< Address of the data
} Flash_CacheElement;

extern Flash_CacheElement flashCache[FLASH_CACHE_SIZE]; ///< A cache for the flash
extern uint8_t flashCounter; ///< The current position in the cache

/**
 * Clears a complete flash sector (128 kilobytes) of data.
 *
 * @param [in]  startingAddress The starting address of the memory
 * @param [in]  amount Amount of sectors that should be cleared
 *
 * @retval HAL_StatusTypeDef HAL Status
 */
HAL_StatusTypeDef Flash_ClearSector(uint32_t startingAddress, uint8_t amount);

/**
 * Writes a whole flash word to the flash. A flash word contains 8 words (156 bytes).
 *
 * @param [in]  startingAddress The starting address of the memory
 * @param [in]  *pData A pointer to the flash word array with eight words in it
 *
 * @retval HAL_StatusTypeDef HAL Status
 */
HAL_StatusTypeDef Flash_WriteFlashWord(uint32_t startingAddress, uint32_t *pData);

/**
 * Writes a whole flash word to the flash. A flash word contains 8 words (156 bytes).
 * However this doesn't write it directly to the flash. It is added to an internal cache instead
 * and written to the flash as soon as it is no longer busy.
 *
 * @param [in]  startingAddress The starting address of the memory
 * @param [in]  *pData A pointer to the flash word array with eight words in it
 */
void Flash_SafeWriteFlashWord(uint32_t startingAddress, uint32_t *pData);

/**
 * A handler that is repeatedly called that handles writing data to the flash.
 */
void Flash_HandleData();

/**
 * Reads one byte from the flash memory starting at the provided address.
 *
 * @retval uint8_t The read byte
 */
uint8_t Flash_ReadByte(uint32_t startingAddress);

/**
 * Reads one half word (two bytes) from the flash memory starting at the provided address.
 *
 * @retval uint16_t The read half word (two bytes)
 */
uint16_t Flash_ReadHalfWord(uint32_t startingAddress);

/**
 * Reads one word (four bytes) from the flash memory starting at the provided address.
 *
 * @retval uint32_t The read word (four bytes)
 */
uint32_t Flash_ReadWord(uint32_t startingAddress);

/**
 * A helper function that returns the flash bank from a given address.
 *
 * @intfunction
 *
 * @param [in] uint32_t address The address
 *
 * @retval uint8_t The flash bank
 */
uint8_t __Flash_GetBank(uint32_t address);

/**
 * A helper function that returns the flash sector from a given address.
 *
 * @intfunction
 *
 * @param [in] uint32_t address The address
 *
 * @retval uint8_t The flash sector
 */
uint8_t __Flash_GetSector(uint32_t address);

#endif /* INC_FLASH_H */
