#include <mcp/syscalls.h>

void _Stub_exit(int h) {
    sys_exit(h);    
}