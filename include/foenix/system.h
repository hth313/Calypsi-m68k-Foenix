// A2560 System control registers
//
// These controls LEDs, buzzer, LFSR (pseudo random number) and holds
// identity values about the machine.

#ifndef __A2560_SYSTEM_H__
#define __A2560_SYSTEM_H__

#include <stdint.h>
#include "foenix/types.h"

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define GavinBase 0x00b00000
#else
#define GavinBase 0xfec00000
#endif

typedef struct _SystemControl {
  union {
    struct {
      uint16_t power_led         : 1;
      uint16_t sd_led            : 1;
      uint16_t                   : 2;
      uint16_t buzzer            : 1;
      uint16_t                   : 3;
      uint16_t                   : 7;
      uint16_t manual_reset      : 1;
    };
    uint16_t control;
  };
  uint16_t security_word;
  union {
    struct {
      uint16_t lfsr_enable       : 1;
      uint16_t seed_write        : 1;
      uint16_t                   : 6;
      uint16_t                   : 8;
    };
    uint16_t lfsr_control;
  };
  uint16_t seed;
  uint16_t random;
  union {
    struct {
      uint16_t lfsr_ctrl         : 7;
      uint16_t lfsr_done         : 1;
    };
    uint16_t lfsr_status;
  };
  union {
    struct {
      uint16_t id                : 4;
      uint16_t                   : 1;
      uint16_t speed             : 3;
      uint16_t cpu_id            : 8;
      };
    uint16_t machine_id;
  };
  uint16_t reserved;
  uint16_t byteOrderHigh;        // 0x4567
  uint16_t byteOrderLow;         // 0x1234
} SystemControl_t;

typedef enum MachineID {
  Machine_FMX, Machine_C256U, Machine_C256JR, Machine_A2560DEV,
  Machine_GenX, Machine_C256UPlus, Machine_Reserved1, Machine_Reserved2,
  Machine_A2560X, Machine_A2560U, Machine_A2560M, Machine_A2560K
} MachineID_t;

#define SystemControl (* (volatile SystemControl_t*) GavinBase)

#endif // __A2560_SYSTEM_H__
