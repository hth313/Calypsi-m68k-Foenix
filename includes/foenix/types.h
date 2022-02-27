#ifndef __FOENIX_TYPES_H__
#define __FOENIX_TYPES_H__

// Define natural register width if not specified. This describes whether
// this is a 16 or 32 bit system.
#ifndef __FOENIX_A2560_REGISTER_SIZE__
#ifdef __CALYPSI_CORE_68000__
#define __FOENIX_A2560_REGISTER_SIZE__ 16
#else
#define __FOENIX_A2560_REGISTER_SIZE__ 32
#endif
#endif // __FOENIX_A2560_REGISTER_WIDTH__


#endif // __FOENIX_TYPES_H__
