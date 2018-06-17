#include <stdio.h>
#include "syntabs.h"
#include "analyseur_semantique.h"
#include "util.h"
#include "dico.h"


int trace_tab = 1;
extern int uC;

/**
 * Axiome de départ
 * @param n [prog]
 */
void tab_n_prog(n_prog *n)  
{
  	entreeProg();
  	tab_l_dec(n->variables);
    adresseGlobaleCourante = 0; 
  	tab_l_dec(n->fonctions); 
    rechercheMain("main");
}

/**
 * lit la liste instruction
 * @param n [liste]
 */
void tab_l_instr(n_l_instr *n)
{
  if(n){
  tab_instr(n->tete);
  tab_l_instr(n->queue);
  }
}

/**
 * gère les instuctions
 * @param n [une instruction redirigeai vers celle qui correspond]
 */
void tab_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) tab_l_instr(n->u.liste);
    else if(n->type == affecteInst) tab_instr_affect(n);
    else if(n->type == siInst) tab_instr_si(n);
    else if(n->type == tantqueInst) tab_instr_tantque(n);
    else if(n->type == faireInst) tab_instr_faire(n);
    else if(n->type == pourInst) tab_instr_pour(n);    
    else if(n->type == appelInst) tab_instr_appel(n);
    else if(n->type == retourInst) tab_instr_retour(n);
    else if(n->type == ecrireInst) tab_instr_ecrire(n);
  }
}

/**
 * redirection de l' instruction si
 * @param n [instruction si]
 */
void tab_instr_si(n_instr *n)
{  
  
  tab_exp(n->u.si_.test);
  tab_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    tab_instr(n->u.si_.sinon);
  }
}

/**
 * redirection de l'instruction tant que
 * @param n [instruction tanque]
 */
