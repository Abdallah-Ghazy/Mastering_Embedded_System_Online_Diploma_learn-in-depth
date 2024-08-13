/*
 * lifo.h
 *
 *  Created on: Aug 1, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdio.h>
#include <stdlib.h>

// Type definition for a LIFO buffer
typedef struct {
    unsigned int length;  // Maximum number of items the buffer can hold
    unsigned int count;   // Current number of items in the buffer
    unsigned int* base;   // Pointer to the base of the buffer
    unsigned int* head;   // Pointer to the current position in the buffer
} LIFO_Buf_t;


// Enum to represent the status of LIFO operations
typedef enum {
    LIFO_no_error,  // No error occurred
    LIFO_full,      // Buffer is full
    LIFO_empty,     // Buffer is empty
    LIFO_null       // Null pointer encountered
} LIFO_status;


// API function prototypes
LIFO_status LIFO_Add_item(LIFO_Buf_t* lifo_buf, unsigned int item);
LIFO_status LIFO_get_item(LIFO_Buf_t* lifo_buf, unsigned int* item);
LIFO_status LIFO_init(LIFO_Buf_t* lifo_buf, unsigned int* buf, unsigned int length);

#endif /* LIFO_H_ */
