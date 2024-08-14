#ifndef PSD_H_
#define PSD_H_
#include "state.h"


enum {
    PSD_init,
    PSD_reading,
    PSD_waiting
} PSDStateID;

STATE_DEFINE(PSD_init);
STATE_DEFINE(PSD_reading);
STATE_DEFINE(PSD_waiting);

extern void (*PSD_state)();

#endif
