.section .text
.global _entry

_entry:
	la sp, kstack
	li a0, 4096
	add sp, sp, a0
	call kmain
spin:
	j spin
