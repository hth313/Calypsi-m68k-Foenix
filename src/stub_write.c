#include <mcp/syscalls.h>
#include <stddef.h>
#include "constants.h"

size_t _Stub_write(int h, const char *p, size_t l) {
    if (h == STDOUT_FILENO || h == STDERR_FILENO) {
        return sys_chan_write(CONSOLE, p, l);
    } else if (h == STDIN_FILENO) {
        return -1;
    } else {
        return sys_chan_write(h - FILE_TABLE_OFFSET, p, l);
    }
}