/*
 * File: linker_script.ld
 * Author: Eng. Abdallah Ghazy
 * 
 * Description:
 * This linker script is designed for the STM32F103x6 microcontroller with a Cortex-M3 core.
 * It specifies memory regions and section placements for the build process.
 * The script outlines memory regions, including flash and SRAM, and maps various sections of 
 * the code to these regions. The linker script ensures that the vector table, code, and data 
 * sections are placed correctly in memory, and handles the initialization of the stack and 
 * zeroing of the .bss section.
 * 
 * Memory Layout:
 * - flash (rx): Read-Execute region starting at 0x08000000 with a length of 32KB.
 * - sram (rwx): Read-Write-Execute region starting at 0x20000000 with a length of 20KB.
 * 
 * Sections:
 * - .vectors: Contains the vector table with interrupt handlers and the initial stack pointer.
 * - .text: Contains the executable code and read-only data. Placed in flash.
 * - .data: Contains initialized data that is copied from flash to SRAM during startup.
 * - .bss: Contains uninitialized data, which is zeroed during startup. The section also reserves
 *   additional space for the stack.
 * 
 * Usage:
 * - Ensure that the linker script is referenced in your build configuration to correctly place
 *   sections in the memory regions defined.
 * - Modify the memory regions and section placements if using a different microcontroller
 *   or if memory configurations change.
 * 
 * Notes:
 * - The script assumes a typical memory layout for the STM32F103x6 microcontroller.
 * - Adjust the lengths and starting addresses if the memory layout differs from the assumed
 *   configuration.
 * 
 * License:
 * - This script is provided "as is" without any warranties. Use it at your own risk.
 * 
 * Date: [8/12/2024]
 */

MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 32K
    sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{ 
    .vectors : {
        *(.vectors*)
        _E_vectors = .;
    } >flash

    .text : {
        *(.text*)
        *(.rodata*)
        _E_text = .;
    } >flash

    .data : 
    {
        _S_DATA = .;
        *(.data*)
        . = ALIGN(4);
        _E_DATA = .;
    } >sram AT> flash

    .bss : 
    {
        _S_bss = .;
        *(.bss*)
        . = ALIGN(4);
        _E_bss = .;
        . = . + 0x1000; 
        _stack_top = .;
    } >sram
}
