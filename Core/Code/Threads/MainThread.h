#pragma once

#include "cmsis_os.h"

#include "../Logic/CoreData.h"
#include "../Logic/Flash.h"
#include "../Logic/I2CSlave.h"

void MainThread_StartThread(void *argument);
