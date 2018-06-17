#ifndef __LEX__
#define __LEX__

#include "stdio.h"
#include "symboles.h"
#define YYTEXT_MAX 100
extern char yytext[YYTEXT_MAX];


int yylex(void);
void nom_token( int token, char *nom, char *valeur );
void test_yylex_internal( FILE *yyin );
int lgc(char *A);
int mangeEspaces();

#endif
