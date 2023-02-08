#ifndef __VICKY_H__
#define __VICKY_H__

#include <stdint.h>
#include "foenix/types.h"

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define VICKY_BASE  0x00b40000
#define VRAM_BASE   0x00800000
#define VRAM_BASE_A VRAM_BASE
#endif

#if __FOENIX_A2560_REGISTER_SIZE__ == 32
#define VICKY_BASE  0xfec40000
#define VRAM_BASE   0x00800000
#define VRAM_BASE_A VRAM_BASE
#define VRAM_BASE_B 0x00c00000
#endif

// ----------------------------------------------------------------------
//
// Vicky
//
// ----------------------------------------------------------------------

typedef struct _Vicky Vicky_t;

// Vicky registers
#define Vicky (* (Vicky_t volatile __far *) VICKY_BASE)

typedef uint8_t * vram_ptr;

typedef union {
  struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
  };
  uint32_t reg;
} color_t;

struct _Vicky {
  union {                       // master control register
    struct {
      uint32_t text_mode_enable         : 1;
      uint32_t text_mode_overlay_enable : 1;
      uint32_t graphic_mode_enable      : 1;
      uint32_t bitmap_engine_enable     : 1;
      uint32_t tile_engine_enable       : 1;
      uint32_t sprite_engine_enable     : 1;
      uint32_t                          : 1;
      uint32_t disable_video_display    : 1;
      uint32_t video_mode0              : 1;
      uint32_t video_mode1              : 1;
      uint32_t double_pixel_mode        : 1;
      uint32_t                          : 2;
      uint32_t gamma_dipswitch_value    : 1;   // read-only
      uint32_t hires_dipswitch_value    : 1;   // read-only
      uint32_t active_clock             : 1;   // read-only
      uint32_t gamma_choice_input       : 1;
      uint32_t gamma_enable             : 1;
      uint32_t display_sleep            : 1;   // turn sync off
      uint32_t                          : 5;
      uint32_t                          : 8;
    };
    uint32_t reg;
  } master_control;
  struct {
    union {                     // border control register
      struct {
        uint32_t enable:1;
        uint32_t  :3;
        uint32_t scroll_x:3;
        uint32_t  :1;
        uint32_t x:6;
        uint32_t  :2;
        uint32_t y:6;
        uint32_t  :2;
        uint32_t  :8;
      };
      uint32_t control;
    };
    color_t color;              // border color register
  } border;
  color_t background_color;     // background color register
  union {                       // cursor control register
    struct {
      uint32_t enable:1;
      uint32_t flash_rate:2;    // see 'enum cursor_flash_rate' below
      uint32_t font_set:2;      // see 'enum cursor_font_size' below
      uint32_t font_size:1;
      uint32_t  :2;
      uint32_t x_offset:8;
      uint32_t cursor_char:8;
      uint32_t background_color:4;
      uint32_t foreground_color:4;
    };
    uint32_t reg;
  } cursor_control;
  union {                       // cursor position register
    struct {
      uint32_t x:16;
      uint32_t y:16;
    };
    uint32_t reg;
  } cursor_position;
#if __FOENIX_A2560_REGISTER_SIZE__ == 16
  union {                       // line interrupt register (4 of them)
    union {
      struct {
        uint16_t enable:1;
        uint16_t  :3;
        uint16_t compare:12;
      };
      uint16_t reg;
    } line_interrupt[4]; // note: indexed style only works on 16 bit system
    union {
      struct {
        uint16_t enable0:1;
        uint16_t  :3;
        uint16_t compare0:12;
        uint16_t enable1:1;
        uint16_t  :3;
        uint16_t compare1:12;
      } line_interrupt_01;
      struct {
        uint16_t enable2:1;
        uint16_t  :3;
        uint16_t compare2:12;
        uint16_t enable3:1;
        uint16_t  :3;
        uint16_t compare3:12;
      } line_interrupt_23;
      uint16_t reg0;
      uint16_t reg1;
      uint16_t reg2;
      uint16_t reg3;
    };
  };
  uint16_t reserved[8];
  uint16_t FPGA_load_date[2];
  uint16_t PCB_revision[2];
  uint16_t FPGA_version[2];
  uint16_t FPGA_chip_part[2];
#endif
#if __FOENIX_A2560_REGISTER_SIZE__ == 32
  union {                       // line interrupt register (4 of them)
    struct {
      uint32_t enable0:1;
      uint32_t  :3;
      uint32_t compare0:12;
      uint32_t enable1:1;
      uint32_t  :3;
      uint32_t compare1:12;
    } line_interrupt_01;
    struct {
      uint32_t enable2:1;
      uint32_t  :3;
      uint32_t compare2:12;
      uint32_t enable3:1;
      uint32_t  :3;
      uint32_t compare3:12;
    } line_interrupt_23;
  };
#endif
};

