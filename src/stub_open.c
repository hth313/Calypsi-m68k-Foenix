#include <mcp/syscalls.h>
#include <stddef.h>
#include "constants.h"

#define	FA_READ             0x01
#define	FA_WRITE            0x02
#define	FA_OPEN_EXISTING    0x00
#define	FA_CREATE_NEW       0x04
#define	FA_CREATE_ALWAYS    0x08
#define	FA_OPEN_ALWAYS      0x10
#define	FA_OPEN_APPEND      0x30
#define MODE_MAP_CNT        8

typedef struct {
    char posix[4];
    int fsys;
} mode_map_t;

// Mapping copied from http://elm-chan.org/fsw/ff/doc/open.html
static mode_map_t mapping[MODE_MAP_CNT] = {
    {"r",   FA_READ},
    {"r+",  FA_READ | FA_WRITE},
    {"w",   FA_CREATE_ALWAYS | FA_WRITE},
    {"w+",  FA_CREATE_ALWAYS | FA_WRITE | FA_READ},
    {"a",   FA_OPEN_APPEND | FA_WRITE},
    {"a+",  FA_OPEN_APPEND | FA_WRITE | FA_READ},
    {"wx",  FA_CREATE_NEW | FA_WRITE},
    {"w+x", FA_CREATE_NEW | FA_WRITE | FA_READ}
};

// TODO: int _Stub_open(const char *path, int oflag, ...);
int __open(const char *name,const char *mode) {
    int result = -1;
    int m = -1;

    for (int i=0; i<MODE_MAP_CNT; i++) {
        char *map = mapping[i].posix;
        if (strcmp(mode, map) == 0) {
            m = mapping[i].fsys;
            break;
        }
    }

    if (m >= 0) {
        result = sys_fsys_open(name, m);
    }

    return (result >= 0) ? result + FILE_TABLE_OFFSET : result;
}