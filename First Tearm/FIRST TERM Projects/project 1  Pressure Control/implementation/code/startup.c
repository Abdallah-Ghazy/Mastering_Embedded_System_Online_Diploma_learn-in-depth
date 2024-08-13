/* 
 * File: startup.c
 * Author: Eng. Abdallah Ghazy
 * 
 * Description:
 * This file contains the startup code for the STM32F103x6 microcontroller. 
 * It includes the vector table and the Reset Handler. The vector table 
 * defines the initial stack pointer and handlers for various exceptions 
 * and interrupts. The Reset Handler is responsible for initializing 
 * the data and bss sections and then calling the main function.
 * 
 * Vector Table:
 * - _stack_top: Initial stack pointer.
 * - ResetHandler: Called on reset, initializes data and bss sections.
 * - NMIHandler: Non-Maskable Interrupt Handler (weak alias to Default_Handler).
 * - HardfaultHandler: Hard Fault Handler (weak alias to Default_Handler).
 * - MemManage_Handler: Memory Management Fault Handler (weak alias to Default_Handler).
 * - BusFault_Handler: Bus Fault Handler (weak alias to Default_Handler).
 * - UsageFault_Handler: Usage Fault Handler (weak alias to Default_Handler).
 * - SVC_Handler: Supervisor Call Handler (weak alias to Default_Handler).
 * - DebugMon_Handler: Debug Monitor Handler (weak alias to Default_Handler).
 * - PendSV_Handler: PendSV Handler (weak alias to Default_Handler).
 * - SysTick_Handler: SysTick Timer Handler (weak alias to Default_Handler).
 * 
 * Usage:
 * - Ensure that the linker script correctly places sections in the memory.
 * - The `ResetHandler` function must be defined to initialize the microcontroller
 *   and set up the memory before calling the `main` function.
 * - Interrupt handlers can be customized by defining the corresponding functions
 *   with the appropriate names and linking them to this file.
 * 
 * Notes:
 * - This code assumes that the linker script defines memory regions
 *   and section placement correctly.
 * - Modify the weak aliases and handlers as needed for your specific application.
 * 
 * License:
 * - This code is provided "as is" without any warranties. Use it at your own risk.
 * 
 * Date: [8/12/2024]
 */

#include <stdint.h>

extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _stack_top;

extern int main();
void ResetHandler(void);
void Default_Handler(void);

void Default_Handler(void)
{
    ResetHandler();
}

// Weak aliases for interrupt handlers
void NMIHandler(void) __attribute__((weak, alias("Default_Handler")));
void HardfaultHandler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

// Vector table
uint32_t _init[] __attribute__((section(".vectors"))) = {
    (uint32_t) &_stack_top,            // Initial stack pointer
    (uint32_t) &ResetHandler,          // Reset Handler
    (uint32_t) &NMIHandler,            // NMI Handler
    (uint32_t) &HardfaultHandler,      // HardFault Handler
    (uint32_t) &MemManage_Handler,     // MemManage Handler
    (uint32_t) &BusFault_Handler,      // BusFault Handler
    (uint32_t) &UsageFault_Handler,    // UsageFault Handler
    (uint32_t) 0,                      // Reserved
    (uint32_t) 0,                      // Reserved
    (uint32_t) 0,                      // Reserved
    (uint32_t) 0,                      // Reserved
    (uint32_t) &SVC_Handler,           // SVC Handler
    (uint32_t) &DebugMon_Handler,      // DebugMon Handler
    (uint32_t) &PendSV_Handler,        // PendSV Handler
    (uint32_t) &SysTick_Handler        // SysTick Handler
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
