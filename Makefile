VPATH = src
AS_FLAGS = --core=68000 --target=Foenix --code-model=large --data-model=small
C_FLAGS = -Iinclude

# Library products
ALL_LIBS = foenix-lc-sd.a

# Common source files
ASM_SRCS = startup-user.s startup-morfe.s syscall.s
C_SRCS = stub_exit.c stub_open.c stub_puts.c stub_write.c stub_close.c stub_lseek.c stub_putchar.c stub_read.c \
         mcp_syscalls.c

# Object files
OBJS = $(ASM_SRCS:%.s=%.o) $(C_SRCS:%.c=%.o)

%.o: %.s
	as68k $(AS_FLAGS) --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%.o: %.c
	cc68k $(AS_FLAGS) $(C_FLAGS) -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

all: $(ALL_LIBS)

foenix-lc-sd.a: $(OBJS)
	(cd obj ; nlib ../$@ $^)

clean:
	-(cd obj ; rm $(OBJS) $(OBJS:%.o=%.lst))
	-rm $(ALL_LIBS)
