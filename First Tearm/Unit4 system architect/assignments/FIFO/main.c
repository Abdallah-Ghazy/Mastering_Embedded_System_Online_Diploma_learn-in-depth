#include "fifo.h"

int main() {
    FIFO_Buf_t FIFO_UART;  // Define a FIFO buffer structure
    element_type temp = 0; // Define a variable to store dequeued values

    // Initialize the FIFO with a buffer size of 5
    if (FIFO_init(&FIFO_UART, uart_buffer, width1) == FIFO_no_error)
        printf("FIFO init -----------Done\n");

    // Enqueue elements into the FIFO
    for (element_type i = 0; i < 7; i++) {
        printf("FIFO Enqueue (%X) \n", i);
        if (FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error)
            printf("\t FIFO enqueue -----------Done\n");
        else
            printf("\t FIFO enqueue -----------Failed\n");
    }

    // Print the FIFO contents after enqueuing
    FIFO_print(&FIFO_UART);

    // Dequeue elements from the FIFO
    if (FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error)
        printf("\t FIFO dequeue %X -----------Done\n", temp);

    if (FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error)
        printf("\t FIFO dequeue %X -----------Done\n", temp);

    // Print the FIFO contents after dequeuing
    FIFO_print(&FIFO_UART);

    return 0;
}
