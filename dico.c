#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dico.h"
#include "util.h"

dico_ dico;
int contexte;
int adresseLocaleCourante;
int adresseArgumentCourant;
int adresseGlobaleCourante;
int CaractereActuel;

/**
 * initailisateur du dico
 */
void entreeProg(void){
  dico.base = 0;
  dico.sommet = 0;
  contexte = C_VARIABLE_GLOBALE;
  adresseGlobaleCourante = 0;
  adresseLocaleCourante = 0;
  adresseArgumentCourant = 0;
}
/**
 * [switch dico.sommet et dico.base]
 */
void entreeFonction(void){
  dico.base = dico.sommet;
  contexte = C_VARIABLE_LOCALE;
  adresseLocaleCourante = 0;
  adresseArgumentCourant = 0;

}

/**
 * [Sortie de la fonction contexte globale et écrasement du contenu]
 */
void sortieFonction(void){
  dico.sommet = dico.base ;
  dico.base = 0;
  contexte = C_VARIABLE_GLOBALE;
  adresseLocaleCourante = 0;
  adresseArgumentCourant = 0;  
  //dico.retour = 0;
}
/**
 * enregistrement sans vérification qu'il y a un retour dans la fonction
 * @param base   [dico.sommet de la fonction]
 * @param retour [void]
 */
void ajouteRetour(int base, int retour)
{
  if (retour)
  {
    dico.tab[base].retour = retour;
  }
}

/**
 * Ajouter les identificateur dans le dico et vérifie si le main et déclarer sans paramètres
 * @param  identif    [chaine de caractère]
 * @param  classe     [classe]
 * @param  type       [type]
 * @param  adresse    [adresse en base 10 ( pas fois 4 )]
 * @param  complement [taille tableau ou nombre aguments]
 * @return            [retourne le dico.somment actuel]
 */
int ajouteIdentificateur(char *identif, int classe, int type, int adresse, int complement)
{
  // condition main sans paramètre
  if( (strcmp("main",identif) == 0) && (complement>0)) 
  {
    erreur_1s_tab_decm("main", "doit être sans paramètre");
  } 
  dico.tab[dico.sommet].identif = strdup(identif);
  dico.tab[dico.sommet].classe = classe;
  dico.tab[dico.sommet].type = type;
  if( type == T_FONCTION)
    dico.tab[dico.sommet].adresse = maxDico * dico.sommet;
  else
    dico.tab[dico.sommet].adresse = adresse;
  dico.tab[dico.sommet].retour = 0;
  if( classe == C_ARGUMENT || classe == C_VARIABLE_LOCALE)
    dico.tab[dico.sommet].complement = -1;
  else
    dico.tab[dico.sommet].complement = complement;
  dico.sommet++;

  if(dico.sommet == maxDico){
    fprintf(stderr, "attention, plus de place dans le dictionnaire des \
                     identificateurs, augmenter maxDico\n");
   if (stderr != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            CaractereActuel = fgetc(stderr); // On lit le caractère
            printf("\n\n%c", CaractereActuel); // On l'affiche
        } while (CaractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de stderr)
        fclose(stderr);
    }
    exit(1);
  }
 /* affiche_dico(); */
  return dico.sommet - 1;
}

/**
 * Prend en compte la recherche de variable à éxécuter : 
 *   - tableau existant 
 *   - tableau indicé ou non 
 *   - le nombre d'argument 
 *   - l'existence des variable FONCTION, ENTIER, TABLEAU ; 
 * @param  identif [chaine de carctère correspodant à la variable attendu]
 * @param  cl      [classe atendu]
 * @param  typ     [type attendu]
 * @param  compt   [complément attentu]
 * @return         [ i > -1 si OK]
 */
