#include <stdio.h>
#include "state.h"
#include "AlarmActyatorDriver.h"

void (*AAD_State)();

void StartAlarm(void) {
    // printf("The Alarm in Start State ............\n");
    Set_Alarm_actuator(0);
    AAD_State = STATE(AAD_waiting);
}

void StopeAlarm(void) {
    //printf("The Alarm in Stope State ............\n");
    Set_Alarm_actuator(1);
    AAD_State = STATE(AAD_waiting);
}

STATE_DEFINE(AAD_init) {
    AADStateID = AAD_init;
    // printf("The Sensor in init State ............\n");
}

STATE_DEFINE(AAD_waiting) {
    AADStateID = AAD_waiting;
    // printf("The Alarm in waiting State ............\n");
}
