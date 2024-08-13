/*
 * lifo.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Abdallah Ghazy
 */
#include "lifo.h"

LIFO_status LIFO_Add_item(LIFO_Buf_t *lifo_buf, unsigned int item) {
    // Check for null pointers
    if (!lifo_buf || !lifo_buf->base || !lifo_buf->head)
        return LIFO_null;

    // Check if the buffer is full
    if (lifo_buf->count >= lifo_buf->length)
        return LIFO_full;

    // Add the item to the buffer
    *(lifo_buf->head) = item;
    lifo_buf->head++;
    lifo_buf->count++;

    return LIFO_no_error;
}

LIFO_status LIFO_get_item(LIFO_Buf_t *lifo_buf, unsigned int *item) {
    // Check for null pointers
    if (!lifo_buf || !lifo_buf->base || !lifo_buf->head || !item)
        return LIFO_null;

    // Check if the buffer is empty
    if (lifo_buf->count == 0)
        return LIFO_empty;

    // Get the item from the buffer
    lifo_buf->head--;
    lifo_buf->count--;
    *item = *(lifo_buf->head);

    return LIFO_no_error;
}

LIFO_status LIFO_init(LIFO_Buf_t *lifo_buf, unsigned int *buf, unsigned int length) {
    // Check for null pointers and invalid length
    if (!lifo_buf || !buf || length == 0)
        return LIFO_null;

    // Initialize the buffer
    lifo_buf->base = buf;
    lifo_buf->head = buf;
    lifo_buf->length = length;
    lifo_buf->count = 0;

    return LIFO_no_error;
}
