ASM = nasm
GCC = gcc
ASM_FLAGS = -f elf64
LDFLAGS = -nostartfiles -no-pie
EXEC = exo4
OBJ_FILES = exo4.o utils.o


all: $(EXEC)


$(EXEC): $(OBJ_FILES)
	$(GCC) -o $@ $^ $(LDFLAGS)


exo4.o: exo4.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<

utils.o: utils.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<


clean:
	rm -f $(OBJ_FILES) $(EXEC)