enum cursor_font_size { Cursor_font_8x8, Cursor_font_8x16 };

enum cursor_flash_rate {
  Flash_1_sec,
  Flash_0_5_sec,
  Flash_0_25_sec,
  Flash_0_20_sec
};

// ----------------------------------------------------------------------
//
// Tile map
//
// ----------------------------------------------------------------------

typedef struct tilemap { // all tilemap registers are write ONLY
  union {
    struct {
      uint16_t layer_enable:1;
      uint16_t  :5;
      uint16_t collision_on:1;
    };
    uint16_t  reg;
  } control;
  vram_ptr data;
  uint16_t width;
  uint16_t height;
  struct {
    uint16_t scroll:4;
    uint16_t pos:10;
    uint16_t  :1;
    uint16_t neg:1;
  } x, y;
} tilemap_t;


// There are four tilemap register sets, use them as Tilemap[n].field
// where n is 0-3.
#define Tilemap ((tilemap_t __far *)(VICKY_BASE + 0x0200))

// Bits for control register
#define TILE_Enable       0x01
#define TILE_Collision_On 0x40 /* Enable */

// ----------------------------------------------------------------------
//
// Tile sets
//
// ----------------------------------------------------------------------

typedef struct tileset {
  uint32_t addy:22;
  uint32_t  :5;
  uint32_t stride_256:1;
} tileset_t;

// Adjust video RAM address for Vicky.
inline vram_ptr vicky_address (vram_ptr p) {
  return (vram_ptr) ((long)p - VRAM_BASE);
}

// Adjust video RAM address for Vicky buffer A (32 bit systems)
inline vram_ptr vicky_address_a (vram_ptr p) {
  return (vram_ptr) ((long)p - VRAM_BASE_A);
}

// Adjust video RAM address for Vicky buffer A (32 bit systems)
#ifdef VRAM_BASE_B
inline vram_ptr vicky_address_b (vram_ptr p) {
  return (vram_ptr) ((long)p - VRAM_BASE_B);
}
#endif // VRAM_BASE_B

// There are eight tileset register sets, use them as Tileset[n].field
// where n is 0-7.
#define Tileset ((tileset_t volatile __far *)(VICKY_BASE + 0x0280))

// ----------------------------------------------------------------------
//
// Bitmap plane
//
// ----------------------------------------------------------------------

typedef struct bitplane {
  union {
    struct {
      uint32_t enable:1;
      uint32_t lut:3;
      uint32_t  :2;
      uint32_t collision:1;
      uint32_t  :1;
      uint32_t  :24;
    };
    uint32_t reg;
  } control;
  vram_ptr start;
} bitplane_t;

// There are two bitmap planes, use them as Bitplane[n].field
// where n is 0-1.
#define Bitplane ((bitplane_t __far *)(VICKY_BASE + 0x0100)

// ----------------------------------------------------------------------
//
// Sprites
//
// ----------------------------------------------------------------------

typedef struct sprite { // all sprite registers are write ONLY
  union {
    struct {
      uint16_t enable : 1;
      uint16_t lut : 3;
      uint16_t depth : 3;
      uint16_t collision_enable : 1;
    };
    uint16_t reg;
  } control;
  vram_ptr data;
  uint16_t x;
  uint16_t y;
} sprite_t;

// There are 64 sprite register sets, use them as Sprite[n].field
// where n is 0-63.
#define Sprite ((sprite_t __far *)(VICKY_BASE + 0x1000))

#endif // __VICKY_H__
