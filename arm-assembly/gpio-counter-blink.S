@ R0 - first parameter to printf
@ R1 - second parameter to printf
@ R7 - index counter

#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/pads_bank0.h"

       .EQU PIN, 20

.thumb_func                 @ Tells the assembler to use Thumb names
.global main                @ Tells the linker that this file is the "main" file

       .align 4
main:                       @ Label
        BL  stdio_init_all  @ Tell sdk to init UART/USB
        MOV R7, #0
        MOV R3, #1
        MOV R0, #PIN
        LSL R3, R0
        LDR R2, gpiobase
        STR R3, [R2, #SIO_GPIO_OE_SET_OFFSET]
        STR R3, [R2, #SIO_GPIO_OUT_CLR_OFFSET]
        LDR R2, padsbank0
        LSL R3, R0, #2
        ADD R2, R3
        MOV R1, #PADS_BANK0_GPIO0_IE_BITS
        LDR R4, setoffset
        ORR R2, R4
        STR R1, [R2, #PADS_BANK0_GPIO0_OFFSET]
        LSL R0, #3
        LDR R2, iobank0
        ADD R2, R0
        MOV R1, #IO_BANK0_GPIO3_CTRL_FUNCSEL_VALUE_SIO_3
        STR R1, [R2, #IO_BANK0_GPIO0_CTRL_OFFSET]

loop:
        ADD R7, #1
        MOV R1, R7
        LDR R0, =tests      @ Load String
        BL  printf          @ Run the printf function from the sdk

        MOV R0, #PIN
        BL  gpio_on
        BL  delay

        MOV R0, #PIN
        BL  gpio_off
        BL  delay

        B   loop

delay:
        MOV R4, #0xFF
        MOV R6, #0xFF
        LSL R4, #8
        ORR R4, R6
        LSL R4, #8
        ORR R4, R6
time:
        SUB R4, #1
        BPL time

        MOV R4, #0xFF
        MOV R6, #0xFF
        LSL R4, #8
        ORR R4, R6
        LSL R4, #8
        ORR R4, R6
time1:
        SUB R4, #1
        BPL time1

        MOV R4, #0xFF
        MOV R6, #0xFF
        LSL R4, #8
        ORR R4, R6
        LSL R4, #8
        ORR R4, R6
time2:
        SUB R4, #1
        BPL time2
        BX  LR

gpio_on:
        MOV R3, #1
        LSL R3, R0
        LDR R2, gpiobase
        STR R3, [R2, #SIO_GPIO_OUT_SET_OFFSET]
        BX  LR

gpio_off:
        MOV R3, #1
        LSL R3, R0
        LDR R2, gpiobase
        STR R3, [R2, #SIO_GPIO_OUT_CLR_OFFSET]
        BX  LR

          .align 4            @ alignment for data readability
iobank0:  .word IO_BANK0_BASE
gpiobase: .word SIO_BASE
padsbank0: .word PADS_BANK0_BASE
setoffset: .word REG_ALIAS_SET_BITS

.data                       @ Special label for predefined
         .align 4            @ alignment for data readability
tests:   .asciz "The value is %d\n"