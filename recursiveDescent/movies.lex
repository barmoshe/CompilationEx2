%{
#include "movies.h"
union _lexVal lexicalValue;
extern int atoi (const char *);
extern void exit(int);

int line = 1;
%}

%option noyywrap
/*%option yylineno*/

%%
"** super heroes **"  { return TITLE; }
"media" {return MEDIA;}
"TV" {return TV;}
"zilch" {return ZILCH;}
"MOVIES" { return MOVIES;}
"DC" {lexicalValue.is_DC = 1; return PUBLISHER;}
"Marvel" {lexicalValue.is_DC = 0;return PUBLISHER;}
\#(.*) {}
"/" {return SLASH;}
":" {return COLON;}
[0-9]+     { return YEAR; }
\[[A-Za-z]+(" "[A-Za-z]+)*\]   { return NAME; }
     
[\t\r ]+   /* skip white space */
\n         { line++; }
.          { fprintf (stderr, "line %d: unrecognized token %s\n",
                               line, yytext);  
             exit(1);
           }

%%

char *token_name(enum token token)
{
   static char *names[] = {
       "EOF",
       "TITLE",
       "MEDIA",
       "TV",
       "ZILCH",
       "MOVIES",
       "PUBLISHER",
       "SLASH",
       "COLON",
       "YEAR",
       "NAME"};

   return token <= NAME ? names[token] : "unknown token";
}