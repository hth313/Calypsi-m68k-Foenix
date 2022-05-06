VPATH = src
AFLAGS = --core=68000 --target=Foenix
CFLAGS = --core=68000 -Iinclude

# Library products
ALL_LIBS = foenix-sc-sd.a foenix-sc-ld.a foenix-lc-sd.a foenix-lc-ld.a

# Common source files
ASM_SRCS = startup-user.s startup-morfe.s syscall.s
C_SRCS = mcp_syscalls.c $(STUB_SRCS)
STUB_SRCS = stub_exit.c stub_open.c stub_puts.c stub_write.c stub_close.c stub_lseek.c stub_putchar.c stub_read.c

# Object files
OBJS_SC_SD = $(ASM_SRCS:%.s=%-sc-sd.o) $(C_SRCS:%.c=%-sc-sd.o)
OBJS_SC_LD = $(ASM_SRCS:%.s=%-sc-ld.o) $(C_SRCS:%.c=%-sc-ld.o)
OBJS_LC_SD = $(ASM_SRCS:%.s=%-lc-sd.o) $(C_SRCS:%.c=%-lc-sd.o)
OBJS_LC_LD = $(ASM_SRCS:%.s=%-lc-ld.o) $(C_SRCS:%.c=%-lc-ld.o)

# Add --rtattr to stub files
$(STUB_SRCS:%.c=%-sc-sd.o) : CFLAGS += --rtattr stubs=foenix --weak-symbols
$(STUB_SRCS:%.c=%-sc-ld.o) : CFLAGS += --rtattr stubs=foenix --weak-symbols
$(STUB_SRCS:%.c=%-lc-sd.o) : CFLAGS += --rtattr stubs=foenix --weak-symbols
$(STUB_SRCS:%.c=%-lc-ld.o) : CFLAGS += --rtattr stubs=foenix --weak-symbols

%-sc-sd.o: %.s
	as68k $(AFLAGS) --code-model=small --data-model=small --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-sc-sd.o: %.c
	cc68k $(CFLAGS) --code-model=small --data-model=small -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-sc-ld.o: %.s
	as68k $(AFLAGS) --code-model=small --data-model=large --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-sc-ld.o: %.c
	cc68k $(CFLAGS) --code-model=small --data-model=large -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-sd.o: %.s
	as68k $(AFLAGS) --code-model=large --data-model=small --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-sd.o: %.c
	cc68k $(CFLAGS) --code-model=large --data-model=small -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-ld.o: %.s
	as68k $(AFLAGS) --code-model=large --data-model=large --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-ld.o: %.c
	cc68k $(CFLAGS) --code-model=large --data-model=large -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

all: $(ALL_LIBS)

foenix-sc-sd.a: $(OBJS_SC_SD)
	(cd obj ; nlib ../$@ $^)

foenix-sc-ld.a: $(OBJS_SC_LD)
	(cd obj ; nlib ../$@ $^)

foenix-lc-sd.a: $(OBJS_LC_SD)
	(cd obj ; nlib ../$@ $^)

foenix-lc-ld.a: $(OBJS_LC_LD)
	(cd obj ; nlib ../$@ $^)

clean:
	-(cd obj ; rm $(OBJS_SC_SD) $(OBJS_SC_SD:%.o=%.lst))
	-(cd obj ; rm $(OBJS_SC_MD) $(OBJS_SC_LD:%.o=%.lst))
	-(cd obj ; rm $(OBJS_LC_SD) $(OBJS_LC_SD:%.o=%.lst))
	-(cd obj ; rm $(OBJS_LC_MD) $(OBJS_LC_LD:%.o=%.lst))
	-rm $(ALL_LIBS)
