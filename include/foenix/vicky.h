#ifndef __VICKY_H__
#define __VICKY_H__

#include <stdint.h>
#include "foenix/types.h"

#if __FOENIX_A2560_REGISTER_SIZE__ == 16
#define VICKY_BASE  0x00b40000
#define VRAM_BASE   0x00c00000
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
    uint32_t master_control;
#define TEXT_MODE_ENABLE           0x00000001
#define TEXT_MODE_OVERLAY_ENABLE   0x00000002
#define GRAPHIC_MODE_ENABLE        0x00000004
#define BITMAP_ENGINE_ENABLE       0x00000008
#define TILE_ENGINE_ENABLE         0x00000010
#define SPRITE_ENGINE_ENABLE       0x00000020
#define DISABLE_VIDEO_DISPLAY      0x00000080
#define VIDEO_MODE0                0x00000100
#define VIDEO_MODE1                0x00000200
#define DOUBLE_PIXEL_MODE          0x00000400
#define GAMMA_DIPSWITCH_VALUE      0x00002000
#define HIRES_DIPSWITCH_VALUE      0x00004000
#define ACTIVE_CLOCK               0x00008000
#define GAMMA_CHOICE_INPUT         0x00010000
#define GAMMA_ENABLE               0x00020000
#define DISPLAY_SLEEP              0x00040000
  };
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
    uint32_t color;
  } border;
  uint32_t background_color;     // background color register
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
    uint32_t cursor_position;
  };
#if __FOENIX_A2560_REGISTER_SIZE__ == 16
  union {                       // line interrupt register (4 of them)
    union {
      struct {
        uint16_t enable:1;
        uint16_t  :3;
        uint16_t compare:12;
      };
      uint16_t comtrol;
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
    uint16_t  control;
  };
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
#define Tilemap ((tilemap_t volatile __far *)(VICKY_BASE + 0x0200))

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
    uint32_t control;
  };
  vram_ptr start;
} bitplane_t;

// There are two bitmap planes, use them as Bitplane[n].field
// where n is 0-1.
#define Bitplane ((bitplane_t volatile __far *)(VICKY_BASE + 0x0100)

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
      uint16_t addy_low : 8;
    };
    uint16_t control;
#define SPRITE_ENABLE               0x01
#define SPRITE_LUT(lut)             ((lut) << 1)
#define SPRITE_DEPTH(depth)         ((depth) << 4)
#define SPRITE_COLLISION_ENABLE     0x80
#define SPRITE_ADDY_LOW(addy)       ((((long)addy) & 0xff) << 8)
  };

  uint16_t addy_high;
#define SPRITE_ADDY_HIGH(addy)      (((long)addy) >> 8)

  uint16_t x;
  uint16_t y;
} sprite_t;

// There are 64 sprite register sets, use them as Sprite[n].field
// where n is 0-63.
#define Sprite ((sprite_t volatile __far *)(VICKY_BASE + 0x1000))

#define SPRITE_SIZE   1024

// ----------------------------------------------------------------------
//
// Color lookup table
//
// ----------------------------------------------------------------------

typedef struct lut {
  uint8_t data[256][4];
} lut_t;

#define LUT ((lut_t volatile __far *)(VICKY_BASE + 0x2000))

#endif // __VICKY_H__
