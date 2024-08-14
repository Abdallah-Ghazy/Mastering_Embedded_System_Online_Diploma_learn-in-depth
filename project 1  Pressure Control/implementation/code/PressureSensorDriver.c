#include "PressureSensorDriver.h"
#include "state.h"
#include <stdio.h>
#include "driver/driver.h"

int PSD_PressureVal ;
int PSD_PrSensorTime = 10000;
void (*PSD_state)();

// int PSD_Get_Pressure_random(int l, int r, int count) {
//     return (rand() % (r - l + 1)) + l;
// }

STATE_DEFINE(PSD_init){
    PSDStateID = PSD_init;
    // printf("The Sensor in init State ............\n");
}

STATE_DEFINE(PSD_reading){
    PSDStateID = PSD_reading;
    // printf("The Sensor in reading State ............\n");

   // PSD_PressureVal = PSD_Get_Pressure_random(15, 30, 1);
   // printf("PSD_Reading : PressureVal = %d\n", PSD_PressureVal);

    PSD_PressureVal = getPressureVal();
    SetPressureValue(PSD_PressureVal);

    PSD_state = STATE(PSD_waiting);
}

STATE_DEFINE(PSD_waiting){
    PSDStateID = PSD_waiting;

    // delay
    Delay(PSD_PrSensorTime);
    PSD_state = STATE(PSD_reading);
}
