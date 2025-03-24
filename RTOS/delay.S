.globl delay
.align 4
delay:
    la t0, TRAPFRAME
    
    # save the user registers in TRAPFRAME
    

    sd ra, 0(t0)
    sd sp, 8(t0)
    sd gp, 16(t0)
    sd tp, 24(t0)
    sd x8, 32(t0)    # s0
    sd x9, 40(t0)    # s1
    sd x18, 48(t0)   # s2
    sd x19, 56(t0)   # s3
    sd x20, 64(t0)   # s4
    sd x21, 72(t0)   # s5
    sd x22, 80(t0)   # s6
    sd x23, 88(t0)   # s7
    sd x24, 96(t0)   # s8
    sd x25, 104(t0)  # s9
    sd x26, 112(t0)  # s10
    sd x27, 120(t0)  # s11



    
    call set_timer_interrupt_at


spin:
    j spin
