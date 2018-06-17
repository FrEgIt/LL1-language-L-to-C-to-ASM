#ifndef __MIPS__
#define __MIPS__

#include "syntabs.h"

#define applist_remove_first(list) applist_remove_id(list, 1)
#define applist_remove_last(list) applist_remove_id(list, applist_length(list))



typedef struct 
{
  int imbrication_si; // si instruction bloc autre ++
  int etage_si; // n fois si dans le meme bloc alors ++
  int fonction_si;
}cpSI_;
extern cpSI_ Dico_SI;


typedef struct 
{
  int imbrication_tq; // si instruction bloc autre ++
  int etage_tq; // n fois si dans le meme bloc alors ++
  int fonction_tq;
} cpTQ_;

extern cpTQ_ Dico_TQ;



// LISTE DOUBLECHAINER POUR APPEL FONCTION ...
struct node
{
    int data;
    struct node *app_next;
    struct node *app_prev;
};

typedef struct applist
{
    int length;
    struct node *app_tail;
    struct node *app_head;
} Applist;

Applist *applist_new(void);
void applist_delete(Applist **app_list);
Applist *applist_append(Applist *app_list, int data);
Applist *applist_remove_id(Applist *app_list, int position);
int applist_length(Applist *p_list);
int applist_last_data(Applist *app_list);


							//Applist *list = NULL; déclaration vide








void mips_n_prog(n_prog *n);
void mips_l_instr(n_l_instr *n);
void mips_instr(n_instr *n);
void mips_instr_si(n_instr *n);
void mips_instr_tantque(n_instr *n);
void mips_instr_faire(n_instr *n);      /* MODIFIE POUR EVAL */
void mips_instr_pour(n_instr *n);       /* MODIFIE POUR EVAL */
void mips_instr_affect(n_instr *n);
void mips_instr_appel(n_instr *n);
void mips_instr_retour(n_instr *n);
void mips_instr_ecrire(n_instr *n);
void mips_l_exp(n_l_exp *n);
void mips_exp(n_exp *n);
void mips_varExp(n_exp *n);
void mips_opExp(n_exp *n);
void mips_intExp(n_exp *n);
void mips_lireExp(n_exp *n);
void mips_appelExp(n_exp *n);
void mips_l_dec(n_l_dec *n);
void mips_dec(n_dec *n);
void mips_foncDec(n_dec *n);
void mips_varDec(n_dec *n); // ok
void mips_tabDec(n_dec *n); // ok
void mips_var(n_var *n);
void mips_var_simple(n_var *n);
void mips_var_indicee(n_var *n);
void mips_appel(n_appel *n);

void mips_n_prog(n_prog *n);

#endif
