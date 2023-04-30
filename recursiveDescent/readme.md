Recursive Descent Parser Example for Movie Analysis

This is an example of a recursive descent parser built to replace an existing Bison parser for movie analysis. The goal of the parser is to analyze a list of superheroes and determine which publisher (DC or Marvel) has more superheroes that have not appeared in movies.

The project contains the following files:

movies.c: The implementation of the recursive descent parser.
movies.h: The header file for movies.c.
movies.lex: The lexical analyzer file, used to tokenize the input.
movies.txt: The input file containing the list of superheroes to analyze.
lex.yy.c: The output of the flex command used to generate the lexical analyzer.
prog: The compiled executable.
To build and run the project:

Compile the movies.c and lex.yy.c files together with the prog executable:
bash
Copy code
gcc -o prog movies.c lex.yy.c -lfl
Run the program, passing in the movies.txt file as input:
bash
Copy code
./prog movies.txt
The program will output which publisher has more superheroes that have not appeared in movies, either "More Marvel superheroes did not appear in movies" or "More DC superheroes did not appear in movies".

Note that this example assumes that the input is correctly formatted according to the provided grammar.