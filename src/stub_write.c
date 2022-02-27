#include <mcp/syscalls.h>
#include <stddef.h>
#include <stubs.h>
#include "constants.h"

size_t _Stub_write(int h, const void *p, size_t l) {
    if (h == STDOUT_FILENO || h == STDERR_FILENO) {
        return sys_chan_write(CONSOLE, (unsigned char*)p, l);
    } else if (h == STDIN_FILENO) {
        return -1;
    } else {
        return sys_chan_write(h - FILE_TABLE_OFFSET, (unsigned char*)p, l);
    }
}
