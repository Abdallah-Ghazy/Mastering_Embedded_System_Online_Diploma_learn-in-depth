/*
 * main.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Abdallah Ghazy
 */
extern int flag;
#include "SMS.h"
int main(int argc, char **argv) {

	while (flag) {
		displayMenu();
		ExecuteOption();

	}
}
