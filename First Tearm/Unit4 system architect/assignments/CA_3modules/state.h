/*
 * state.h
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_)  ST_##_stateFUN_

void US_set_distance(int d);
void DC_motor(int s);

#endif /* STATE_H_ */
