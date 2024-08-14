#ifndef MA_H_
#define MA_H_

#include "state.h"

enum {
    MA_HighPressureDetect,
    MA_LowPressureDetect 
} MAStateID;

STATE_DEFINE(MA_HighPressureDetect);
STATE_DEFINE(MA_LowPressureDetect);

extern void (*MA_state)();

#endif
