CC = gcc
CFLAGS = -Wall -c -g
LFLAGS = -Wall
SOURCES = main.c tc.c
OBJECT = main.o tc.o
TAGS = tags
EXE = terminal_control_test.out

$(EXE): $(OBJECT)
	$(CC) -o $@ $(LFLAGS) $^

main.o: main.c tc.h
	$(CC) -o $@ $(CFLAGS) main.c

tc.o: tc.h tc.c
	$(CC) -o $@ $(CFLAGS) tc.c

clean:
	rm -f $(OBJECT) $(TAGS) $(EXE)

all: clean $(OBJECT) $(EXE)

clean_build: all

build_clean: $(OBJECT) $(EXE)
	rm -f $(OBJECT) $(TAGS)
