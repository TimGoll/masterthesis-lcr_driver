/**
  ******************************************************************************
  * @file           AnaOut.h
  * @author         Tim Goll
  * @date           18.10.2021
  * @brief          Handles the analog output for the internal DACs.
  ******************************************************************************
  * The analog output of this board is used to create a sinusoidal signal. To
  * achieve those speeds required without clogging up the MCU, DMA is used. DMA
  * is a direct memory access that pushes the data on a timer interrupt from
  * memory to the analog output without interfering the CPU.
  *
  ******************************************************************************
  */

#pragma once

#include "../config.h"

#include <stdlib.h>
#include <math.h>

#include "cmsis_os.h"
#include "stm32h7xx_hal.h"

/**
 * @brief The analog output structure.
 *
 * The analog data structure handles the buffer, the size and the DMA channel associated with it.
 * An instance of this structure is passed with every function call in this scope.
 */
typedef struct {
	DAC_HandleTypeDef *hdac; ///< The handler to the internal DAC
	uint16_t *buffer; ///< The buffer that is outputted
	uint16_t buffer_size; ///< The size of the buffer that is repeatedly outputted via DMA
	uint32_t dac_channel; ///< The channel of the DAC
} SineGen_t;

/**
 * Initializes the analog output. Also sets up the DMA channel and pushes the then created output buffer to the DMA module.
 *
 * @param [in] *dev The analog output structure
 * @param [in] *tmr The pointer to the timer that should be associated with the DMA channel
 * @param [in] *hdac The pointer to the DMA channel
 * @param [in] dac_channel The channel of the DAC
 */
void SineGen_Initialize(SineGen_t *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac, uint32_t dac_channel);

/**
 * A helper function that sets up a sine wave in a predefined buffer that is pushed via DMA to a DAC.
 *
 * @param [in] *dev The analog output structure
 * @param [in] min The minimum voltage of the signal
 * @param [in] max The maximum voltage of the signal
 * @param [in] frequency The signal frequency in Hz
 */
void SineGen_SetupSine(SineGen_t *dev, uint16_t min, uint16_t max, uint16_t frequency);

/**
 * Push the generated output to the DAC so that it will be outputted.
 *
 * @param [in] *dev The analog output structure
 */
void SineGen_OutputSine(SineGen_t *dev);
