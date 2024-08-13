#define SYSCTL_RCGC2_R           (*((volatile unsigned long*)(0x400fe108)))
#define GPIO_PORTF_DIR_R         (*((volatile unsigned long*)(0x40025400)))
#define GPIO_PORTF_DEN_R         (*((volatile unsigned long*)(0x4002551c)))
#define GPIO_PORTF_DATA_R        (*((volatile unsigned long*)(0x400253fc)))

int main()
{
    // Enable the clock for GPIO Port F
    SYSCTL_RCGC2_R = 0x20;

    // Small delay for the clock to stabilize
    volatile int delay_count = 0;
    for(delay_count = 0; delay_count < 200; delay_count++ );

    // Set Pin 3 as output and enable it
    GPIO_PORTF_DIR_R |= (1 << 3);
    GPIO_PORTF_DEN_R |= (1 << 3);

    while(1)
    {
        // Toggle Pin 3
        GPIO_PORTF_DATA_R |= (1 << 3);  // Set Pin 3 high
        for(delay_count = 0; delay_count < 200000; delay_count++ );  // Delay
        GPIO_PORTF_DATA_R &= ~(1 << 3); // Set Pin 3 low
        for(delay_count = 0; delay_count < 200000; delay_count++ );  // Delay
    }

    return 0;
}
