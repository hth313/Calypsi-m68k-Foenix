	.rtmodel version, "1"
	.rtmodel cpu, "*"
;
; Function to make a system call based on the number of the system function:
; int32_t syscall(int32_t number, int32_t p0, int32_t p1, int32_t p2, int32_t p3, int32_t p4, int32_t p5)
;
	.public _syscall
	.section code
	.align 2
_syscall:
    movem.l d1-d7,-(sp)         ; Save caller's registers
    move.l (56,sp),d6           ; Parameter 5 to D6
    move.l (52,sp),d5           ; Parameter 4 to D5
    move.l (48,sp),d4           ; Parameter 3 to D4
    move.l (44,sp),d3           ; Parameter 2 to D3
    move.l (40,sp),d2           ; Parameter 1 to D2
    move.l (36,sp),d1           ; Parameter 0 to D1
    move.l (32,sp),d0           ; Function number to D0

    trap #15                    ; Call into the kernel

    movem.l (sp)+,d1-d7         ; Restore caller's registers
    rts
