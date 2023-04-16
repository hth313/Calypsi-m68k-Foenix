// Header definitions for the SN76489 chip

#ifndef __A2560_PSG_H__
#define __A2560_PSG_H__

#include <stdint.h>

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define GavinBase 0x00b00000
#else
#define GavinBase 0xfec00000
#endif

#define PSG_LEFT  (* (volatile uint8_t*) (GavinBase + 0x0110) )
#define PSG_RIGHT (* (volatile uint8_t*) (GavinBase + 0x0120) )
#define PSG_MONO  (* (volatile uint8_t*) (GavinBase + 0x0130) )

#endif // __A2560_PSG_H__
