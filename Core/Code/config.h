// ANALOG OUT
#define DAC_SAMPLE_FREQ 1000000 // STM H7 has 1MSample/s

// ANALOG IN PROCESSING
#define ADC_FFT_SIZE 256
#define ADC_BUFFER_SIZE ADC_FFT_SIZE * 2
#define ADC_SAMPLE_FREQ 500000 // the max sample frequency seems to be 7.5MHz
#define ADC_PROCESS_FREQ 100 // process the data 100 times per second

