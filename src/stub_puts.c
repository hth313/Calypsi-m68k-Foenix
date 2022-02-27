#include <string.h>
#include <stubs.h>
#include <mcp/syscalls.h>
#include "constants.h"

int _Stub_puts(const char *str) {
  sys_chan_write(CONSOLE, (unsigned char*)str, strlen(str));
  return 0;
}
