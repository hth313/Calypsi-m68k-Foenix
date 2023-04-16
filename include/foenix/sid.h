#ifndef __A2560_SID_H__
#define __A2560_SID_H__

#include <stdint.h>

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define GavinBase 0x00b00000
#else
#define GavinBase 0xfec00000
#endif

struct sid_voice {
  uint8_t freq_low;
  uint8_t freq_high;
  uint8_t pw_low;
  uint8_t pw_high;
  uint8_t control;
#define SID_GATE       0x01
#define SID_SYNC       0x02
#define SID_RING_MOD   0x04
#define SID_TEST       0x08
#define SID_TRIANGLE   0x10
#define SID_SAW_TOOTH  0x20
#define SID_SQUARE     0x40
#define SID_NOICE      0x80
  uint8_t attack_decay;
  uint8_t sustain_release;
};

typedef struct sid {
  struct sid_voice voice[3];
  uint8_t filter_fc_low;
  uint8_t filter_fc_high;
  uint8_t filter_res_filt;
  uint8_t filter_mode_vol;
  uint8_t potx;
  uint8_t poty;
  uint8_t osc3_random;
  uint8_t env3;
} sid_t;

#define SID_LEFT  (* (volatile sid_t*) (GavinBase + 0x1000) )
#define SID_RIGHT (* (volatile sid_t*) (GavinBase + 0x1200) )
#define SID_MONO  (* (volatile sid_t*) (GavinBase + 0x1400) )

#endif // __A2560_SID_H__
