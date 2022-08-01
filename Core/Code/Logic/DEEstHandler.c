#include "DEEstHandler.h"

DEEstHandler_Model_t __DEEstList[DEESTIMATION_MODEL_MAX_COUNT];
uint8_t __DEEstListSize = 0;
uint32_t __lastModeChangePress = 0;

// fallback name
char *fallback_name = "undefined ID";

void DEEstHandler_Register(char* name, void (*init)(), void (*process)(AnaRP_t *voltage_data, AnaRP_t *current_data)) {
	if (__DEEstListSize >= DEESTIMATION_MODEL_MAX_COUNT) {
		return;
	}

	// temporary cache model in dev variable
	DEEstHandler_Model_t *dev = &__DEEstList[__DEEstListSize];

	// since one element got added we have to increase the size
	__DEEstListSize++;

	strcpy(dev->name, name);

	dev->process = process;

	// now call the initialize function
	init();
}

void DEEstHandler_RunModel(AnaRP_t *voltage_data, AnaRP_t *current_data) {
	// cache the model ID to make sure it is not changed while we try to access it
	uint8_t selected_model = CoreData_GetDEModel();

	if (selected_model >= __DEEstListSize) {
		return;
	}

	__DEEstList[selected_model].process(voltage_data, current_data);
}

char *DEEstHandler_GetModelName() {
	// cache the model ID to make sure it is not changed while we try to access it
	uint8_t selected_model = CoreData_GetDEModel();

	if (selected_model >= __DEEstListSize) {
		return fallback_name;
	}

	return __DEEstList[selected_model].name;
}





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	// only proceed if correct button was pressed
	if (GPIO_Pin != GPIO_PIN_13) {
		return;
	}

	// only proceed if debounce time has passed
	if (HAL_GetTick() < __lastModeChangePress + BUTTON_DEBOUNCE_TIME) {
		return;
	}

	// update last button press time
	__lastModeChangePress = HAL_GetTick();

	// cycle through available modes
	CoreData_SetDEModel((CoreData_GetDEModel() + 1) % __DEEstListSize);
}

