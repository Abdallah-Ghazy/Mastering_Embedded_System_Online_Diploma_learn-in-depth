#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
#include "driver\\driver.h"

typedef unsigned char uint8_t;

#define STATE_DEFINE(_STFName_) void STF_##_STFName_(void)
#define STATE(_STFName_) STF_##_STFName_
#define STATE_INIT(_STFName_) STATE(_STFName_)()

void HighPressureDetect(void);
void SetPressureValue(int);
void StartAlarm(void);
void StopeAlarm(void);

#endif
