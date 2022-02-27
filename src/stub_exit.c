#include <mcp/syscalls.h>
#include <stubs.h>

void _Stub_exit(int exitCode) __noreturn_function {
  sys_exit(exitCode);
}
