#include <mcp/syscalls.h>
#include <calypsi/stubs.h>

void _Stub_exit(int exitCode) __noreturn_function {
  sys_exit(exitCode);
}
