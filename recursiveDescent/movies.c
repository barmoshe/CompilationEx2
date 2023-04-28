// Purpose: Recursive descent parser for movies
#include <stdio.h>
#include <stdlib.h> /* for exit() */
#include <string.h>
#include "movies.h"

extern enum token yylex(void);
enum token lookahead;


// the recursive descent parser
void input();
struct counter hero_list();
struct counter super_hero();
int media_info();
int media_spec();
void match(int expectedToken);
void parse();

int main(int argc, char **argv)
{
    extern FILE *yyin;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 2;
    }

    parse();

    fclose(yyin);
    return 0;
}

void match(int wanted)
{
    if (lookahead == wanted)
        lookahead = yylex();
    else
    {
        char e[100];
        sprintf(e, "error: expected token %s, found token %s",
                token_name(wanted), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}
void parse()
{
    lookahead = yylex();
    input();
    if (lookahead != 0)
    { // 0 means EOF
        errorMsg("EOF expected");
        exit(1);
    }
}

void errorMsg(const char *s)
{
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

void input()
{ // grammer rule
    match(TITLE);
    struct counter publisher = hero_list();
    match(TITLE);
    printf("DC: %d\n", publisher.dc_count_no_movie);
    printf("Marvel: %d\n", publisher.marvel_count_no_movie);
    if (publisher.dc_count_no_movie > publisher.marvel_count_no_movie)
        printf("More DC super heroes did not appear in movies\n");
    else if (publisher.dc_count_no_movie < publisher.marvel_count_no_movie)
        printf("More Marvel super heroes did not appear in movies\n");
}

struct counter hero_list()
{ // grammer rule
    // init counter
    struct counter publisher_total = {0, 0};
    while (lookahead == NAME)
    {
        struct counter publisher2 = super_hero();
        publisher_total.dc_count_no_movie += publisher2.dc_count_no_movie;
        publisher_total.marvel_count_no_movie += publisher2.marvel_count_no_movie;
    }
    return publisher_total;
}

struct counter super_hero()
{ // grammer rule
    struct counter publisher = {0, 0};
    match(NAME);
    if (lookahead == PUBLISHER)
    {
        match(PUBLISHER);
        int is_DC= lexicalValue.is_DC;
        match(YEAR);
        int in_movie=media_info();
        if (is_DC && !in_movie)
            publisher.dc_count_no_movie++;
        else if (!is_DC && !in_movie)
            publisher.marvel_count_no_movie++;

        
    }
    else
    {
        errorMsg("error: publisher not found");
        exit(1);
    }
    return publisher;
}

int media_info()
{ // if not epsilon then grammer rule
    if (lookahead == MEDIA)
    {
        match(MEDIA);
        match(COLON);
        int result = media_spec();
        return result;
    }
    else
        return 0;
}

int media_spec()
{ // grammer rule
    int result = 0;

    if (lookahead == ZILCH)
    {
        match(ZILCH);
        result = 0;
    }
    // else check if MOVIES SLASH TV or TV SLASH MOVIES
    else if (lookahead == MOVIES)
    {
        match(MOVIES);
        if (lookahead == SLASH)
        {
            match(SLASH);
            match(TV);
        }
        result = 1;
    }
    else if (lookahead == TV)
    {
        match(TV);
        if (lookahead == SLASH)
        {
            match(SLASH);
            match(MOVIES);
            result = 1;
        }
    }
    else
    {
        errorMsg("error: media not found");
        return -1;
        exit(1);
        
    }
    return result;
}