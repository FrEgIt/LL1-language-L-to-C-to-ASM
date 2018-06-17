#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "analyseur_abstrait.h"
#include "symboles.h"

char yytext[100];
FILE *yyin;
int RETOURNERfin;

int main(int argc, char **argv) { 
	RETOURNERfin = 0;
	yyin = fopen(argv[2], "r");
	if( 0 == strcmp(argv[1],"-l"))
	{
		if(yyin == NULL)
			{
				fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
				return -1;
			}
		test_yylex_internal(yyin);
	}
	else if( 0 == strcmp(argv[1],"-s") )
	{
		if(yyin == NULL)
			{
				fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
				return -1;
			}
		test_yysynt_internal();
	}
	else if( 0 == strcmp(argv[1],"-a") )
	{
		if(yyin == NULL)
			{
				fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
				return -1;
			}
		test_yyasynt_internal();
	}
	else if( 0 == strcmp(argv[1],"-t") )
	{
		if(yyin == NULL)
			{
				fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
				return -1;
			}
		test_yytab_internal();
	}
	else if( 0 == strcmp(argv[1],"-m") )
	{
		if(yyin == NULL)
			{
				fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
				return -1;
			}
		test_yymips_internal();
	}

  return RETOURNERfin;
}
