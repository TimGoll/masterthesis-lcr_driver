/**
  ******************************************************************************
  * @file           AnaRP.h
  * @author         Tim Goll
  * @date           28.09.2021
  * @brief          Analog Read and Process data.
  ******************************************************************************
  * AnaRP handles the analog input data. It reads the data with a DMA stream into
  * memory and then processes this data repeatedly.
  * Once half the buffer for a given ADC is filled via DMA stream, a interrupt is
  * called. This data is then processed in the HandleData function.
  *
  ******************************************************************************
  */

#ifndef INC_ANARP_H
#define INC_ANARP_H

#include "stm32h7xx_hal.h"

#define ANARP_BUFFER_SIZE 4096 ///< size should be set so that size/2 is enough to reconstruct sine wave

typedef struct {
	ADC_HandleTypeDef *hadc;
	uint16_t size;
	uint16_t buffer[ANARP_BUFFER_SIZE];
} AnaRP_t;

/**
 * Initializes a analog input data struct. It also sets up the DMA stream.
 *
 * @param [in] *dev The analog data struct that contains everything regarding the specific analog data instance
 * @param [in] *hadc The handler of the ADC in use
 */
void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc);

/**
 * Handles the data repeatedly. Once half the data buffer is filled, it is processed in this function.
 *
 * @param [in] *dev The analog data struct that contains everything regarding the specific analog data instance
 */
void AnaRP_HandleData(AnaRP_t *dev);

#endif /* INC_ANARP_H */
