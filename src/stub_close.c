#include <mcp/syscalls.h>
#include <stddef.h>
#include "constants.h"

void _Stub_close(int h) {
    if (h > STDERR_FILENO) {
        sys_fsys_close(h - FILE_TABLE_OFFSET);
    }
}