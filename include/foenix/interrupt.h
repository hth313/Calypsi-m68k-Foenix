// A2560 interrupt controller
//

#ifndef __A2560_INTERRUPT_H__
#define __A2560_INTERRUPT_H__

#include <stdint.h>

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define GavinBase 0x00b00000
#else
#define GavinBase 0xfec00000
#endif

struct InterruptBits {
  uint16_t vicky;
#define INT_VICKY_SOF               0x0001
#define INT_VICKY_SOL               0x0002
#define INT_VICKY_SPRITE_COLLISION  0x0004
#define INT_VICKY_BITMAP_COLLISION  0x0008
#define INT_VICKY_VDMA              0x0010
#define INT_VICKY_TILE_COLLISION    0x0020
#define INT_VICKY_HOT_PLUG          0x0080

  uint16_t gavin;
#define INT_PS2_KEYBOARD            0x0001
#define INT_PS_MOUSE                0x0004
#define INT_COM1                    0x0008
#define INT_TIMER0                  0x0100
#define INT_TIMER1                  0x0200
#define INT_TIMER2                  0x0400
#define INT_TIMER_SOF               0x0800
#define INT_RTC                     0x8000

  uint16_t beatrix;
#define INT_IDE                     0x0001
#define INT_SD_CARD_INSERT          0x0002
#define INT_OPL3                    0x0020
#define INT_DAC0_PLAYBACK           0x8000

  uint16_t reserved;
};

typedef struct {
  struct InterruptBits pending;
  struct InterruptBits polarity;      // not in use
  struct InterruptBits edge;          // not in use
  struct InterruptBits mask;
} InterruptController_t;

#define InterruptController  (* (volatile InterruptController_t*) (GavinBase + 0x100))

#endif // __A2560_INTERRUPT_H__
