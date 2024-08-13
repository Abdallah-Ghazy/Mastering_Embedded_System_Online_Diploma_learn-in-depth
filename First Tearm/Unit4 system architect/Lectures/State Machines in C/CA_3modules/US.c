/*
 * CA.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#include "US.h"

int US_distance = 0;


int US_Get_distance_random(int l, int r, int count) {
    return (rand() % (r - l + 1)) + l;
}

void (*US_state)();

US_init(){
	printf("\nUS_init......");
}



STATE_define(US_busy) {
	US_state_id = US_busy;

    US_distance = US_Get_distance_random(45, 55, 1);
    printf("\n CA_Waiting State: distance = %d Speed = %d \n", US_distance);
    US_set_distance(US_distance);
    US_state = STATE(US_busy);
}
