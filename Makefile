CFLAGS = -ggdb -std=c11 -pedantic -Wall -Wextra -Werror -Wwrite-strings
CC = gcc

my_ls: main.o my_ls.o
	$(CC) $(CFLAGS) main.o my_ls.o -o my_ls
main.o: main.c my_ls.h
	$(CC) -c $(CFLAGS) main.c
my_ls.o: my_ls.c my_ls.h
	$(CC) -c $(CFLAGS) my_ls.c

clean:
	rm  main.o my_ls.o my_ls -f
