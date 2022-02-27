#include <mcp/syscalls.h>
#include <stddef.h>
#include <stubs.h>
#include "constants.h"

long _Stub_lseek(int h, long offset, int origin) {
  if (h > STDERR_FILENO) {
    return sys_chan_seek(h - FILE_TABLE_OFFSET, offset, origin - 1);
  } else {
    return -1;
  }
}
