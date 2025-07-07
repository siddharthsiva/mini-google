CC = gcc
CFLAGS = -Wall -pthread

SRCS = main.c server.c search.c file_saver.c template.c security.c
OBJS = $(SRCS:.c=.o)

mini-google: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o mini-google
	rm -rf cache logs
