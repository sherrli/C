# A makefile for FileReverse.c with macros

FLAGS      = -std=c99 -Wall
TURNIN     = FileReverse.c Makefile README
SOURCES    = FileReverse.c
OBJECTS    = FileReverse.o
EXEBIN     = FileReverse
ASSIGNMENT = lab3
CRUZID     = shcli

all: $(EXEBIN)

$(EXEBIN): $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean:
	rm -f $(EXEBIN) $(OBJECTS)
