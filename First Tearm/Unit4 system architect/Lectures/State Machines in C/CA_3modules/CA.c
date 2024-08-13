/*
 * CA.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#include "CA.h"

int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;

void (*CA_state)();

void US_set_distance(int d){
	CA_distance = d;
	CA_state = (CA_distance <= CA_threshold) ? STATE(CA_waiting) : STATE(CA_driving);

	printf("US-------------- Distance = %d -------------------------- \n",CA_distance);
}



STATE_define(CA_waiting) {
    CA_state_id = CA_waiting;
    printf("\n CA_Waiting State: distance = %d Speed = %d \n", CA_distance, CA_speed);
    CA_speed = 0;
    DC_motor(CA_speed);
}

STATE_define(CA_driving) {
    CA_state_id = CA_driving;
    CA_speed = 30;
    printf("\n CA_Driving State: distance = %d Speed = %d \n", CA_distance, CA_speed);


    DC_motor(CA_speed);
}
