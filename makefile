CC = gcc

OBJECTS = lex.yy.o movies.tab.o

# 'movies' is the name of the executable file.
# Use 'movies.exe'  on Windows
movies: $(OBJECTS)
	$(CC) $(OBJECTS)  -o movies
	./movies movies.txt


lex.yy.c: movies.lex
	flex movies.lex
	
movies.tab.c movies.tab.h: movies.y
	bison -d movies.y
	
lex.yy.o: lex.yy.c movies.tab.h

movies.tab.o: movies.tab.c
	$(CC) -c movies.tab.c

clean:
	rm -f movies movies.tab.c movies.tab.h lex.yy.c $(OBJECTS)
	
	