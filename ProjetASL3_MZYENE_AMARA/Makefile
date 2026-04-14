CC = gcc
CFLAGS = -Wall -g -Isrc

PARSER = le_parser
LEXER = le_lexer

BIN = bin/tpcas

OBJ = obj/$(LEXER).o \
      obj/$(PARSER).o \
      obj/tree.o \
      obj/table.o

# ===================== BUILD =====================

$(BIN): $(OBJ)
	$(CC) -o $@ $^

# ===================== OBJ =====================

obj/tree.o: src/tree.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/table.o: src/table.c src/table.h src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(PARSER).o: obj/$(PARSER).c src/tree.h src/table.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).o: obj/$(LEXER).c obj/$(PARSER).h
	$(CC) -c -o $@ $< $(CFLAGS)

# ===================== GENERATION =====================

obj/$(LEXER).c: src/$(LEXER).lex obj/$(PARSER).h
	flex -o $@ $<

obj/$(PARSER).c obj/$(PARSER).h: src/$(PARSER).y
	bison -d -o obj/$(PARSER).c $<

# ===================== CLEAN =====================

clean:
	rm -f obj/* bin/tpcas

.PHONY: clean