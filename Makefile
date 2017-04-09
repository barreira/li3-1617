CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0`
LIBS = `pkg-config --libs libxml-2.0`
OUT = program
OBJS = program.o interface.o avl.o articles.o contributors.o

program: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(OUT) $(LIBS)	

program.o: program.c interface.h
	cc -c program.c

avl.o: avl.c avl.h
	cc -c avl.c

interface: interface.c interface.h contributors.h articles.h
	cc -c interface.c

articles: articles.c articles.h avl.h
	cc -c articles.c

contributors: contributors.c contributors.h avl.h
	cc -c contributors.c

clean:
	rm -f *.o program