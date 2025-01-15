#include <calypsi/stubs.h>
#include <mcp/syscalls.h>
#include "mcp_errors.h"

int _Stub_rename(const char *oldpath, const char *newpath) {
    int result = sys_fsys_rename(oldpath, newpath);
    return (result == 0) ? 0 : map_errno(result);
}
