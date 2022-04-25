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

#include "../config.h"

#define ARM_MATH_CM7 // cortex m7 based MCU

#include "../../Libs/CMSIS_DSP/arm_math.h"

typedef struct {
	ADC_HandleTypeDef *hadc; ///< the ADC handle
	uint16_t size; ///< size of the buffer
	uint16_t buffer[2][ADC_FFT_SIZE]; ///< the double buffer for the DAC
	uint8_t filled_buffer; ///< the currently selected buffer that is filled with data about to be processed

	uint32_t next_processing; ///< time in milliseconds when the next processing should take place

	uint8_t process_data_flag; ///< a flag that is set to 1 if there is data to process

	arm_rfft_fast_instance_f32 fft_inst; ///< The FFT instance
	float32_t fft_in[ADC_FFT_SIZE]; ///< The input array for the FFT (converted ADC buffer)
	float32_t fft_out[ADC_FFT_SIZE]; ///< The output of the FFT (complex numbers: real(0), imag(0), real(1), ...)
	float32_t fft_mag[ADC_FFT_SIZE / 2]; ///< The magnitude, only real numbers, therefore half the output size
	float32_t fft_max_amp;
	uint32_t fft_max_amp_idx;

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

/**
 * Processes the data repeatedly. Once half the process flag is set, it is processed in this function.
 *
 * @param [in] *dev The analog data struct that contains everything regarding the specific analog data instance
 */
void AnaRP_ProcessData(AnaRP_t *dev);

uint8_t __AnaRP_FindADC(ADC_HandleTypeDef *hadc, AnaRP_t **adc);

#endif /* INC_ANARP_H */
