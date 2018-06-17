#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "symboles.h"
#include "analyseur_lexical.h"
#include "util.h"
#define is_num(c)(('0' <= (c)) && ((c) <= '9'))
#define is_maj(c)(('A' <= (c)) && ((c) <= 'Z'))
#define is_min(c)(('a' <= (c)) && ((c) <= 'z'))
#define is_dollar(c)('$' == (c))
#define is_alpha_strict(c)(is_maj(c) || is_min(c) || (c)== '_')
#define is_alpha(c)(is_maj(c) || is_min(c) || (c) == '_' || (c) == '$')
#define is_alphanum(c)(is_num((c)) || is_alpha((c)))
#define is_not(c)(c <'0' || (c >'9' && c <'A') || (c >'Z' && c<'a') || c >'z' || c!='_' || c!='$') // NON FONCTIONNEL
#define is_separator(c)(c=='-' ||  c=='+' ||  c=='*' ||  c=='/' ||  c=='%' ||  c=='<' ||  c=='>' ||  c=='=' ||  c=='(' ||  c==')' ||  c=='{' ||  c=='}' ||  c=='&' ||  c=='|' ||  c==',' ||  c==';' || c=='!' ||  c=='#' ||  c=='\t' ||  c=='\n' || c== ' ' )
#define is_error(c)(c <'0' || (c >'9' && c <'A') || (c >'Z' && c<'a') || c >'z' || c!='_' || c!='$' ||  c!='-' ||  c!='+' ||  c!='*' ||  c!='/' ||  c!='%' ||  c!='<' ||  c!='>' ||  c!='=' ||  c!='(' ||  c!=')' ||  c!='{' ||  c!='}' ||  c!='&' ||  c!='|' ||  c!=',' ||  c!=';' || c!='!' ||  c!='#' ||  c!='\t' ||  c!='\n' || c!= ' ' )


char *tableMotsClefs[] = {
  "si", "alors", "sinon", "tantque", "faire", "entier",  "retour", "lire", "ecrire"
};

int codeMotClefs[] = {SI, ALORS , SINON, TANTQUE, FAIRE, ENTIER, RETOUR, LIRE, ECRIRE};
extern FILE *yyin;

int nbMotsClefs = 9;
int yyleng;


/* Compter les lignes pour afficher les messages d'erreur avec numero ligne */
int nb_ligne = 1;

/*******************************************************************************
 * Fonction qui ignore les espaces et commentaires. 
 * Renvoie -1 si arrivé à la fin du fichier, 0 si tout va bien 
 ******************************************************************************/
int mangeEspaces()
{ 
  char c = fgetc(yyin);
  int comment = 0;
  while( comment || (c == ' ') || (c == '\n') || (c == '\t') || (c == '#' ) ) {
    if( c == '#' ) {
        comment = 1;
    }
    if( c == '\n' ) {
      nb_ligne++;
      comment = 0;
    }
    c = fgetc(yyin); 
  }
  if ( feof(yyin) ) {
    return -1;
  }    
  ungetc(c, yyin);
  return 0;
}

/*******************************************************************************
 * Lit un caractère et le stocke dans le buffer yytext 
 ******************************************************************************/
char lire(void)
{
  yytext[yyleng++] = fgetc(yyin);
  yytext[yyleng] = '\0';
  return yytext[yyleng - 1];
}

/*******************************************************************************
 * Remet le dernier caractère lu au buffer clavier et enlève du buffer yytext 
 ******************************************************************************/
void delireCar()
{
  char c;
  c = yytext[yyleng - 1];
  yytext[--yyleng] = '\0';
  ungetc(c, yyin);
}
/*******************************************************************************
 * Fonction principale de l'analyseur lexical, lit les caractères de yyin et
 * renvoie les tokens sous forme d'entier. Le code de chaque unité est défini 
 * dans symboles.h sinon (mot clé, idententifiant, etc.). Pour les tokens de 
 * type ID_FCT, ID_VAR et NOMBRE la valeur du token est dans yytext, visible 
 * dans l'analyseur syntaxique.
 ******************************************************************************/
