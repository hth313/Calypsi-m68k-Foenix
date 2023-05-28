// Header definitions for the YMF262 chip

#ifndef __A2560_OPL3_H__
#define __A2560_OPL3_H__

#include <stdint.h>

struct _OPL3 {
  uint8_t test;
  uint8_t timer1;
  uint8_t timer2;

  uint8_t irq;
#define OPL3_RST    0x80
#define OPL3_MT1    0x40
#define OPL3_MT2    0x20
#define OPL3_ST2    0x02
#define OPL3_ST1    0x01

  uint8_t set_mode;
  uint8_t _reserved1[2];

  uint8_t csm;
#define OPL3_NTS    0x40

  uint8_t am_vib_egt_ksr_mult[0x20];
#define OPL3_AM     0x80
#define OPL3_VIB    0x40
#define OPL3_EGT    0x20
#define OPL3_KSR    0x10
#define OPL3_MULT_MASK  0x0f

  uint8_t ksl_tl[0x20];
#define OPL3_KSL_SHIFT   6
#define OPL3_TL_MASK  0x3f

  uint8_t ar_dr[0x20];
  uint8_t sl_rr[0x20];
  uint8_t fnum[9];
  uint8_t _reserved2[7];

  uint8_t kon_block_fnum[9];
#define OPL3_KON      0x20
#define OPL3_BLOCK_MASK 0x1a
#define OPL3_FNUM_MASK  0x03

  uint8_t _reserved3[4];
  uint8_t depth_rythm;
#define OPL3_DAM      0x80
#define OPL3_DVB      0x40
#define OPL3_RYT      0x20
#define OPL3_BD       0x10
#define OPL3_SD       0x08
#define OPL3_TOM      0x04
#define OPL3_TC       0x02
#define OPL3_HH       0x01

  uint8_t _reserved4[2];

  uint8_t feedback[9];
#define OPL3_CHD      0x80
#define OPL3_CHC      0x40
#define OPL3_CHB      0x20
#define OPL3_CHA      0x10
#define OPL3_FB_MASK  0x0e
#define OPL3_CNT      0x01

  uint8_t _reserved5[7+16];
  uint8_t wave_select[16+6];
};

#include <foenix/beatrix.h>

#endif // __A2560_OPL3_H__
