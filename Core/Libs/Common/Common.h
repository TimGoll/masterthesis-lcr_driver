#pragma once

#include <stdio.h>
#include <math.h>

uint16_t Common_Power(uint16_t base, uint16_t exp);

void Common_GetSignificantAndMantissa(uint32_t number, uint16_t base, uint8_t digits, uint16_t *significant, uint16_t *mantissa);
