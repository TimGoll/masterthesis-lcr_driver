#include <stdint.h>

#ifndef SSD1306_FONTS_H
#define SSD1306_FONTS_H

#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10

/**
 * @brief A font data type.
 */
typedef struct {
	const uint8_t char_width; ///< Character width in pixels
	const uint8_t char_height; ///< Character height in pixels
	const uint16_t *data; ///< Pointer to font data array
} SSD1306_Font_t;

#ifdef SSD1306_INCLUDE_FONT_6x8
extern SSD1306_Font_t SSD1306_font_6x8;
#endif

#ifdef SSD1306_INCLUDE_FONT_7x10
extern SSD1306_Font_t SSD1306_font_7x10;
#endif

#ifdef SSD1306_INCLUDE_FONT_11x18
extern SSD1306_Font_t SSD1306_font_11x18;
#endif

#ifdef SSD1306_INCLUDE_FONT_16x26
extern SSD1306_Font_t SSD1306_font_16x26;
#endif

#endif // SSD1306_FONTS_H
