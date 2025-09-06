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

#if defined (__CALYPSI_TARGET_SYSTEM_A2560K__) || defined (__CALYPSI_TARGET_SYSTEM_A2560U__)
              .extern _Gavin
              .extern _Beatrix
              .extern _Vicky
              .extern _VickyBaseVRAM

# define GavinLow   0x00b00000
# define BeatrixLow 0x00b20000
# define VickyLow   0x00b40000
# define VickyBaseVRAMLow 0x00c00000

# define GavinHigh   0xfec00000
# define BeatrixHigh 0xfec20000
# define VickyHigh   0xfec40000
# define VickyBaseVRAMHigh 0x00800000
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

              .section libcode, noroot, noreorder
#if defined (__CALYPSI_TARGET_SYSTEM_A2560K__) || defined (__CALYPSI_TARGET_SYSTEM_A2560U__)
              .pubweak _Gavin_initialize
_Gavin_initialize:
              move.l  #GavinLow,a0  ; assume A2560U system
              move.l  #BeatrixLow,a2
              move.l  #VickyLow,a1
              move.l  #VickyBaseVRAMLow,d0
              cmp.w   #0x4567,0x0010(a0) ; check byte order
              beq.s   20$
              move.l  #GavinHigh,a0 ; no, assume A2560K 32-bit
              move.l  #BeatrixHigh,a2
              move.l  #VickyHigh,a1
              move.l  #VickyBaseVRAMHigh,d0
20$:
              ;; keep base pointer to Gavin
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              move.l  a0,(.near _Gavin,A4)
              move.l  a2,(.near _Beatrix,A4)
              move.l  a1,(.near _Vicky,A4)
              move.l  d0,(.near _VickyBaseVRAM,A4)
#else
              move.l  a0,_Gavin
              move.l  a2,_Beatrix
              move.l  a1,_Vicky
              move.l  d0,_VickyBaseVRAM
#endif // __CALYPSI_DATA_MODEL_SMALL__
#endif // __CALYPSI_TARGET_SYSTEM_A2560K__ || __CALYPSI_TARGET_SYSTEM_A2560U__

              .section libcode, root, noreorder
              moveq.l #0,d0         ; argc = 0
              call    main
              jump    exit
