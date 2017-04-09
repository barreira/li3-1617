CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0`
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
LIBS = `pkg-config --libs libxml-2.0`

program: interface
	$(CC) $(CFLAGS) program.c -o program $(LIBS) interface.o

avl:
	$(CC) $(CFLAGS) -c avl.c $(LIBS)

interface: avl contributors articles
	$(CC) $(CFLAGS) -c interface.c $(LIBS) avl.o contributors.o articles.o

articles: avl
	$(CC) $(CFLAGS) -c articles.c $(LIBS) avl.o

contributors: avl
	$(CC) $(CFLAGS) -c contributors.c $(LIBS) avl.o

clean:
	rm -f *.o program