void tab_instr_tantque(n_instr *n)
{
  tab_exp(n->u.tantque_.test);
  tab_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void tab_instr_faire(n_instr *n)          /* MODIFIE POUR EVAL */
{                                             /* MODIFIE POUR EVAL */
  // char *fct = "instr_faire";                  /* MODIFIE POUR EVAL */
  // tab_balise_ouvrante(fct, trace_tab);    /* MODIFIE POUR EVAL */
  tab_instr(n->u.faire_.faire);           /* MODIFIE POUR EVAL */
  tab_exp(n->u.faire_.test);              /* MODIFIE POUR EVAL */
  // tab_balise_fermante(fct, trace_tab);    /* MODIFIE POUR EVAL */
}                                             /* MODIFIE POUR EVAL */

/*-------------------------------------------------------------------------*/

void tab_instr_pour(n_instr *n)                /* MODIFIE POUR EVAL */
{                                                  /* MODIFIE POUR EVAL */
  tab_instr(n->u.pour_.init);                  /* MODIFIE POUR EVAL */
  tab_exp(n->u.pour_.test);                    /* MODIFIE POUR EVAL */
  tab_instr(n->u.pour_.faire);                 /* MODIFIE POUR EVAL */
  tab_instr(n->u.pour_.incr);                  /* MODIFIE POUR EVAL */
}                                                  /* MODIFIE POUR EVAL */

/**
 * redirection pour l'instruction affect
 * @param n [instruction affect]
 */
void tab_instr_affect(n_instr *n)
{
  tab_var(n->u.affecte_.var);
  tab_exp(n->u.affecte_.exp);
}

/**
 * redirection pour l'instruction appel
 * @param n [instruction appel]
 */
void tab_instr_appel(n_instr *n)
{
  tab_appel(n->u.appel);
}

/**
 * gestion de l'appel de fonction
 * @param n [appel]
 */
void tab_appel(n_appel *n) 
{  
  	tab_l_exp(n->args);
  	// création de la variable de passage pour compter cb de argument
	    n_l_exp * argstmp = n->args;
	    int argsNB = 0;
	    // on compte pour chacun
	        while (argstmp !=NULL)
	        {
	          argsNB++;
	          argstmp = argstmp->queue;
	        }
	// fin 
  	int rien_tab = rechercheExecutable(n->fonction, contexte, T_FONCTION, argsNB);
    rien_tab = 0;
}

/**
 * redirection pour l'instruction retour
 * @param n [instruction retour]
 */
void tab_instr_retour(n_instr *n) 
{
  tab_exp(n->u.retour_.expression);
}

/**
 * redirection pour l'instruction ecrire
 * @param n [instruction ecrire]
 */
void tab_instr_ecrire(n_instr *n) 
{
  tab_exp(n->u.ecrire_.expression);
}

/**
 * lit la liste des expressions
 * @param n [liste des expressions]
 */
void tab_l_exp(n_l_exp *n)
{
	if(n != NULL){
    	tab_exp(n->tete);
    	tab_l_exp(n->queue);
  	}
}

/**
 * Rediction des exp selon leur type
 * @param n [expression]
 */
void tab_exp(n_exp *n) 
{

  if(n->type == varExp) tab_varExp(n);
  else if(n->type == opExp) tab_opExp(n);
  else if(n->type == intExp) tab_intExp(n);
  else if(n->type == appelExp) tab_appelExp(n);
  else if(n->type == lireExp) tab_lireExp(n);
}

/**
 * redicrection de l'expresion var
 * @param n [exp]
 */
void tab_varExp(n_exp *n) 
{
  tab_var(n->u.var);
}

/**
 * Gestion des oprateur et de leur expression associative gauche
 * @param n [exp op]
 */
void tab_opExp(n_exp *n)  
{
  int rien_tab = 0;
  if(n->u.opExp_.op == plus) rien_tab = 1;
  else if(n->u.opExp_.op == moins) rien_tab = 1;
  else if(n->u.opExp_.op == fois) rien_tab = 1;
  else if(n->u.opExp_.op == divise) rien_tab = 1;
  else if(n->u.opExp_.op == modulo) rien_tab = 1;
  else if(n->u.opExp_.op == egal) rien_tab = 1;
  else if(n->u.opExp_.op == diff) rien_tab = 1;
  else if(n->u.opExp_.op == sup) rien_tab = 1;
  else if(n->u.opExp_.op == supeg) rien_tab = 1;
  else if(n->u.opExp_.op == inf) rien_tab = 1;
  else if(n->u.opExp_.op == infeg) rien_tab = 1;
  else if(n->u.opExp_.op == ou) rien_tab = 1;
  else if(n->u.opExp_.op == et) rien_tab = 1;
  else if(n->u.opExp_.op == non) rien_tab = 1;
  if( n->u.opExp_.op1 != NULL ) {
    tab_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    tab_exp(n->u.opExp_.op2);
  }
}

/**
 * rien
 * @param n [redirection vide]
 */
void tab_intExp(n_exp *n) 
{
  // char texte[ 50 ]; // Max. 50 chiffres
  // sprintf(texte, "%d", n->u.entier);
  // tab_element( "intExp", texte, trace_tab );
}

/**
 * rien
 * @param n [redirection vide]
 */void tab_lireExp(n_exp *n)  
{
  // char *fct = "lireExp";
  // tab_balise_ouvrante(fct, trace_tab);
  // tab_balise_fermante(fct, trace_tab);

}

/**
 * redicrection expression appel
 * @param n [exp]
 */
void tab_appelExp(n_exp *n)
{
  tab_appel(n->u.appel);
  
}

/**
 * Gestion de la liste des declaration
 * @param n [liste déclarative]
 */
void tab_l_dec(n_l_dec *n) 
{
  if( n ){
    tab_dec(n->tete);
    tab_l_dec(n->queue);
  }
}

/**
 * redirection de la déclation suivant son type
 * @param n [la déclation]
 */
void tab_dec(n_dec *n) 
{

  if(n != NULL){
    if(n->type == foncDec) {
      tab_foncDec(n);
    }
    else if(n->type == varDec) {
      tab_varDec(n);
    }
    else if(n->type == tabDec) { 
      tab_tabDec(n);
    }
  }
}

/**
 * gestion de la déclaration d'une fonction
 * @param n [declaration fonction]
 */
void tab_foncDec(n_dec *n) 
{
  int rien_tab = rechercheDeclarative(n->nom, contexte, T_FONCTION);
  rien_tab = 0;

    // création de la variable de passage pour compter cb de parametres

        n_l_dec * paramtmp = n->u.foncDec_.param;
        int paramNB = 0;

        	// on compte pour chacun

		        while (paramtmp != NULL)
		        {
		          	paramNB++;
		          	paramtmp = paramtmp->queue;
		        }

    // fin    
    adresseGlobaleCourante++; 
    int adresseGlobaleCourantetmp =  ajouteIdentificateur(n->nom, contexte, T_FONCTION, adresseGlobaleCourante, paramNB);
    adresseGlobaleCourantetmp = adresseGlobaleCourantetmp + 1 - 1;
    entreeFonction();
    contexte = C_ARGUMENT;
  	tab_l_dec(n->u.foncDec_.param);
  	contexte = C_VARIABLE_LOCALE;
  	tab_l_dec(n->u.foncDec_.variables);
  	tab_instr(n->u.foncDec_.corps);
  	affiche_dico(1);
    sortieFonction();
}

/**
 * gestion de la déclaration d'une variable simple
 * @param n [declaration variable simple]
 */
void tab_varDec(n_dec *n) 
{
  int rien_tab = rechercheDeclarative(n->nom, contexte, T_ENTIER);
  rien_tab = 0;
        if( contexte == C_VARIABLE_GLOBALE)
        {
          	adresseGlobaleCourante = adresseGlobaleCourante + 1 -dico.sommet + ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseGlobaleCourante, -1);
        }
       	else if ( contexte == C_ARGUMENT)
       	{
        	adresseArgumentCourant = 1 + ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseArgumentCourant, -1) - dico.base ;
       	}
       	else if ( contexte == C_VARIABLE_LOCALE)
       	{
          	adresseLocaleCourante =  1 + ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseLocaleCourante, -1) - dico.base - adresseArgumentCourant ;
       	}
}

