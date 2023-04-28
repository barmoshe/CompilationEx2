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
   int dc_count_no_movie;
   int marvel_count_no_movie;
};
// We don't really need a union here because only there is only one field.
union _lexVal
{
   int is_DC;
};

extern union _lexVal lexicalValue; // like yylval when we use bison

void errorMsg(const char *s);

#endif
