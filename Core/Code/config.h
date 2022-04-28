// ANALOG OUT
#define DAC_SAMPLE_FREQ 1000000 // STM H7 has 1MSample/s

// ANALOG IN PROCESSING
#define ADC_SAMPLE_FREQ 1280000 // this is the resulting frequency, hardware oversampling is ignored
#define ADC_PROCESS_FREQ 100 // process the data 100 times per second
#define ADC_FFT_SIZE 256
