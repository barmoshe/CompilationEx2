%{
#include <stdio.h>
#include <string.h>
int dc_counter = 0;
int marvel_counter = 0;
int dc_counter_movies = 0;
int marvel_counter_movies = 0;

extern int yylex (void);
void yyerror (const char *s);


%}

%union {
  char *str_val;
  int in_movie;
}

%token TITLE
%token NAME
%token PUBLISHER
%token YEAR
%token TV
%token MOVIES
%token ZILCH
%token COLON
%token MEDIA
%token SLASH

%type<str_val> PUBLISHER
%type<in_movie> media_info
%type<in_movie> media_spec


%%

input: TITLE hero_list TITLE {
  printf("DC: %d\n", dc_counter);
  printf("Marvel: %d\n", marvel_counter);
  printf("DC Movies: %d\n", dc_counter_movies);
  printf("Marvel Movies: %d\n", marvel_counter_movies);
  if (marvel_counter - marvel_counter_movies > dc_counter - dc_counter_movies) {
    printf("More Marvel super heroes did not appear in movies\n");
  } else if (marvel_counter - marvel_counter_movies < dc_counter - dc_counter_movies) {
    printf("More DC super heroes did not appear in movies\n");
  }
}

hero_list: hero_list super_hero {}
         | /* epsilon */ {
            dc_counter_movies = 0;
            marvel_counter_movies = 0;
            marvel_counter = 0;
            dc_counter = 0;

            }
         

super_hero: NAME PUBLISHER YEAR media_info {
            char *pub = $2;
            if (strcmp(pub, "DC") == 0) {
              dc_counter += 1;
              dc_counter_movies += $4;
            } else if (strcmp(pub, "Marvel") == 0) {
              marvel_counter += 1;
              marvel_counter_movies += $4;
            }
}
           

media_info: MEDIA COLON media_spec {
            $$ = $3;
}
          | /*epsilon */ {
            $$ = 0;
          }
          

media_spec: /*epsilon */ {$$ = 0;}
          | TV {$$ = 0;}
          | MOVIES {$$ = 1;}
          | MOVIES SLASH TV {$$ = 1;}
          | TV SLASH MOVIES {$$ = 1;}
          | ZILCH {$$ = 0;}
          

%%
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
  
  yyparse();
  
  fclose (yyin);
  return 0;
}

void yyerror (const char *s)
{
  extern int line;
  fprintf (stderr, "line %d: %s\n", line, s);
}
