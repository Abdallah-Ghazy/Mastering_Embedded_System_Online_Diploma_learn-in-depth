/*
 * CA.h
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

enum {
	DC_idle,DC_busy
} DC_state_id;

STATE_define(DC_idle);
STATE_define(DC_busy);



void DC_init();
extern void (*DC_state)();

#endif /* US_H_ */
