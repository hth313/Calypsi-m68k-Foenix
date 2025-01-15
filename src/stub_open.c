#include <mcp/syscalls.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <calypsi/stubs.h>
#include <errno.h>
#include "mcp_errors.h"
#include "constants.h"

#define FA_READ             0x01
#define FA_WRITE            0x02
#define FA_OPEN_EXISTING    0x00
#define FA_CREATE_NEW       0x04
#define FA_CREATE_ALWAYS    0x08
#define FA_OPEN_ALWAYS      0x10
#define FA_OPEN_APPEND      0x30

/*
File mode mappings.
https://man7.org/linux/man-pages/man3/fopen.3.html
http://elm-chan.org/fsw/ff/doc/open.html

│ fopen()     │ open() flags                  │ FatFS
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     r       │ O_RDONLY                      │ FA_READ                               │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     w       │ O_WRONLY | O_CREAT | O_TRUNC  │ FA_CREATE_ALWAYS | FA_WRITE           │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     a       │ O_WRONLY | O_CREAT | O_APPEND │ FA_OPEN_APPEND | FA_WRITE             │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     r+      │ O_RDWR                        │ FA_READ | FA_WRITE                    │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     w+      │ O_RDWR | O_CREAT | O_TRUNC    │ FA_CREATE_ALWAYS | FA_WRITE | FA_READ │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     a+      │ O_RDWR | O_CREAT | O_APPEND   | FA_OPEN_APPEND | FA_WRITE | FA_READ   │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
*/
static int _map_oflags(int oflag) {
    int result = 0;

    switch (oflag) {
        // r
        case O_RDONLY:
            result = FA_READ;
            break;
        // w
        case (O_WRONLY | O_CREAT | O_TRUNC):
            result = FA_CREATE_ALWAYS | FA_WRITE;
            break;
        // a
        case (O_WRONLY | O_CREAT | O_APPEND ):
            result = FA_OPEN_APPEND | FA_WRITE;
            break;
        // r+
        case (O_RDWR ):
            result = FA_READ | FA_WRITE;
            break;
        // w+
        case (O_RDWR | O_CREAT | O_TRUNC):
            result = FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
            break;
        // a+
        case (O_RDWR | O_CREAT | O_APPEND):
            result = FA_OPEN_APPEND | FA_WRITE | FA_READ;
            break;
        default:
            __set_errno(EINVAL);
            result = -1;
            break;
    }

    return result;
}

int _Stub_open(const char *path, int oflag, ...) {
    int mode = _map_oflags(oflag);
    if (mode < 0) {
        return -1;
    }

    int result = sys_fsys_open(path, mode);
    if (result < 0) {
        return map_errno(result);
    } else {
        return result + FILE_TABLE_OFFSET;
    }
}