int yylex(void)
{
  char c = 1;
  int i;
  yytext[yyleng = 0] = '\0';
  // début
	if(mangeEspaces() == 0)
		{
			c = lire();
			//avancement du curseur
			// symbole
			if(';' == c)
				return POINT_VIRGULE;
				
			else if('+' == c)
				return PLUS;
					
			else if('[' == c)
				return CROCHET_OUVRANT;	
				
			else if(']' == c)
				return CROCHET_FERMANT;
				
			else if('-' == c)
				return MOINS;
			
			else if('*' == c)
				return FOIS;
				
			else if('%' == c)
				return MODULO;
			
			else if('/' == c)
				return DIVISE;
				
			else if('(' == c)
				return PARENTHESE_OUVRANTE;
			
			else if(')' == c)
				return PARENTHESE_FERMANTE;
				
			else if('[' == c)
				return CROCHET_OUVRANT;
				
			else if(']' == c)
				return CROCHET_FERMANT;
                        
            else if('{' == c)
				return ACCOLADE_OUVRANTE;
				
			else if('}' == c)
				return ACCOLADE_FERMANTE;
			
			else if('=' == c)
				return EGAL;
				
			else if('<' == c)
				return INFERIEUR;
				
			else if('>' == c)
				return SUPERIEUR;
				
			else if('&' == c)
				return ET;
					
			else if('|' == c)
				return OU;
				
			else if('!' == c)
				return NON;
					
			else if(',' == c)
				return VIRGULE;
				
		  else if(is_dollar(c))
				{
					while(is_alphanum(c)&& !is_separator(c) )
					{
						c=lire();
						if( c == '[')
						{
							delireCar();
							if(yyleng>1) return ID_VAR;
							else return ERREUR;
							
						}
					}
					delireCar();
					if(yyleng>1) return ID_VAR;
				}
			// cas fonction ou type ou class de condition/in/out
		  else if(is_alpha_strict(c))
				{
					while(is_alphanum(c)&& !is_separator(c))
					{
						c=lire();
					}
					delireCar();
					for(i=0; i < nbMotsClefs; i++)
					{
						if( 0== strcmp(yytext, tableMotsClefs[i]))
						{
							return codeMotClefs[i];
						}
					}
					return ID_FCT;
				}
			
			//cas nombre
		  else if(is_num(c))
				{
					while(is_num(c)&& !is_separator(c) )
						{
							c=lire();
						}
					delireCar();
					return NOMBRE;
				}
			
			}	
			else if(mangeEspaces() == -1)
				return FIN;
      return ERREUR;
}

/*******************************************************************************
 * Fonction auxiliaire appelée par l'analyseur syntaxique tout simplement pour 
 * afficher des messages d'erreur et l'arbre XML 
 ******************************************************************************/
void nom_token( int token, char *nom, char *valeur ) {
  int i;
  
  strcpy( nom, "symbole" );
  if(token == POINT_VIRGULE) strcpy( valeur, "POINT_VIRGULE");
  else if(token == PLUS) strcpy(valeur, "PLUS");
  else if(token == MODULO) strcpy(valeur, "MODULO");
  else if(token == MOINS) strcpy(valeur, "MOINS");
  else if(token == FOIS) strcpy(valeur, "FOIS");
  else if(token == DIVISE) strcpy(valeur, "DIVISE");
  else if(token == PARENTHESE_OUVRANTE) strcpy(valeur, "PARENTHESE_OUVRANTE");
  else if(token == PARENTHESE_FERMANTE) strcpy(valeur, "PARENTHESE_FERMANTE");
  else if(token == CROCHET_OUVRANT) strcpy(valeur, "CROCHET_OUVRANT");
  else if(token == CROCHET_FERMANT) strcpy(valeur, "CROCHET_FERMANT");
  else if(token == ACCOLADE_OUVRANTE) strcpy(valeur, "ACCOLADE_OUVRANTE");
  else if(token == ACCOLADE_FERMANTE) strcpy(valeur, "ACCOLADE_FERMANTE");
  else if(token == EGAL) strcpy(valeur, "EGAL");
  else if(token == INFERIEUR) strcpy(valeur, "INFERIEUR");
  else if(token == SUPERIEUR) strcpy(valeur, "SUPERIEUR");
  else if(token == ET) strcpy(valeur, "ET");
  else if(token == OU) strcpy(valeur, "OU");
  else if(token == NON) strcpy(valeur, "NON");
  else if(token == FIN) strcpy(valeur, "FIN");
  else if(token == VIRGULE) strcpy(valeur, "VIRGULE");

  else if( token == ID_VAR ) 
  {
    strcpy( nom, "id_variable" );  
    strcpy( valeur, yytext );        
  }
  else if( token == ID_FCT ) 
  {
    strcpy( nom, "id_fonction" );    
    strcpy( valeur, yytext );    
  }
  else if( token == NOMBRE ) 
  {
    strcpy( nom, "nombre" );
    strcpy( valeur, yytext ); 
  }
  else 
  {
    strcpy( nom, "mot_clef" );
    for(i=0; i < nbMotsClefs; i++)
    {
      if( token ==  codeMotClefs[i] )
      {
        strcpy( valeur, tableMotsClefs[i] );
        break;
      }
    }
  }  
}

/*******************************************************************************
 * Fonction auxiliaire appelée par le compilo en mode -l, pour tester l'analyseur
 * lexical et, étant donné un programme en entrée, afficher la liste des tokens.
 ******************************************************************************/
void test_yylex_internal(FILE *yyin) {
  int uniteCourante;
  char nom[100];
  char valeur[100]; 
  do {
    uniteCourante = yylex(); 
    if ( uniteCourante == ERREUR) {
    	erreur_1s("lexical",yytext); // erreur lexical 
	}
    nom_token( uniteCourante, nom, valeur );
    fprintf (stdout, "%s\t%s\t%s\n", yytext, nom, valeur);      
  } while (uniteCourante != FIN);
}

