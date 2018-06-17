#ifndef __SEMANTIQUE__
#define __SEMANTIQUE__


#include "syntabs.h"

void tab_n_prog(n_prog *n);
void tab_l_instr(n_l_instr *n);
void tab_instr(n_instr *n);
void tab_instr_si(n_instr *n);
void tab_instr_tantque(n_instr *n);
void tab_instr_faire(n_instr *n);      /* MODIFIE POUR EVAL */
void tab_instr_pour(n_instr *n);       /* MODIFIE POUR EVAL */
void tab_instr_affect(n_instr *n);
void tab_instr_appel(n_instr *n);
void tab_instr_retour(n_instr *n);
void tab_instr_ecrire(n_instr *n);
void tab_l_exp(n_l_exp *n);
void tab_exp(n_exp *n);
void tab_varExp(n_exp *n);
void tab_opExp(n_exp *n);
void tab_intExp(n_exp *n);
void tab_lireExp(n_exp *n);
void tab_appelExp(n_exp *n);
void tab_l_dec(n_l_dec *n);
void tab_dec(n_dec *n);
void tab_foncDec(n_dec *n);
void tab_varDec(n_dec *n);
void tab_tabDec(n_dec *n);
void tab_var(n_var *n);
void tab_var_simple(n_var *n);
void tab_var_indicee(n_var *n);
void tab_appel(n_appel *n);

void tab_n_prog(n_prog *n);

#endif
