#ifndef __A2560_BEATRIX_H__
#define __A2560_BEATRIX_H__

#include <stdint.h>
#include <foenix/opl3.h>
#include <foenix/psg.h>
#include <foenix/sid.h>

struct _CompleteBeatrix {
  char _skip_control[0x110];

  union {
    union {
      uint8_t psg_left;
      char _skip_psg_left[0x10];
    };
    union {
      uint8_t psg_right;
      char _skip_psg_right[0x10];
    };
    union {
      uint8_t psg_mono;
      char _skip_psg_mono[0x10];
    };
    char _skip_psg[0x201 - 0x110];
  };

  union {
    union {
      struct _OPL3 opl3_right;
      char _skip_opl3_right[0x100];
    };
    union {
      struct _OPL3 opl3_left;
      char _skip_opl3_left[0x100];
    };
    char _skip_opl3[0x0e00 - 0x201];
  };

  char _skip_codec[0x200];

  union {
    union {
      struct _SID sid_left;
      char _skip_sid_left[0x100];
    };
    union {
      struct _SID sid_right;
      char _skip_sid_right[0x100];
    };
    union {
      struct _SID sid_mono;
      char _skip_sid_mono[0x100];
    };
    char _skip_sid[0x1000];
  };
};

// Vicky base address has been set up by C startup.
#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
#define _CompleteBeatrix ((struct _CompleteBeatrix volatile*)0x00b20000)
#endif

#if defined(__CALYPSI_TARGET_SYSTEM_A2560K__)
#define _CompleteBeatrix ((struct _CompleteBeatrix volatile*)0xfec20000)
#endif

#define PSG                  _CompleteBeatrix.psg
#define OPL3_RIGHT           _CompleteBeatrix.opl3_right
#define OPL3_LEFT            _CompleteBeatrix.opl3_left
#define SID_LEFT             _CompleteBeatrix.sid_left
#define SID_RIGHT            _CompleteBeatrix.sid_right
#define SID_MONO             _CompleteBeatrix.sid_mono

#endif // __A2560_BEATRIX_H__
