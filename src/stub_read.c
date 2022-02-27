#include <mcp/syscalls.h>
#include <stddef.h>
#include <stubs.h>
#include "constants.h"

size_t _Stub_read(int h, void *p, size_t l) {
    if (h == STDIN_FILENO) {
        return sys_chan_read(0, p, l);
    } else if (h > STDERR_FILENO) {
        return sys_chan_read(h - FILE_TABLE_OFFSET, p, l);
    } else {
        return -1;
    }
}
