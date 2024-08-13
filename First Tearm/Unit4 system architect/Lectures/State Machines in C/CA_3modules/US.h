/*
 * CA.h
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef US_H_
#define US_H_

#include "state.h"

enum {
	US_busy
} US_state_id;

STATE_define(US_busy);

void US_init();
extern void (*US_state)();

#endif /* US_H_ */
