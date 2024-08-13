/* linker script cortexM3 STM32F103x6
Eng. Abdallah Ghazy
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