/**
 * gestion de la délcaration d'une variable indicer
 * @param n [declaration variable indicer]
 */
void tab_tabDec(n_dec *n) 
{
  int rien_tab = rechercheDeclarative(n->nom, contexte, T_TABLEAU_ENTIER);
  rien_tab = 0;
	  if( contexte == C_VARIABLE_GLOBALE)
	   {
	      adresseGlobaleCourante = adresseGlobaleCourante + n->u.tabDec_.taille - dico.sommet + ajouteIdentificateur(n->nom, contexte, T_TABLEAU_ENTIER, adresseGlobaleCourante, n->u.tabDec_.taille);
   		}
}

/**
 * Rediction selon le tpe de la variable
 * @param n [description]
 */
void tab_var(n_var *n)  
{
  	if(n->type == simple) 
  	{
    	tab_var_simple(n);
  	}
  	else if(n->type == indicee) 
  	{
    	tab_var_indicee(n);
  	}
}

/**
 * gestion d'une variable simple
 * @param n [var simple]
 */
void tab_var_simple(n_var *n) 
{
	int rien_tab = rechercheExecutable(n->nom, contexte, T_ENTIER, 0);
  rien_tab = 0;
}

/**
 * gestion d'une variable indicé
 * @param n [var simple]
 */
void tab_var_indicee(n_var *n) 
{
  int rien_tab = rechercheExecutable(n->nom, contexte, T_TABLEAU_ENTIER, 0) ;
  rien_tab = 0;

}
