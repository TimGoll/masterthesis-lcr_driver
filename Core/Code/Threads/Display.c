#include "Display.h"

// define struct for OLED display
SSD1306_t ssd1306;

char buffer[64];

uint8_t i = 0;

void Display_StartThread(void *argument) {
	// the reference to the I2C instance is passed as a void pointer on creation of the thread
	// here it is cast back to the correct type
	I2C_HandleTypeDef *hi2c1 = (I2C_HandleTypeDef*) argument;

	SSD1606Font_AddSpecialChar(&SSD1306_font_6x8, char_omega); // omega as \1

	SSD1306_Initialize(&ssd1306, hi2c1, 0x3C, 128, 64, 0, 0, 0, 0);

	while(1) {
		// prepare values
		uint16_t freq_significant, freq_mantissa;
		Common_GetSignificantAndMantissa(LCRData_GetMeasurementFrequency(), 1000, 2, &freq_significant, &freq_mantissa);

		uint16_t min_volt_significant, min_volt_mantissa;
		Common_GetSignificantAndMantissa(LCRData_GetMinMeasurementVoltage(), 1241, 2, &min_volt_significant, &min_volt_mantissa);

		uint16_t max_volt_significant, max_volt_mantissa;
		Common_GetSignificantAndMantissa(LCRData_GetMaxMeasurementVoltage(), 1241, 2, &max_volt_significant, &max_volt_mantissa);

		// static top header
		SSD1306_Fill(&ssd1306, SSD1306_COLOR_BLACK);

		SSD1306_SetCursor(&ssd1306, 0, 0);
		SSD1306_DrawBitmap(&ssd1306, logo_bitmap, SSD1306_COLOR_WHITE);

		SSD1306_SetCursor(&ssd1306, 24, 0);
		SSD1306_DrawBitmap(&ssd1306, name_bitmap, SSD1306_COLOR_WHITE);

		SSD1306_SetCursor(&ssd1306, 104, 9);
		SSD1306_DrawString(&ssd1306, VERSION, SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		// estimation procedure mode
		SSD1306_SetCursor(&ssd1306, 0, 16);
		SSD1306_DrawString(&ssd1306, "Mode 0 - FFT RC Model", SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		// divider line
		SSD1306_DrawLine(&ssd1306, 0, 25, 127, 25, SSD1306_COLOR_WHITE);

		// excitement signal data
		sprintf(buffer, "Fs=%d.%02dkHz", freq_significant, freq_mantissa);
		SSD1306_SetCursor(&ssd1306, 0, 28);
		SSD1306_DrawString(&ssd1306, buffer, SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		sprintf(buffer, "Us=%d.%02dV .. %d.%02dV", min_volt_significant, min_volt_mantissa, max_volt_significant, max_volt_mantissa);
		SSD1306_SetCursor(&ssd1306, 0, 36);
		SSD1306_DrawString(&ssd1306, buffer, SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		// divider line
		SSD1306_DrawLine(&ssd1306, 0, 45, 127, 45, SSD1306_COLOR_WHITE);

		// R/C data
		SSD1306_SetCursor(&ssd1306, 0, 48);
		SSD1306_DrawString(&ssd1306, "R=1854\1", SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		SSD1306_SetCursor(&ssd1306, 0, 56);
		SSD1306_DrawString(&ssd1306, "C=6786pF", SSD1306_font_6x8, SSD1306_COLOR_WHITE);

		SSD1306_UpdateScreen(&ssd1306);

		osDelay(100); //update display 10 times per second
	}
}
