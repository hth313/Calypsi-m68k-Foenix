;;; This startup is for loading into memory as a hex file using C256Mgr.
;;; In this case we need to populate the reset vector and will start in
;;; supervisor mode.

              .rtmodel cstartup,"Foenix_morfe"

              .rtmodel version, "1"
              .rtmodel core, "*"

              ;; External declarations
              .section heap
              .section stack
              .section data_init_table

              .extern __initialize_data, __initialize_udata
              .extern main, exit

#ifdef __CALYPSI_DATA_MODEL_SMALL__
              .extern _NearBaseAddress
#endif

#include "macros.h"

;;; ***************************************************************************
;;;
;;; __program_start - actual start point of the program
;;;
;;; Initialize sections and call main(). Currently this startup does not
;;; handle command line arguments from the mcp.
;;;
;;; ***************************************************************************

              .section libcode, noreorder
              .pubweak __program_start, __program_root_section
              .align  2
__program_root_section:
__program_start:
              move.l  #.sectionEnd stack + 1,a0
              move.l  a0,usp
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              lea.l   _NearBaseAddress.l,a4
#endif
              andi.w  #~0x2000,sr   ; no, drop out of supervisor

;;; Initialize data sections if needed.
              .section libcode, noroot, noreorder
              .pubweak __data_initialization_needed
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
