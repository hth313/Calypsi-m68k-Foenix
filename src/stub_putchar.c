#include <mcp/syscalls.h>
#include <stubs.h>
#include "constants.h"

int _Stub_putchar(int ch) {
  sys_chan_write_b(CONSOLE, ch);
  return 0;
}
