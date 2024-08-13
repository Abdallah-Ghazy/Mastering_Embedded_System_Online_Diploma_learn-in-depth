/*
 * main.c
 *
 *  Created on: Aug 4, 2024
 *      Author: Abdallah Ghazy
 */

#include "CA.h"

void setup() {
    CA_state = STATE(CA_waiting);
}

int main() {
    setup();
    while (1) {
        CA_state();
    }
    return 0;
}
