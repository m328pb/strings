# strings

low memory string functions for ATmega328. Intention is to avoid avr
implementation (not even to mention Arduino libs).
AVR by default implement only sprintf functions which already take ~948bytes.
Full version (including printf) use ~1730bytes. Just for completness, use
these compiler options: `-Wl,-u,vfprintf -lprintf_flt -lmpb`

This library footprint:

```bash
AVR Memory Usage
----------------
Device: Unknown

Program:     524 bytes
(.text + .data + .bootloader)

Data:          2 bytes
(.data + .bss + .noinit)
```

## functions

- str_find();
- str_cut();
- str_set();
- mem_set();
- str_len();
- str_compare();
- str_add();
- str_copy();
- mem_copy();
- ftos();
- stoi();
- btoi();
- str_concat();
