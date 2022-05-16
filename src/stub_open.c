#include <mcp/syscalls.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <stubs.h>
#include <errno.h>
#include "constants.h"

#define FA_READ             0x01
#define FA_WRITE            0x02
#define FA_OPEN_EXISTING    0x00
#define FA_CREATE_NEW       0x04
#define FA_CREATE_ALWAYS    0x08
#define FA_OPEN_ALWAYS      0x10
#define FA_OPEN_APPEND      0x30

#define FSYS_ERR_DISK_ERR               -18 /* (1) A hard error occurred in the low level disk I/O layer */
#define FSYS_ERR_INT_ERR                -19 /* (2) Assertion failed */
#define FSYS_ERR_NOT_READY              -20 /* (3) The physical drive cannot work */
#define FSYS_ERR_NO_FILE                -21 /* (4) Could not find the file */
#define FSYS_ERR_NO_PATH                -22 /* (5) Could not find the path */
#define FSYS_ERR_INVALID_NAME           -23 /* (6) The path name format is invalid */
#define FSYS_ERR_DENIED                 -24 /* (7) Access denied due to prohibited access or directory full */
#define FSYS_ERR_EXIST                  -25 /* (8) Access denied due to prohibited access */
#define FSYS_ERR_INVALID_OBJECT         -26 /* (9) The file/directory object is invalid */
#define FSYS_ERR_WRITE_PROTECTED        -27 /* (10) The physical drive is write protected */
#define FSYS_ERR_INVALID_DRIVE          -28 /* (11) The logical drive number is invalid */
#define FSYS_ERR_NOT_ENABLED            -29 /* (12) The volume has no work area */
#define FSYS_ERR_NO_FILESYSTEM          -30 /* (13) There is no valid FAT volume */
#define FSYS_ERR_MKFS_ABORTED           -31 /* (14) The f_mkfs() aborted due to any problem */
#define FSYS_ERR_TIMEOUT                -32 /* (15) Could not get a grant to access the volume within defined period */
#define FSYS_ERR_LOCKED                 -33 /* (16) The operation is rejected according to the file sharing policy */
#define FSYS_ERR_NOT_ENOUGH_CORE        -34 /* (17) LFN working buffer could not be allocated */
#define FSYS_ERR_TOO_MANY_OPEN_FILES    -35 /* (18) Number of open files > FF_FS_LOCK */
#define FSYS_ERR_INVALID_PARAMETER      -36 /* (19) Given parameter is invalid */

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

static void map_errno(int result) {
    switch (result) {
        case FSYS_ERR_DISK_ERR:
        case FSYS_ERR_INT_ERR:
        case FSYS_ERR_NOT_READY:
        case FSYS_ERR_NOT_ENABLED:
        case FSYS_ERR_NO_FILESYSTEM:
            __set_errno(ENODEV);
            break;
        case FSYS_ERR_NO_FILE:
        case FSYS_ERR_NO_PATH:
            __set_errno(ENOENT);
            break;
        case FSYS_ERR_INVALID_NAME:
        case FSYS_ERR_INVALID_OBJECT:
        case FSYS_ERR_INVALID_DRIVE:
        case FSYS_ERR_INVALID_PARAMETER:
            __set_errno(EINVAL);
            break;
        case FSYS_ERR_DENIED:
        case FSYS_ERR_WRITE_PROTECTED:
            __set_errno(EACCES);
            break;
        case FSYS_ERR_EXIST:
            __set_errno(EEXIST);
            break;
        case FSYS_ERR_TOO_MANY_OPEN_FILES:
            __set_errno(ENFILE);
            break;
        case FSYS_ERR_LOCKED:
            __set_errno(ETXTBSY);
            break;
        case FSYS_ERR_MKFS_ABORTED:
        case FSYS_ERR_TIMEOUT:
        case FSYS_ERR_NOT_ENOUGH_CORE:
            __set_errno(EFAULT);
            break;
        default:
            __set_errno(EIO);
            break;
    }
}

int _Stub_open(const char *path, int oflag, ...) {
    int mode = _map_oflags(oflag);
    if (mode < 0) {
        return -1;
    }

    int result = sys_fsys_open(path, mode);
    if (result < 0) {
        map_errno(result);
        return -1;
    } else {
        return result + FILE_TABLE_OFFSET;
    }
}
