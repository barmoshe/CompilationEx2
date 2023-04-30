# CompilationEx2

#Bar Moshe and Amir Peleg
#206921777_205818032
Compi_ex2

This directory contains two implementations of a compiler for a movie database language:

bottonUp: a compiler built using a bottom-up parsing technique.
recursiveDescent: a compiler built using a recursive descent parsing technique.
BottonUp
The bottonUp directory contains the following files:

lex.yy.c: the output of flex, the scanner generator.
movies.lex: the input file for flex containing the regular expressions for the scanner.
movies.y: the input file for yacc, the parser generator.
movies.txt: an example input file for the movie database language.
movies.tab.c, movies.tab.h, movies.tab.o: the output files of yacc, which together make up the parser.
makefile: a makefile for building the compiler.
To build and run the compiler, navigate to the bottonUp directory and run the command make. This will generate an executable file called movies. To compile a movie database file, run the command ./movies < input_file, where input_file is the name of the file containing the movie database. The compiler will output any syntax errors it finds, and will print the number of movies and the number of movies per publisher (DC and Marvel) at the end.

RecursiveDescent
The recursiveDescent directory contains the following files:

lex.yy.c: the output of flex, the scanner generator.
movies.c, movies.h: the implementation of the parser using recursive descent.
movies.lex: the input file for flex containing the regular expressions for the scanner.
movies.txt: an example input file for the movie database language.
prog: an executable file built from movies.c, movies.h, and movies.lex.
makefile: a makefile for building the compiler.
To build and run the compiler, navigate to the recursiveDescent directory and run the command make. This will generate an executable file called prog. To compile a movie database file, run the command ./prog < input_file, where input_file is the name of the file containing the movie database. The compiler will output any syntax errors it finds, and will print the number of movies and the number of movies per publisher (DC and Marvel) at the end.



