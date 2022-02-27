#include <mcp/syscalls.h>
#include <stddef.h>
#include <stubs.h>
#include "constants.h"

int _Stub_close(int h) {
    if (h > STDERR_FILENO) {
        sys_fsys_close(h - FILE_TABLE_OFFSET);
    }
    return 0;
}
