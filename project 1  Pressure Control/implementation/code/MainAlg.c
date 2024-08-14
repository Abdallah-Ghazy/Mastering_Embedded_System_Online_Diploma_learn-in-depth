#include "MainAlg.h"
#include "state.h"
#include <stdio.h>
#include "driver/driver.h"

int MA_PressureVal = 0;
int MA_threshold = 20;

void (*MA_state)();

void SetPressureValue(int p){
MA_PressureVal = p;
MA_state = (MA_PressureVal <= MA_threshold) ?  STATE(MA_LowPressureDetect) : STATE(MA_HighPressureDetect);
	// printf("-------------- Pressure Value = %d -------------------------- \n",MA_PressureVal);
	
}

STATE_DEFINE(MA_HighPressureDetect){
	// printf("The CPU in MA_HighPressureDetect State ............\n");
    HighPressureDetect();
}

STATE_DEFINE(MA_LowPressureDetect) {
    // printf("The CPU is in MA_LowPressureDetect State ............\n");

    
}

