/*
 * main.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#include "US.h"
#include "DC.h"
#include "CA.h"

void setup() {

	US_init();
	DC_init();

    CA_state = STATE(CA_waiting);
    US_state = STATE(US_busy);
    DC_state = STATE(DC_idle);
}

int main() {
    setup();
    while (1) {
    	US_state();
        CA_state();
        DC_state();
    }
    return 0;
}
