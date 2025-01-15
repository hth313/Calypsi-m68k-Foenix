#include <calypsi/stubs.h>
#include <mcp/syscalls.h>

char** _Stub_environ(void) {
    // MCP does not provide a way to enumerate the ENV variables
    // sys_var_set and sys_var_set require knowledge of the keys
    return NULL;
}