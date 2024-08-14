#ifndef AAD_H_
#define AAD_H_

#include "state.h"

enum {
    AAD_init,
    AAD_waiting,
    AAD_AlarmON,
    AAD_AlarmOFF
} AADStateID;

STATE_DEFINE(AAD_init);
STATE_DEFINE(AAD_waiting);
// STATE_DEFINE(AAD_AlarmON);
// STATE_DEFINE(AAD_AlarmOFF);

extern void (*AAD_State)();

#endif
