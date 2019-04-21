# Makefile for Dictionary ADT with a verbose valgrind memory leak check.

ADT     = Dictionary
EXEBIN  = $(ADT)Client
SOURCES = $(ADT).c $(EXEBIN).c
OBJECTS = $(ADT).o $(EXEBIN).o
HEADERS = $(ADT).h
FLAGS   = -std=c99 -Wall -g

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full -v $(EXEBIN)
