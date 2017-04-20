CC = gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0`
LIBS = `pkg-config --libs libxml-2.0`
OUT = program
OBJS = program.o interface.o menu.o avl.o articles.o contributors.o

program: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(OUT) $(LIBS)	

program.o: program.c interface.h menu.h
	cc -c program.c

interface: interface.c interface.h avl.h contributors.h articles.h
	cc -c interface.c

menu: menu.c menu.h interface.h
	cc -c menu.c

avl: avl.c avl.h articles.h contributors.h
	cc -c avl.c

articles: articles.c articles.h avl.h
	cc -c articles.c

contributors: contributors.c contributors.h avl.h
	cc -c contributors.c

clean:
	rm -f *.o program