#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"

#define element_type uint8_t  // Define the element type as uint8_t
#define width1 5             // Define the buffer size as 5
element_type uart_buffer[width1]; // Define a buffer with the size of width1

typedef struct {
    unsigned int length;  // Length of the buffer
    unsigned int count;   // Number of items currently in the buffer
    element_type *base;   // Pointer to the base of the buffer
    element_type *head;   // Pointer to the current head of the buffer
    element_type *tail;   // Pointer to the current tail of the buffer
} FIFO_Buf_t;

typedef enum {
    FIFO_no_error,  // No error occurred
    FIFO_full,      // Buffer is full
    FIFO_empty,     // Buffer is empty
    FIFO_null       // Null pointer encountered
} FIFO_Buf_status;

// Function prototypes for FIFO operations
FIFO_Buf_status FIFO_init(FIFO_Buf_t *fifo, element_type *buff, uint32_t length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t *fifo, element_type item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t *fifo, element_type *item);
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t *fifo);
void FIFO_print(FIFO_Buf_t *fifo);

#endif /* FIFO_H_ */
