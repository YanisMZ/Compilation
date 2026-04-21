CC = gcc
CFLAGS = -Wall -g -Isrc

PARSER = le_parser
LEXER = le_lexer

BIN = bin/tpcc

OBJ = obj/$(LEXER).o \
      obj/$(PARSER).o \
      obj/tree.o \
      obj/table.o \
      obj/semantic.o



$(BIN): $(OBJ)
	$(CC) -o $@ $^



obj/tree.o: src/tree.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/table.o: src/table.c src/table.h src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/semantic.o: src/semantic.c src/semantic.h src/table.h src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(PARSER).o: obj/$(PARSER).c src/tree.h src/table.h src/semantic.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).o: obj/$(LEXER).c obj/$(PARSER).h
	$(CC) -c -o $@ $< $(CFLAGS)



obj/$(LEXER).c: src/$(LEXER).lex obj/$(PARSER).h
	flex -o $@ $<

obj/$(PARSER).c obj/$(PARSER).h: src/$(PARSER).y
	bison -d -o obj/$(PARSER).c $<


clean:
	rm -f obj/* bin/tpcc

.PHONY: clean