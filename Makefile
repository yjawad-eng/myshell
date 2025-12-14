CC=gcc
CFLAGS= -Wall -Wextra -g
INC=-Iinclude
OBJ = \
	 src/main.o\
	 src/parse.o\
	 src/execute.o\
	 src/builtin.o\
	 src/signals.o\
	 src/logger.o
myshell: $(OBJ)
	$(CC) $(CFLAGS) -o myshell $(OBJ)
src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
clean:
	rm -f src/*.o myshell

