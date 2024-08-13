/*
 * main.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Abdallah Ghazy
 */
#include "lifo.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int buffer1[5];

int main() {
    int temp = 0;
    LIFO_Buf_t uart_lifo, I2C_lifo;

    // Initialize LIFO buffers
    LIFO_init(&uart_lifo, buffer1, 5);

    unsigned int *buffer2 = (unsigned int*) malloc(5 * sizeof(unsigned int));
    if (buffer2 == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Return with error code
    }
    LIFO_init(&I2C_lifo, buffer2, 5);

    // Add items to UART LIFO buffer
    for (int i = 0; i < 5; i++) {
        if (LIFO_Add_item(&uart_lifo, i) == LIFO_no_error)
            printf("UART_LIFO Add: %d\n", i);
        else
            printf("UART_LIFO Add failed: %d\n", i);
    }

    // Get items from UART LIFO buffer
    for (int i = 0; i < 5; i++) {
        if (LIFO_get_item(&uart_lifo, &temp) == LIFO_no_error)
            printf("UART_LIFO Get: %d\n", temp);
        else
            printf("UART_LIFO Get failed\n");
    }

    // Clean up
    free(buffer2);

    return 0;
}
