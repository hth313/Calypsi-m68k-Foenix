              .rtmodel version, "1"
              .rtmodel cpu, "*"
;;;
;;; Function to make a system call based on the number of the system function:
;;; int32_t syscall(int32_t number, int32_t p0, int32_t p1, int32_t p2, int32_t p3, int32_t p4, int32_t p5)
;;;
              .public syscall
              .section code
              .align  2
syscall:
              movem.l d2-d6,-(sp)   ; Save caller's registers
              movem.l (a0)+,d1-d6
              trap    #15           ; Call into the kernel
              movem.l (sp)+,d2-d6   ; Restore caller's registers
              rts
