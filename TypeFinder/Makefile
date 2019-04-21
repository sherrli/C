# Professor Tantalo assigned lab4 for Data Structures course.
# Optional: use gcc -g -c to enable gdb debugging

PROGRAM    = charType
FLAGS      = -std=c99 -Wall
SOURCES    = $(PROGRAM).c
OBJECTS    = $(PROGRAM).o
EXEBIN     = $(PROGRAM)

all: $(EXEBIN)

$(EXEBIN): $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	gcc -g -c $(FLAGS) $(SOURCES)

clean:
	rm $(EXEBIN) $(OBJECTS)
