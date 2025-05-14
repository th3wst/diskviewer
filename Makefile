
CC = gcc
CFLAGS = -Wall -Wextra -lncurses

OBJS = main.o viewer.o diskio.o jump.o mbr.o gpt.o search.o editor.o

all: diskviewer

diskviewer: $(OBJS)
	$(CC) -o diskviewer $(OBJS) $(CFLAGS)

clean:
	rm -f *.o diskviewer
