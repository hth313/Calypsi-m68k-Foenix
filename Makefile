VPATH = src
AFLAGS = --core=68000 --target=Foenix --code-model=large --data-model=small
CFLAGS = --core=68000 -Iinclude --code-model=large --data-model=small

# Library products
ALL_LIBS = foenix-lc-sd.a

# Common source files
ASM_SRCS = startup-user.s startup-morfe.s syscall.s
C_SRCS = mcp_syscalls.c $(STUB_SRCS)
STUB_SRCS = stub_exit.c stub_open.c stub_puts.c stub_write.c stub_close.c stub_lseek.c stub_putchar.c stub_read.c

# Object files
OBJS = $(ASM_SRCS:%.s=%.o) $(C_SRCS:%.c=%.o)

# Add --rtattr to stub files
$(STUB_SRCS:%.c=%.o) : CFLAGS += --rtattr stubs=foenix
$(STUB_SRCS:%.c=%.o) : CFLAGS += --rtattr stubs=foenix

%.o: %.s
	as68k $(AFLAGS) --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%.o: %.c
	cc68k $(CFLAGS) -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

all: $(ALL_LIBS)

foenix-lc-sd.a: $(OBJS)
	(cd obj ; nlib ../$@ $^)

clean:
	-(cd obj ; rm $(OBJS) $(OBJS:%.o=%.lst))
	-rm $(ALL_LIBS)
