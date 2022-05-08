#pragma once

#include <stdio.h>
#include <math.h>

uint16_t Common_Power(uint16_t base, uint16_t exp);

void Common_GetSignificantAndMantissa(uint32_t number, uint16_t base, uint8_t digits, uint16_t *significant, uint16_t *mantissa);

uint32_t Common_Map(uint32_t in, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
