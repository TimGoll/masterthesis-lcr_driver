#include "Display.h"

// define struct for OLED display
SSD1306_t ssd1306;

char buffer[64];

uint8_t i = 0;

void Display_StartThread(void *argument) {
	// the reference to the I2C instance is passed as a void pointer on creation of the thread
	// here it is cast back to the correct type
	I2C_HandleTypeDef *hi2c1 = (I2C_HandleTypeDef*) argument;

	SSD1306_Initialize(&ssd1306, hi2c1, 0x3C, 128, 32, 0, 0, 0, 0);

	while(1) {
		SSD1306_Fill(&ssd1306, SSD1306_COLOR_BLACK);
		SSD1306_DrawLine(&ssd1306, 43 + i, 0, 43, 31, SSD1306_COLOR_WHITE);
		SSD1306_DrawLine(&ssd1306, 86 + i, 0, 86, 31, SSD1306_COLOR_WHITE);

		i = (i+1)%32;

		// Sample Frequency
		sprintf(buffer, "Fs=10015Hz");
		SSD1306_SetCursor(&ssd1306, 0, 0);
		SSD1306_WriteString(&ssd1306, buffer, SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		sprintf(buffer, "Us=3.12V");
		SSD1306_SetCursor(&ssd1306, 0, 8);
		SSD1306_WriteString(&ssd1306, buffer, SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		SSD1306_UpdateScreen(&ssd1306);

		osDelay(100); //update display 10 times per second
	}
}
