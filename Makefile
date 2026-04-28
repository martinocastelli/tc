CC = gcc
CFLAGS = -Wall -c -g
LFLAGS = -Wall
SOURCES = tc_tester.c tc.c
OBJECT = tc_tester.o tc.o
TAGS = tags
EXE = terminal_control_test.out

$(EXE): $(OBJECT)
	$(CC) -o $@ $(LFLAGS) $^

tc_tester.o: tc_tester.c tc.h
	$(CC) -o $@ $(CFLAGS) main.c

tc.o: tc.h tc.c
	$(CC) -o $@ $(CFLAGS) tc.c

clean:
	rm -f $(OBJECT) $(TAGS) $(EXE)

all: clean $(OBJECT) $(EXE)

clean_build: all

build_clean: $(OBJECT) $(EXE)
	rm -f $(OBJECT) $(TAGS)
