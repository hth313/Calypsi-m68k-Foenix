;;; Startup variant, change attribute value if you make your own
              .rtmodel cstartup,"Foenix"

              .rtmodel version, "1"

              ;; External declarations
              .section sstack
              .section stack
              .section heap
              .section data_init_table

              .extern __initialize_data, __initialize_udata
              .extern main, exit

#ifdef __CALYPSI_DATA_MODEL_SMALL__
              .extern _NearBaseAddress
#endif

#include "macros.h"

;;; ***************************************************************************
;;;
;;; The reset vector. This uses the entry point label __program_root_section
;;; which by default is what the linker will pull in first.
;;;
;;; ***************************************************************************

              .section reset
              .pubweak __program_root_section
__program_root_section:
              .long   .sectionEnd sstack + 1
              .long   __program_start

;;; ***************************************************************************
;;;
;;; __program_start - actual start point of the program
;;;
;;; Initialize sections and call main().
;;; You can override this with your own routine, or tailor it as needed.
;;; The easiest way to make custom initialization is to provide your own
;;; __low_level_init which gets called after stacks have been initialized.
;;;
;;; ***************************************************************************

              .section libcode, noreorder
              .pubweak __program_start
              .align  2
__program_start:
              move.l  #.sectionEnd stack + 1,a0
              move.l  a0,usp
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              lea.l   _NearBaseAddress.l,a4
#endif
              call     __low_level_init
              tst.l   d0            ; stay in supervisor?
              bne.s   10$           ; yes
              andi.w  #~0x2000,sr   ; no, drop out of supervisor
10$:

;;; Initialize data sections if needed.
              .section libcode, noroot, noreorder
              .public __data_initialization_needed
              .extern __initialize_sections
              .align  2
__data_initialization_needed:
              move.l  #(.sectionStart data_init_table),a0
              move.l  #(.sectionEnd data_init_table),a1
              call    __initialize_sections

;;; **** Initialize streams if needed.
              .section libcode, noroot, noreorder
              .pubweak __call_initialize_global_streams
              .extern __initialize_global_streams
__call_initialize_global_streams:
              call    __initialize_global_streams

;;; **** Initialize heap if needed.
              .section libcode, noroot, noreorder
              .pubweak __call_heap_initialize
              .extern __heap_initialize, __default_heap
__call_heap_initialize:
              move.l  #.sectionSize heap,d0
              move.l  #__default_heap,a0
              move.l  #.sectionStart heap,a1
              call    __heap_initialize

              .section libcode, root, noreorder
              moveq.l #0,d0         ; argc = 0
              call    main
              jump    exit

;;; ***************************************************************************
;;;
;;; __low_level_init - custom low level initialization
;;;
;;; This default routine just returns doing nothing. You can provide your own
;;; routine, either in C or assembly for doing custom low leve initialization.
;;;
;;; ***************************************************************************

              .section code
              .pubweak __low_level_init
              .align  2
__low_level_init:
              moveq.l #0,d0         ; switch to user mode
              rts
