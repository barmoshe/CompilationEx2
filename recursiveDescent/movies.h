#ifndef MOVIES

// yylex returns 0 when EOF is encountered
enum token
{
   TITLE = 1,
   MEDIA,
   TV,
   ZILCH,
   MOVIES,
   PUBLISHER,
   SLASH,
   COLON,
   YEAR,
   NAME
};

char *token_name(enum token token);


struct counter
{
   int dc_count;
   int marvel_count;
};
// We don't really need a union here because only there is only one field.
union _lexVal
{
   char *str_val;
   int in_movie;
};

extern union _lexVal lexicalValue; // like yylval when we use bison

void errorMsg(const char *s);

#endif
