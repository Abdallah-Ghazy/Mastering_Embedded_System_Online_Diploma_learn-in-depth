#include <stdio.h>
#include "state.h"
#include "AlarmMonitor.h"

int AlarmTime = 10000;
int AlarmPeriod = 0;

void (*AM_State)();

void HighPressureDetect(void) {
    // printf("The CPU in High Pressure Detect ............\n");
    AM_State = STATE(AlarmON);
}

STATE_DEFINE(AlarmOFF) {
    AMStateID = AlarmOFF;
    // printf("The CPU in Alarm OFF State ............\n");
    StopeAlarm();
}

STATE_DEFINE(AlarmON) {
    AMStateID = AlarmON;
    // printf("The CPU in Alarm ON State ............\n");
    StartAlarm();
    AM_State = STATE(waiting);
}

STATE_DEFINE(waiting) {
    AMStateID = waiting;
    // printf("The CPU in waiting State ............\n");

    // delay
    Delay(AlarmTime);
    AM_State = STATE(AlarmOFF);
}