int rechercheExecutable(char *identif, int cl, int typ, int compt)
{
  int i;
  for(i = dico.sommet - 1; i >= 0; i--)
  {
    if(strcmp(identif, dico.tab[i].identif) == 0)
    {
        if (cl == C_VARIABLE_LOCALE)
        {
          if (typ == T_TABLEAU_ENTIER)
           {
             if(dico.tab[i].type != typ) 
             {
              
              erreur_1s_tab_decm(identif, "tableau non existant");
              return -1;
             }
           }
           else if (typ == T_ENTIER)
           {
             if(dico.tab[i].type != typ) 
             {
              erreur_1s_tab_decm(identif, "tableau non indicé");
              return -1;
             }
           }
           else if (T_FONCTION == typ)
           {
             if( dico.tab[i].type != typ && dico.tab[i].complement != compt)
             {
                erreur_1s_tab_decm(identif, "fonction appeler avec le mauvais nombre d'agument");
                return -1;
             }
           }
        }
      return i;
    }
  }
  if(typ == T_FONCTION)
    erreur_1s_tab_decm(identif, "FONCTION non existant");
  else if ( typ == T_ENTIER)
    erreur_1s_tab_decm(identif, "ENTIER non existant");
  else if ( typ == T_TABLEAU_ENTIER)
    erreur_1s_tab_decm(identif, "TABLEAU ENTIER non existant");
  return -1;
}

/**
 * prend en compte les erreures déclarative LOCALE , ARGUMENT, GOLBALE.
 * @param  identif [chaine de caratère corespodante à la fonction]
 * @param  cxt     [contexte courant]
 * @param  typ     [type attendue]
 * @return         [-1 == OK]
 */
int rechercheDeclarative(char *identif, int cxt, int typ)
{
  int i;
  for(i = dico.base; i < dico.sommet; i++)
  {
    //getchar();
    if(strcmp(identif, dico.tab[i].identif)==0)
      {
        
        if ( (dico.tab[i].classe == C_VARIABLE_LOCALE || dico.tab[i].classe == C_ARGUMENT)  && cxt == C_VARIABLE_LOCALE) 
        {
          getchar();
          erreur_1s_tab_decm(identif, "declaration LOCALE qui existe déjà dans LOCALE ou ARGUMENT");
          return i;
        }
        if(cxt == C_VARIABLE_LOCALE  && (typ == T_FONCTION || typ == T_TABLEAU_ENTIER)  )
        {
          getchar();
            erreur_1s_tab_decm(identif, "declaration LOCALE d'une fonction ou d'un tableau");
            return i;
        }
        if( cxt == C_ARGUMENT && dico.tab[i].classe == C_ARGUMENT )
        {
          getchar();
            erreur_1s_tab_decm(identif, "declaration ARGUMENT qui existe déjà dans ARGUMENT");
            return i;
        }
        if (dico.tab[i].classe == C_VARIABLE_GLOBALE && cxt == C_VARIABLE_GLOBALE) 
        {
          getchar();
            erreur_1s_tab_decm(identif, "declaration VARIABLE GLOBALE qui existe déjà dans VARIABLE GLOBALE");
            return i;
        }
      }
    }
  return -1;
}

/**
 * affiche le dico avant la sortie de fonction car sinon ecrasé pour le contenu de celle-ci
 * @param test [pour voir si besoin d'afficher le dico]
 */
void affiche_dico(int test)
{
  if (test)
  {
      int i;
      printf("------------------------------------------\n");
      printf("base = %d\n", dico.base);
      printf("sommet = %d\n", dico.sommet);
      for(i=0; i < dico.sommet; i++){
        printf("%d ", i);
        printf("%s ", dico.tab[i].identif);
        if(dico.tab[i].classe == C_VARIABLE_GLOBALE)
          printf("GLOBALE ");
        else
        if(dico.tab[i].classe == C_VARIABLE_LOCALE)
          printf("LOCALE ");
        else
        if(dico.tab[i].classe == C_ARGUMENT)
          printf("ARGUMENT ");

        if(dico.tab[i].type == T_ENTIER)
          printf("ENTIER ");
        else if(dico.tab[i].type == T_TABLEAU_ENTIER)
          printf("TABLEAU ");
        /*     else if(dico.tab[i].type == _ARGUMENT) */
        /*       printf("ARGUMENT "); */
        else if(dico.tab[i].type == T_FONCTION)
          printf("FONCTION ");
        if(dico.tab[i].type == T_FONCTION)
          printf("%d ", 0);
        else
          printf("%d ", 4*dico.tab[i].adresse);

        printf("%d\n", dico.tab[i].complement);
      }
      printf("------------------------------------------\n");
  }
}

/**
 * recherche du main après avoir déclaré toutes les fonctions
 * @param identif ["main"]
 */
void rechercheMain(char *identif)
{
  int i;
  for(i = dico.sommet - 1; i >= 0; i--)
  {
    if(strcmp(identif, dico.tab[i].identif) == 0)
    {
      return;
    }
  }
    erreur_1s_tab_decm(identif,"main non déclaré.");
    return;
}
