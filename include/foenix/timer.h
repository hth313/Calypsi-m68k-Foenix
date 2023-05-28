#ifndef __A2560_TIMER_H__
#define __A2560_TIMER_H__

#include <stdint.h>

struct timer_entity {
  uint32_t value;
  uint32_t compare;
};

struct _Timer {
  uint32_t control0;
#define TIMER0_ENABLE            0x00000001
#define TIMER0_CLEAR             0x00000002
#define TIMER0_LOAD              0x00000004
#define TIMER0_UP_DOWN           0x00000008
#define TIMER0_ENABLE_RECLEAR    0x00000010
#define TIMER0_ENABLE_RELOAD     0x00000020
#define TIMER0_INTERRUPT_ENABLE  0x00000080

#define TIMER1_ENABLE            0x00000100
#define TIMER1_CLEAR             0x00000200
#define TIMER1_LOAD              0x00000400
#define TIMER1_UP_DOWN           0x00000800
#define TIMER1_ENABLE_RECLEAR    0x00001000
#define TIMER1_ENABLE_RELOAD     0x00002000
#define TIMER1_INTERRUPT_ENABLE  0x00008000

#define TIMER2_ENABLE            0x00010000
#define TIMER2_CLEAR             0x00020000
#define TIMER2_LOAD              0x00040000
#define TIMER2_UP_DOWN           0x00080000
#define TIMER2_ENABLE_RECLEAR    0x00100000
#define TIMER2_ENABLE_RELOAD     0x00200000
#define TIMER2_INTERRUPT_ENABLE  0x00800000

#define TIMER3_ENABLE            0x01000000
#define TIMER3_CLEAR             0x02000000
#define TIMER3_LOAD              0x04000000
#define TIMER3_UP_DOWN           0x08000000
#define TIMER3_ENABLE_RECLEAR    0x10000000
#define TIMER3_ENABLE_RELOAD     0x20000000
#define TIMER3_INTERRUPT_ENABLE  0x80000000

  uint32_t control1;
#define TIMER0_COMPARE_EQUAL     0x08000000
#define TIMER1_COMPARE_EQUAL     0x10000000
#define TIMER2_COMPARE_EQUAL     0x20000000
#define TIMER3_COMPARE_EQUAL     0x40000000

  struct timer_entity entity[4];
};

#include <foenix/gavin.h>

#endif // __A2560_TIMER_H__
