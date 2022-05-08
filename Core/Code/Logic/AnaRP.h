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

#pragma once

#include "stm32h7xx_hal.h"

#include "../config.h"

typedef struct {
	ADC_HandleTypeDef *hadc; ///< the ADC handle
	uint16_t size; ///< size of the buffer
	uint16_t buffer[ADC_SAMPLE_SIZE]; ///< the buffer for the DAC

	uint32_t next_measurement; ///< time in milliseconds when the next measurement should take place

	uint8_t process_data_flag; ///< a flag that is set to 1 if there is data to process
} AnaRP_t;

AnaRP_t *__ADCList[3]; ///< A list that contains all ADC objects.
uint8_t __ADCListSize; ///< The amount of ADCs on the MCU.


/**
 * Initializes a analog input data struct. It also sets up the DMA stream.
 *
 * @param [in] *dev The analog data struct that contains everything regarding the specific analog data instance
 * @param [in] *hadc The handler of the ADC in use
 */
void AnaRP_Initialize(AnaRP_t *dev, ADC_HandleTypeDef *hadc);

void AnaRP_StartDMA(AnaRP_t *dev);

/**
 * Processes the data repeatedly. Once half the process flag is set, it is processed in this function.
 *
 * @param [in] *dev The analog data struct that contains everything regarding the specific analog data instance
 */
void AnaRP_ProcessData(AnaRP_t *dev);

uint8_t AnaRP_IsReady(AnaRP_t *dev);

uint8_t AnaRP_FinishedReading(AnaRP_t *dev);

void AnaRP_ResetState(AnaRP_t *dev);

uint8_t __AnaRP_FindADC(ADC_HandleTypeDef *hadc, AnaRP_t **adc);

