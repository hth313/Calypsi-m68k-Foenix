#include <calypsi/stubs.h>
#include <mcp/syscalls.h>
#include "mcp_errors.h"

int _Stub_remove(const char *path) {
    int result = sys_fsys_delete(path);
    return (result == 0) ? 0 : map_errno(result);
}
