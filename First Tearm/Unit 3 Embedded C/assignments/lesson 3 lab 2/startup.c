#include <stdint.h>


extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _stack_top;

extern int main();
void ResetHandler(void);

void Default_Handler(void)
{
    ResetHandler();
}

// Weak aliases for interrupt handlers
void NMIHandler(void) __attribute__((weak, alias("Default_Handler")));
void HardfaultHandler(void) __attribute__((weak, alias("Default_Handler")));

// Vector table
uint32_t _init[] __attribute__((section(".vectors"))) = {
    (uint32_t) &_stack_top,
    (uint32_t) &ResetHandler,
    (uint32_t) &NMIHandler,
    (uint32_t) &HardfaultHandler
};


void ResetHandler(void)
{
    // Copy .data section from flash to SRAM
    unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
    unsigned char* P_src = (unsigned char*)&_E_text;
    unsigned char* P_dst = (unsigned char*)&_S_DATA;

    for (unsigned int i = 0; i < DATA_size; i++) {
        *((uint8_t*)P_dst++) = *((uint8_t*)P_src++);
    }

    // Initialize .bss section to zero
    unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
    P_dst = (unsigned char*)&_S_bss;

    for (unsigned int i = 0; i < bss_size; i++) {
        *((uint8_t*)P_dst++) = (uint8_t)0;
    }

    // Call main function
    main();
}
