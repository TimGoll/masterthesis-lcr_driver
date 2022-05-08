#include "Common.h"

uint16_t Common_Power(uint16_t base, uint16_t exp) {
	if (exp == 0)
		return 1;
	else if (exp % 2)
		return base * Common_Power(base, exp - 1);
	else {
		uint16_t temp = Common_Power(base, exp / 2);

		return temp * temp;
	}
}

void Common_GetSignificantAndMantissa(uint32_t number, uint16_t base, uint8_t digits, uint16_t *significant, uint16_t *mantissa) {
	*significant = number / base;

	uint32_t remainder = number % base;

	// add half base for rounding
	*mantissa = (remainder * Common_Power(10, digits) + base / 2) / base;
}
