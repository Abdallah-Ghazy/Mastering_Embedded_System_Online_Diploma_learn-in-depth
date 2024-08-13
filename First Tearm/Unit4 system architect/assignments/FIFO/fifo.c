#include "fifo.h"

// Initialize the FIFO buffer
FIFO_Buf_status FIFO_init(FIFO_Buf_t *fifo, element_type *buff, uint32_t length) {
    if (buff == NULL)
        return FIFO_null;  // Return error if buffer is null

    fifo->base = buff;    // Set the base pointer to the provided buffer
    fifo->head = buff;    // Set the head pointer to the start of the buffer
    fifo->tail = buff;    // Set the tail pointer to the start of the buffer
    fifo->length = length; // Set the length of the buffer
    fifo->count = 0;      // Initialize count to 0

    return FIFO_no_error; // Return no error status
}

// Enqueue an item into the FIFO buffer
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t *fifo, element_type item) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null;  // Return error if any pointer is null

    if (FIFO_IS_FULL(fifo) == FIFO_full)
        return FIFO_full; // Return full status if buffer is full

    *(fifo->head) = item; // Place the item at the head of the buffer
    fifo->count++;        // Increment the count of items

    // Wrap around the head pointer if it reaches the end of the buffer
    if (fifo->head == (fifo->base + fifo->length - 1))
        fifo->head = fifo->base;
    else
        fifo->head++;

    return FIFO_no_error; // Return no error status
}

// Dequeue an item from the FIFO buffer
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t *fifo, element_type *item) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null;  // Return error if any pointer is null

    if (fifo->count == 0)
        return FIFO_empty; // Return empty status if buffer is empty

    *item = *fifo->tail; // Retrieve the item from the tail of the buffer
    fifo->count--;       // Decrement the count of items

    // Wrap around the tail pointer if it reaches the end of the buffer
    if (fifo->tail == (fifo->base + fifo->length - 1))
        fifo->tail = fifo->base;
    else
        fifo->tail++;

    return FIFO_no_error; // Return no error status
}

// Check if the FIFO buffer is full
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t *fifo) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null;  // Return error if any pointer is null

    if (fifo->count == fifo->length)
        return FIFO_full; // Return full status if buffer is full

    return FIFO_no_error; // Return no error status
}

// Print the contents of the FIFO buffer
void FIFO_print(FIFO_Buf_t *fifo) {
    element_type *temp;
    int i;

    if (fifo->count == 0) {
        printf("FIFO is empty\n"); // Inform that the buffer is empty
    } else {
        temp = fifo->tail; // Start printing from the tail
        printf("\n==================== FIFO ==================\n");
        for (i = 0; i < fifo->count; i++) {
            printf("\t%02X\n", *temp); // Print each item in hexadecimal format
            temp++; // Move to the next item
        }
        printf("\n======================================\n");
    }
}
