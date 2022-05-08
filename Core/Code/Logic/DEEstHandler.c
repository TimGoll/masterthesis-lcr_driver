#include "DEEstHandler.h"

DEEstHandler_Model_t __DEEstList[DEESTIMATION_MODEL_COUNT];
uint8_t __DEEstListSize = 0;

// fallback name
char *fallback_name = "undefined ID";

void DEEstHandler_Register(char* name, void (*init)(), void (*process)(AnaRP_t *voltage_data, AnaRP_t *current_data)) {
	if (__DEEstListSize >= DEESTIMATION_MODEL_COUNT) {
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
