#include <mcp/syscalls.h>
#include <calypsi/stubs.h>

#ifndef _CONFIG_HAVE_FILENAME
void _Stub_assert(const char *filename, int linenum) __noreturn_function {
    char buffer[255];
    sprintf(buffer, "ASSERTION ERROR: %s at line %d", filename, linenum);
    sys_chan_write(0, (unsigned char *)buffer, strlen(buffer));
    sys_exit(-1);
}
#else
void _Stub_assert() __noreturn_function {
    char *error = "ASSERTION ERROR";
    sys_chan_write(0, (unsigned char *)error, strlen(error));
    sys_exit(-1);
}
#endif
