#include "DEEstHandler.h"

DEEStHandler_Model_t __DEEstList[DEESTIMATION_MODEL_COUNT];
uint8_t __DEEstListSize = 0;
uint8_t __DEEstSelected = 0;


void DEEstHandler_Register(char* name, void (*init)(), void (*process)(AnaRP_t *voltage_data, AnaRP_t *current_data)) {
	if (__DEEstListSize >= DEESTIMATION_MODEL_COUNT) {
		return;
	}

	// temporary cache model in dev variable
	DEEStHandler_Model_t *dev = &__DEEstList[__DEEstListSize];

	// since one element got added we have to increase the size
	__DEEstListSize++;

	strcpy(dev->name, name);

	dev->process = process;

	// now call the initialize function
	init();
}

void DEEstHandler_SelectModel(uint8_t id) {
	if (id > __DEEstListSize) {
		return;
	}

	__DEEstSelected = id;
}

void DEEstHandler_RunModel(AnaRP_t *voltage_data, AnaRP_t *current_data) {
	if (__DEEstSelected >= __DEEstListSize) {
		return;
	}

	__DEEstList[__DEEstSelected].process(voltage_data, current_data);
}
