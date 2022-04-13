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

#ifndef INC_ANAOUT_H
#define INC_ANAOUT_H

#include "math.h"
#include "stm32h7xx_hal.h"

#define ANAOUT_BUFFER_SIZE 128 ///< The fixed buffer size for the buffer that is outputted via DMA.
#define PI 3.1415926

/**
 * @brief The analog output structure.
 *
 * The analog data structure handles the buffer, the size and the DMA channel associated with it.
 * An instance of this structure is passed with every function call in this scope.
 */
typedef struct {
	DAC_HandleTypeDef *hdac; ///< The handler to the internal DAC.
	uint16_t size; ///< The size of the buffer that is repeatedly outputted via DMA.
	uint16_t buffer[ANAOUT_BUFFER_SIZE]; ///< The buffer that is outputted.
} AnaOut;

/**
 * Initializes the analog output. Also sets up the DMA channel and pushes the then created output buffer to the DMA module.
 *
 * @param [in] *dev The analog output structure.
 * @param [in] *tmr The pointer to the timer that should be associated with the DMA channel.
 * @param [in] *hdac The pointer to the DMA channel.
 */
void AnaOut_Initialize(AnaOut *dev, TIM_HandleTypeDef *tmr, DAC_HandleTypeDef *hdac);

/**
 * A helper function that sets up a sine wave in a predefined buffer that is pushed via DMA to a DAC.
 *
 * @intfunction
 *
 * @param  [out] *buffer The buffer that should be filled.
 */
void __AnaOut_SetupSine(uint16_t *buffer);

#endif /* INC_ANAOUT_H */
