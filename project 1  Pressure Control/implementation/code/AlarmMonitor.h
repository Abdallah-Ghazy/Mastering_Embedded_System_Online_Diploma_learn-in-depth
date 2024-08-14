#ifndef AM_H_
#define AM_H_

#include "state.h"

enum {
    AlarmOFF,
    AlarmON,
    waiting
} AMStateID;

STATE_DEFINE(AlarmOFF);
STATE_DEFINE(AlarmON);
STATE_DEFINE(waiting);

extern void (*AM_State)();

#endif
