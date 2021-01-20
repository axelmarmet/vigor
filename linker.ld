ENTRY(start)

SECTIONS
{
    . = 1M;

    .boot ALIGN(4K) :
    {
        *(.multiboot_header)
    }

    .text.start.32 ALIGN(4K) : 
    {
        *boot.o( .text.32 )
    }
    .text.start.64 ALIGN(4K) : 
    {
        *boot.o( .text.64 )
    }

    .text ALIGN(4K) :
    {
        *(.text)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
    }

    .data.start ALIGN(4K) :
    {
        *boot.o(.data)
    }

    .data ALIGN(4K) :
    {
        *(.data)
    }

    .rodata.start ALIGN(4K) :
    {
        *boot.o(.rodata)
    }
    .rodata ALIGN(4K) :
    {
        *(.rodata)
    }

    .bss.start ALIGN(4K) :
    {
        *boot.o(.bss)
    }

    .bss ALIGN(4K) :
    {
        *(.bss)
    }
}
