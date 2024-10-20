#include <mcp/syscalls.h>
#include <stddef.h>
#include <calypsi/stubs.h>
#include "constants.h"

int _Stub_close(int h) {
  sys_fsys_close(h - FILE_TABLE_OFFSET);
  return 0;
}
