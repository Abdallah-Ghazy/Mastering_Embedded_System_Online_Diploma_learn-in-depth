#include <stdint.h>
#include <stdio.h>
#include "AlarmActyatorDriver.h"  
#include "AlarmMonitor.h"       
#include "MainAlg.h"
#include "PressureSensorDriver.h" 
#include "driver/driver.h"
#include "state.h"

extern void GPIO_INITIALIZATION();

void setup() {
    STATE_INIT(PSD_init);
    STATE_INIT(AAD_init);

    PSD_state = STATE(PSD_waiting);
    MA_state = STATE(MA_LowPressureDetect);
    AM_State = STATE(AlarmOFF);
    AAD_State = STATE(AAD_init);
}

int main() {
    GPIO_INITIALIZATION();
    setup();
    while (1) {
        PSD_state();
        MA_state();
        AAD_State();
        AM_State();
    }
}
