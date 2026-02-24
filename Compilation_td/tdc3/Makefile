ASM = nasm
GCC = gcc
ASM_FLAGS = -f elf64
LDFLAGS = -nostartfiles -no-pie
EXEC = alloc
OBJ_FILES = alloc.o utils.o


all: $(EXEC)


$(EXEC): $(OBJ_FILES)
	$(GCC) -o $@ $^ $(LDFLAGS)


alloc.o: alloc.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<

utils.o: utils.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<


clean:
	rm -f $(OBJ_FILES) $(EXEC)
