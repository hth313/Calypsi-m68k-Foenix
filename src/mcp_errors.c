#include <errno.h>
#include "mcp_errors.h"

int map_errno(int result) {
    switch (result) {
        case FSYS_ERR_DISK_ERR:
        case FSYS_ERR_INT_ERR:
        case FSYS_ERR_NOT_READY:
        case FSYS_ERR_NOT_ENABLED:
        case FSYS_ERR_NO_FILESYSTEM:
            return -ENODEV;
        case FSYS_ERR_NO_FILE:
        case FSYS_ERR_NO_PATH:
            return -ENOENT;
        case FSYS_ERR_INVALID_NAME:
        case FSYS_ERR_INVALID_OBJECT:
        case FSYS_ERR_INVALID_DRIVE:
        case FSYS_ERR_INVALID_PARAMETER:
            return -EINVAL;
        case FSYS_ERR_DENIED:
        case FSYS_ERR_WRITE_PROTECTED:
            return -EACCES;
        case FSYS_ERR_EXIST:
            return -EEXIST;
            break;
        case FSYS_ERR_TOO_MANY_OPEN_FILES:
            return -ENFILE;
        case FSYS_ERR_LOCKED:
            return -ETXTBSY;
        case FSYS_ERR_MKFS_ABORTED:
        case FSYS_ERR_TIMEOUT:
        case FSYS_ERR_NOT_ENOUGH_CORE:
            return -EFAULT;
        default:
            return -EIO;
    }
}