#include <stdio.h>
#include <string.h>
#include <mcp/syscalls.h>
#include <calypsi/stubs.h>

void _Stub_assert(const char *filename, int linenum) __noreturn_function {
  char buffer[255];
  sprintf(buffer, "ASSERTION ERROR: %s at line %d", filename, linenum);
  sys_chan_write(0, (unsigned char *)buffer, strlen(buffer));
  sys_exit(-1);
}
