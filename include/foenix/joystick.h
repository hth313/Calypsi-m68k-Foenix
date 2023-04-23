#ifndef __A2560_JOYSTICK_H__
#define __A2560_JOYSTICK_H__

#include <stdint.h>

struct _Joystick {
  uint16_t atari_input;
#define JOY0_UP         0x0100
#define JOY0_DOWN       0x0200
#define JOY0_LEFT       0x0400
#define JOY0_RIGHT      0x0800
#define JOY0_BUTTON_0   0x1000
#define JOY0_BUTTON_1   0x4000
#define JOY0_BUTTON_2   0x8000
#define JOY1_UP         0x0001
#define JOY1_DOWN       0x0002
#define JOY1_LEFT       0x0004
#define JOY1_RIGHT      0x0008
#define JOY1_BUTTON_0   0x0010
#define JOY1_BUTTON_1   0x0040
#define JOY1_BUTTON_2   0x0080

  uint16_t reserved1;
  uint16_t nes_control;
#define NES_PORT_0_ENABLE  0x0001
#define NES_PORT_1_ENABLE  0x0002
#define NES_PORT_0_NES     0x0000
#define NES_PORT_0_SNES    0x0004
#define NES_PORT_1_NES     0x0000
#define NES_PORT_1_SNES    0x0008
#define NES_CAPTURE_DONE   0x0040
#define NES_START_CAPTURE  0x0080

  uint16_t reserved2;
  uint16_t nes_input[2][4];
#define NES_RIGHT        0x0001
#define NES_LEFT         0x0002
#define NES_DOWN         0x0004
#define NES_UP           0x0008
#define NES_START        0x0010
#define NES_SELECT       0x0020
#define NES_B            0x0040
#define NES_Y            0x0080
#define NES_R            0x0100
#define NES_L            0x0200
#define NES_X            0x0400
#define NES_A            0x0800

  uint16_t dip_switch;
#define BOOT_MODE_MASK   0x0003
#define USER_DIP_MASK    0x0700

  uint16_t sd_protect_and_detect;
#define SD_DETECT        0x0100
#define SD_WRITE_PROTECT 0x0200
};

#include <foenix/gavin.h>

#endif // __A2560_JOYSTICK_H__
