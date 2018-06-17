#ifndef __DICO__
#define __DICO__

//#include "syntabs.h"

#define maxDico 100

#define C_VARIABLE_GLOBALE 1
#define C_VARIABLE_LOCALE 2
#define C_ARGUMENT 3

#define T_ENTIER 1
#define T_TABLEAU_ENTIER 2
#define T_FONCTION 3

typedef struct {
  char *identif;
  int classe; // portée
  int type;
  int adresse;
  int complement; // taille d'un tableau, nombre d'arguments d'une fonction
  int retour;
} desc_identif;

typedef struct {
  desc_identif tab[maxDico];
  int base;
  int sommet;
} dico_;

void entreeProg(void);
void entreeFonction(void);
void sortieFonction(void);
int ajouteIdentificateur(char *identif,  int classe, int type, int adresse, int complement);
int rechercheExecutable(char *identif, int cl, int typ, int compt);
int rechercheDeclarative(char *identif, int cxt, int typ);
void affiche_dico(int test);
void ajouteRetour(int base, int retour);
void rechercheMain(char *identif);

extern dico_ dico;
extern int contexte;
extern int adresseLocaleCourante;
extern int adresseArgumentCourant;
extern int adresseGlobaleCourante;

#endif
