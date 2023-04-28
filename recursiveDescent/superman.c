#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "superman.h"

extern enum token yylex (void);
enum token lookahead;

/* Function declarations */
void start();
struct counter superhero_list();
struct counter superhero();
int is_movie();
void match(int expectedToken);
void parse();

int main (int argc, char **argv)
{
	extern FILE *yyin;
	if (argc != 2) {
		fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
		return 1;
	}
	yyin = fopen (argv [1], "r");
	if (yyin == NULL) {
		fprintf (stderr, "failed to open %s\n", argv[1]);
		return 2;
	}
  
	parse();
  
	fclose (yyin);
	return 0;
}

void match(int expectedToken)
{
	if (lookahead == expectedToken)
		lookahead = yylex();
	else 
	{
		char e[100]; 
		sprintf(e, "error: expected token %s, found token %s", 
		token_name(expectedToken), token_name(lookahead));
		errorMsg(e);
		exit(1);
	}
}

void parse()
{
	lookahead = yylex();
	start();
	if (lookahead != 0) {  // 0 means EOF
		errorMsg("EOF expected");
		exit(1);
	}
}

void errorMsg(const char *s)
{
	extern int yylineno;
	fprintf (stderr, "line %d: %s\n", yylineno, s);
}

void start()
{
	match(TITLE);
	struct counter sl = superhero_list();
	if (sl.dc_count_no_movie > sl.marvel_count_no_movie) 
		printf ("More DC super heroes did not appear in movies\n");
	else if (sl.dc_count_no_movie < sl.marvel_count_no_movie)
		printf ("More Marvel super heroes did not appear in movies\n");
	match(TITLE);
}

struct counter superhero_list()
{
	struct counter total = { .dc_count_no_movie = 0, .marvel_count_no_movie = 0 };
	while(lookahead == NAME) 
	{
		struct counter s = superhero();
		total.dc_count_no_movie += s.dc_count_no_movie;
		total.marvel_count_no_movie += s.marvel_count_no_movie;
	}
	return total;
}

struct counter superhero() 
{
	match(NAME);
    
	int is_marvel = lexicalValue.is_marvel;
	match(PUBLISHER);
	match(YEAR);
	
	if(lookahead == MEDIA)
	{
		match(MEDIA);
		if(lookahead == TV)
		{
			match(TV);
    			if(lookahead == MOVIES)
    			{
    				match(MOVIES);
    				struct counter s = { .dc_count_no_movie = 0, .marvel_count_no_movie = 0 };
    				return s;
    			}
    			else
    			{
    				if(is_marvel)
    				{
    					struct counter s = { .dc_count_no_movie = 0, .marvel_count_no_movie = 1 };
    					return s;
    				}
    				else
    				{
    					struct counter s = { .dc_count_no_movie = 1, .marvel_count_no_movie = 0 };
    					return s;
    				}
    			}
    		}
    		else if(lookahead == MOVIES)
    		{
    			match(MOVIES);
    			if(lookahead == TV)
    				match(TV);
    			struct counter s = { .dc_count_no_movie = 0, .marvel_count_no_movie = 0 };
    			return s;
    		}
    		else
    		{
    			if(lookahead == ZILCH)
    				match(ZILCH);
    			if(is_marvel)
    			{
    				struct counter s = { .dc_count_no_movie = 0, .marvel_count_no_movie = 1 };
    				return s;
    			}
    			else
    			{
    				struct counter s = { .dc_count_no_movie = 1, .marvel_count_no_movie = 0 };
    				return s;
    			}
    		}
    }
    else
    {
    	if(is_marvel)
    	{
    		struct counter s = { .dc_count_no_movie = 0, .marvel_count_no_movie = 1 };
    		return s;
    	}
    	else
    	{
    		struct counter s = { .dc_count_no_movie = 1, .marvel_count_no_movie = 0 };
    		return s;
    	}
    }
}
