#ifndef __UTIL__
#define __UTIL__
//
char *duplique_chaine(char *s);
void erreur(char *message);
void erreur_1s(char *message, char *s);
void affiche_balise_ouvrante(const char *fct_, int trace_xml);
void affiche_balise_fermante(const char *fct_, int trace_xml);
void affiche_element(char *fct_, char *texte_, int trace_xml);
void affiche_texte(char *texte_, int trace_xml);
void erreur_1d(char *message, int uc);
void erreur_1d_synt(const char *message, int uc);
void erreur_1d_abstrait(const char *message, int uC);
void erreur_1s_tab_decm(char* nom, char* message);
void erreur_1d_tab_dec(const char *message, int uc);

#endif

