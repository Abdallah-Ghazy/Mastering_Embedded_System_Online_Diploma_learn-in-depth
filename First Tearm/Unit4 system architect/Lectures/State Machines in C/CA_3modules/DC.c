/*
 * CA.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#include "DC.h"
#include "state.h"
int DC_speed = 0;
void (*DC_state)();

void DC_init() {
	printf("DC_init.............");
}

void DC_motor(int s) {
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("US-------------- DC_speed = %d -------------------------- \n",
			DC_speed);
}

STATE_define(DC_idle) {
	DC_state_id = DC_idle;

	printf("\n DC_idle State: Speed = %d \n", DC_speed);
}

STATE_define(DC_busy) {
	DC_state_id = DC_busy;
	printf("US-------------- DC_speed = %d -------------------------- \n",
			DC_speed);
}

