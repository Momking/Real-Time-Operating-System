.globl kernelvec2
.align 4
kernelvec2:

        call intr_off

        la t0, TRAPFRAME

        ld ra, 0(t0)
        ld sp, 8(t0)
        ld gp, 16(t0)
        ld tp, 24(t0)
        ld x8, 32(t0)    # s0
        ld x9, 40(t0)    # s1
        ld x18, 48(t0)   # s2
        ld x19, 56(t0)   # s3
        ld x20, 64(t0)   # s4
        ld x21, 72(t0)   # s5
        ld x22, 80(t0)   # s6
        ld x23, 88(t0)   # s7
        ld x24, 96(t0)   # s8
        ld x25, 104(t0)  # s9
        ld x26, 112(t0)  # s10
        ld x27, 120(t0)  # s11
        
        jalr x0, ra, 0     # Jump to the address in ra (return to scheduler)
