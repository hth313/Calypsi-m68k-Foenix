#include <mcp/syscalls.h>
#include "constants.h"

int _Stub_puts(const char *str) {
	sys_chan_write(CONSOLE, str, strlen(str));
	return 0;
}