ENTRY(reset)

MEMORY
{
    Men (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}

SECTIONS
{	
	. = 0x10000;
    .startup . :
    {
        startup.o(.text)
    } > Men

    .text :
    {
        *(.text)
        *(.text*)
    } > Men

    .data :
    {
        *(.data)
        *(.data*)
    } > Men

    .bss :
    {
        *(.bss)
        *(.bss*)
    } > Men
    . = . + 0x1000;
    stack_top = . ;

    _end = .;
}
