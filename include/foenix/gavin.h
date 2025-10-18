#ifndef __A2560_GAVIN_H__
#define __A2560_GAVIN_H__

#include <foenix/interrupt.h>
#include <foenix/joystick.h>
#include <foenix/rtc.h>
#include <foenix/system.h>
#include <foenix/timer.h>
#include <foenix/uart.h>

struct _CompleteGavin {
  union {
    struct _SystemControl system_control;
    char _skip_system_control[0x80];
  };

  union {
    struct _RTC rtc;
    char _skip_rtc[0x80];
  };

  union {
    struct _InterruptController interrupt_controller;
    char _skip_interrupt_controller[0x100];
  };

  union {
    struct _Timer timer;
    char _skip_timer[0x100];
  };

  char _skip_sdc[0x100];      // TBD

  char _skip_ide[0x100];      // TBD

  union {
    struct _Joystick joystick;
#if defined(__CALYPSI_TARGET_SYSTEM_A2560K__)
    char _skip_joystick[0x100];
#endif
#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
    char _skip_joystick[0x2800 - 0x0500];
#endif
  };

#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
  char _skip_ps2[0xf8];       // TBD

  struct _UART uart;
#endif

#if defined(__CALYPSI_TARGET_SYSTEM_A2560K__)
  char _skip_ethernet[0x100]; // TBD
  char _gap[0x900];           // TBD
  char _mau_argb[0x1060];     // TBD
  char ps2_buffer[4];
  union {
    uint8_t ps2_status; // read
    uint8_t ps2_cmd; // write;
    uint32_t _ps2_pad4;
  };
  uint8_t ps2_pad[0x197];
  uint8_t game_port; // analog joystick data port
  char _game_port_pad[0x78];
  struct _UART uart2;
  char _uart2_pad[0xaf];
  uint8_t midi_data;
  union {
    uint8_t midi_status; // read
    uint8_t midi_cmd;    // write
  };
  uint8_t _midi_pad[0x46];
  uint8_t parallel[8]; // TBD
  uint8_t _parallel_pad[0x70];
  uint8_t fdc[8]; // TBD
  struct _UART uart1;
#endif
};

#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
#define _CompleteGavin (*((struct _CompleteGavin volatile*)0x00b00000))
#endif

#if defined(__CALYPSI_TARGET_SYSTEM_A2560K__)
#define _CompleteGavin (*((struct _CompleteGavin volatile*)0xfec00000))
#endif

#define SystemControl        _CompleteGavin.system_control
#define RTC                  _CompleteGavin.rtc
#define InterruptController  _CompleteGavin.interrupt_controller
#define Timer                _CompleteGavin.timer
#define Joystick             _CompleteGavin.joystick
#if defined(__CALYPSI_TARGET_SYSTEM_A2560U__)
#define UART                 _CompleteGavin.uart
#endif
#if defined(__CALYPSI_TARGET_SYSTEM_A2560K__)
#define UART                 _CompleteGavin.uart1
#define UART2                _CompleteGavin.uart2
#endif

#endif // __A2560_GAVIN_H__
