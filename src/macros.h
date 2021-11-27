#ifndef __MACROS_H
#define __MACROS_H

#ifdef __CALYPSI_ASSEMBLER__

#ifdef __CALYPSI_CODE_MODEL_SMALL__

#define libcode nearcode

call          .macro  dest
              bsr.w     \dest
              .endm

jump          .macro  dest
              bra.w   \dest
              .endm

#else

#define libcode code

call          .macro  dest
              jsr     \dest
              .endm

jump          .macro  dest
              jmp     \dest
              .endm

#endif // __CALYPSI_CODE_MODEL_SMALL__

#endif // __CALYPSI_ASSEMBLER__
#endif // __MACROS_H
