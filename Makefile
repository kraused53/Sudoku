# Project name
TARGET = sudoku

# Compiler Error flags
#	-Wvla	-> Reports any instance of variable length array declaration
#	-Werror	-> Display warnings as errors
ERROR = -Wvla -Werror

# Compiler Warning flags
# 	-Wall		-> Compiler will list all warnings, no matter the severity
# 	-Wshadow	-> Warns whenever a local variable shadows another variable
# 	--pedantic	-> Forces compiler to follow strict ISO C guidelines
WARNING = -Wall -Wshadow --pedantic

# External Libraries
# 	-lncurses -> C ASCII Graphics library
LIBS = -lncurses

# C Compiler
#	gcc 		-> GNU C compiler
#	-std=c99	-> Compile using C99 standard
#	-g			-> Compile with debugging information (allows GDB use)
CC = gcc -std=c99 -g $(WARNING) $(ERROR)

# List of all C source files for this project
SRCS = main.c engine.c GUI.c

# Auto generate names for *.o files from 
# 	SRCS (list of all *.c viles)
OBJS = $(SRCS:%.c=%.o)

# Define how to compile main program
$(TARGET): $(OBJS)
	$(CC) $(CFlags) $(OBJS) $(LIBS) -o $(TARGET)

# Make rule for converting .c files to .o files
.c.o:
	$(CC) $(CFlags) -c $*.c 

# Run the sudoku program and load the first game board
board1: $(TARGET)
	./$(TARGET) ./inputs/board_1.txt

board2: $(TARGET)
	./$(TARGET) ./inputs/board_2.txt

# Remove all .o files the compiled program
clean:
	rm -f $(OBJS) $(TARGET)