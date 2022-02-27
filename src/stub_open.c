#include <mcp/syscalls.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <stubs.h>
#include "constants.h"

#define	FA_READ             0x01
#define	FA_WRITE            0x02
#define	FA_OPEN_EXISTING    0x00
#define	FA_CREATE_NEW       0x04
#define	FA_CREATE_ALWAYS    0x08
#define	FA_OPEN_ALWAYS      0x10
#define	FA_OPEN_APPEND      0x30

static int oflag_to_fatfs(int oflag) {
    int result = 0;
    if (oflag & O_RDONLY) result |= FA_READ;
    if (oflag & O_WRONLY) result |= FA_WRITE;
    if (oflag & O_APPEND) result |= FA_OPEN_APPEND;    
    if (oflag & O_CREAT & O_TRUNC) {
        result |= FA_CREATE_ALWAYS;
    } else if (oflag & O_CREAT) {
        result |= FA_CREATE_NEW;
    }
    return result;
}

int _Stub_open(const char *path, int oflag, ...) {
    int m = oflag_to_fatfs(oflag);
    int result = sys_fsys_open(path, m);
    return (result >= 0) ? result + FILE_TABLE_OFFSET : result;
}