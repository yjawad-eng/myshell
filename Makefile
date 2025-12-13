CC=gcc
CFLAGS= -Wall -Wextra -g
OBJ = src/main.o
myshell: $(OBJ)
	$(CC) $(CFLAGS) -o myshell $(OBJ)
clean:
	rm -f src/*.o myshell

