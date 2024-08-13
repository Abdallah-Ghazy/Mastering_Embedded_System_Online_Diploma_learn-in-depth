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

int US_Get_distance_random(int l, int r, int count) {
    return (rand() % (r - l + 1)) + l;
}

void (*CA_state)();

STATE_define(CA_waiting) {
    CA_state_id = CA_waiting;
    CA_speed = 0;
    CA_distance = US_Get_distance_random(45, 55, 1);
    CA_state = (CA_distance <= CA_threshold) ? STATE(CA_waiting) : STATE(CA_driving);
    printf("\n CA_Waiting State: distance = %d Speed = %d \n", CA_distance, CA_speed);
}

STATE_define(CA_driving) {
    CA_state_id = CA_driving;
    CA_speed = 30;
    CA_distance = US_Get_distance_random(45, 55, 1);
    CA_state = (CA_distance <= CA_threshold) ? STATE(CA_waiting) : STATE(CA_driving);
    printf("\n CA_Driving State: distance = %d Speed = %d \n", CA_distance, CA_speed);
}
