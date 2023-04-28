%{


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
"DC" {yylval.str_val = strdup(yytext); return PUBLISHER;}
"Marvel" {yylval.str_val = strdup(yytext);return PUBLISHER;}
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

   return token <= MEDIA ? names[token] : "unknown token";
}