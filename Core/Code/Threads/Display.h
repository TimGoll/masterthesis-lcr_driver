#pragma once

#include <stdio.h>
#include "cmsis_os.h"

// define which fonts should be used here, limits memory usage
#define SSD1306_INCLUDE_FONT_6x8

#include "../Libs/SSD1306/SSD1306.h"
#include "../Libs/Common/Common.h"

#include "../config.h"
#include "../bitmaps.h"

#include "../Logic/CoreData.h"
#include "../Logic/DEEstHandler.h"

void Display_StartThread(void *argument);
