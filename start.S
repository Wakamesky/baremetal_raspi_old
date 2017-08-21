.align 4
.global _start
_start:

// edit interrupt rule
	cpsid aif


// initialize stack pointer
	ldr sp, =0x1c000000

// initialize bss
	ldr r0 , =__bss_start	// r0 = __bss_start
	ldr r1 , =__bss_end	// r1 = __bss_end
	mov r2 , #0
	cmp r0, r1		// r0 - r1 = ?
	beq startmain		// if r0 != r1 then go to  _main

loop:
	str r2, [r0], #4
	cmp r0, r1
	bmi loop

// branch to main
startmain:
	bl jtag_setup_asm
	bl main

// ???  back to _start
	bx lr

jtag_setup_asm:
    ldr r1, =0x20200000 @ load GPFSEL address
    ldr r2, =0xffff8fff @ load GPIO4 mask
    ldr r3, =0xff1c0e3f @ load GPIO22,24,25,27 mask
    ldr r4, [r1, #0]    @ load GPFSEL0 value
    ldr r5, [r1, #8]    @ load GPFSEL2 value
    and r4, r4, r2      @ clear GPIO4 mode
    and r5, r5, r3      @ clear GPIO22,24,25,27 mode
    ldr r2, =0x00002000 @ load GPIO4 ALT4
    ldr r3, =0x0061b0c0 @ load GPIO22,24,25,27 ALT5
    orr r4, r4, r2      @ set GPIO4 mode to ALT4
    orr r5, r5, r3      @ set GPIO22,24,25,27 mode to ALT5
    str r4, [r1, #0]    @ save GPFSEL0 value
    str r5, [r1, #8]    @ save GPFSEL2 value
    bx lr
