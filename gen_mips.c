#include <stdio.h>
#include <stdlib.h>
#include "syntabs.h"
#include "gen_mips.h"
#include "util.h"
#include "dico.h"
#include "code.h"


cpSI_ Dico_SI;

cpTQ_ Dico_TQ;


extern int uC;
int scale;
int affect;
int OU_;
int ET_;

Applist *fonction_List;

/**
 * allocation en mémoire de la liste...
 * @return  [la liste alloué]
 */
Applist *applist_new(void)
{
    Applist *app_new = malloc(sizeof (Applist));
    if (app_new != NULL)
    {
        app_new->length = 0;
        app_new->app_head = NULL;
        app_new->app_tail = NULL;
    }
    return app_new;
}

/**
 * déssaloue la liste
 * @param app_list [la liste à supprimer]
 */
void applist_delete(Applist **app_list)
{
    if (*app_list != NULL)
    {
        struct node *app_temp = (*app_list)->app_head;
        while (app_temp != NULL)
        {
            struct node *app_del = app_temp;
            app_temp = app_temp->app_next;
            free(app_del);
        }
        free(*app_list), *app_list = NULL;
    }
}

/**
 * insère un nouveau élément en fin de liste
 * @param  app_list [la liste]
 * @param  data     [la donéee à inséré]
 * @return          [laliste ransformé]
 */
Applist *applist_append(Applist *app_list, int data)
{
    if (app_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        struct node *app_new = malloc(sizeof *app_new); /* Création d'un nouveau node */
        if (app_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            app_new->data = data; /* On 'enregistre' notre donnée */
            app_new->app_next = NULL; /* On fait pointer app_next vers NULL */
            if (app_list->app_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
            {
                app_new->app_prev = NULL; /* On fait pointer app_prev vers NULL */
                app_list->app_head = app_new; /* On fait pointer la tête de liste vers le nouvel élément */
                app_list->app_tail = app_new; /* On fait pointer la fin de liste vers le nouvel élément */
            }
            else /* Cas où des éléments sont déjà présents dans notre liste */
            {
                app_list->app_tail->app_next = app_new; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
                app_new->app_prev = app_list->app_tail; /* On fait pointer app_prev vers le dernier élément de la liste */
                app_list->app_tail = app_new; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
            }
            app_list->length++; /* Incrémentation de la taille de la liste */
        }
    }
    return app_list; /* on retourne notre nouvelle liste */
}

/**
 * supprime l'élement de la liste à la postion "position"
 * @param  app_list [liste]
 * @param  position [position de l'élément à supprimer]
 * @return          [renvoie la liste transformé]
 */
Applist *applist_remove_id(Applist *app_list, int position)
{
    if (app_list != NULL)
    {
        struct node *app_temp = app_list->app_head;
        int i = 1;
        while (app_temp != NULL && i <= position)
        {
            if (position == i)
            {
                if (app_temp->app_next == NULL)
                {
                    app_list->app_tail = app_temp->app_prev;
                    app_list->app_tail->app_next = NULL;
                }
                else if (app_temp->app_prev == NULL)
                {
                    app_list->app_head = app_temp->app_next;
                    app_list->app_head->app_prev = NULL;
                }
                else
                {
                    app_temp->app_next->app_prev = app_temp->app_prev;
                    app_temp->app_prev->app_next = app_temp->app_next;
                }
                free(app_temp);
                app_list->length--;
            }
            else
            {
                app_temp = app_temp->app_next;
            }
            i++;
        }
    }
    return app_list;
}

/**
 * pour connaite la taille de la liste et donc la postion du dernier élément
 * @param  app_list [la liste]
 * @return          [la taille de la liste]
 */
int applist_length(Applist *app_list)
{
    int ret = 0;
    if (app_list != NULL)
    {
        ret = app_list->length;
    }
    return ret;
}

/**
 * retourne l'addresse du dico.sommet de la dernier fonction appelé ou délcaré puis gérré dans le gen mips
 * @param  app_list [la liste]
 * @return          [l'adresse dans le dico]
 */
int applist_last_data(Applist *app_list)
{
  int retapp = app_list->app_tail->data;
  return retapp;
}

/**
 * initalise le dico si et tant que qui gère le numéro de fonction l'imbrication puis l'étage dans la fonction du et tant que puis géré dans le gen mips
 */
void initialise_dico_si_tq()
{
  Dico_TQ.imbrication_tq = 0;
  Dico_TQ.etage_tq = 0;
  Dico_TQ.fonction_tq = 0;
  Dico_SI.imbrication_si = 0;
  Dico_SI.etage_si = 0;
  Dico_SI.fonction_si = 0;
}


/**
 * axiome de départ
 * initalise les competeur des etiquette de test INFERIEUR, SUPERIEUR, EGAL, OU, ET, SI, TANT QUE, le dico ...
 * @param n [prog]
 */
void mips_n_prog(n_prog *n) 
{
    scale = 0;
    affect = 0;
    OU_ = 0;
    ET_ = 0;
    // int variablesNBNB = 0;

    fonction_List = NULL;
    fonction_List = applist_new();

    initialise_dico_si_tq();
  	entreeProg();
    code_entree_VG();
    // n_l_dec * tmp = n->variables;
    // while(tmp !=NULL)
    // {
    //   variablesNBNB++;
    //   tmp = tmp->queue;
    // }
  	mips_l_dec(n->variables);

    code_dec_var_fin_VG();
    adresseGlobaleCourante = 0;// adresse fonction = 0;
  	mips_l_dec(n->fonctions); 
    rechercheMain("main");
    // à tester
    // applist_delete(fonction_List);
}

/**
 * Lit la liste des instrcutions
 * @param n [liste instruction]
 */
void mips_l_instr(n_l_instr *n)
{
  if(n){
  mips_instr(n->tete);
  mips_l_instr(n->queue);
  }
}

/**
 * Rediction des instructions selon leur type
 *
 * @param n [instruction]
 */
void mips_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) 
    {
      Dico_SI.imbrication_si++; // imbrication du SI, TANT QUE
      Dico_TQ.imbrication_tq++;
      mips_l_instr(n->u.liste);
      Dico_SI.imbrication_si--; // desimbrication du SI, TANT QUE
      Dico_TQ.imbrication_tq--;
    }
    else if(n->type == affecteInst) mips_instr_affect(n); 
    else if(n->type == siInst) 
    {
      Dico_SI.etage_si++; // etage ++ pour SI
      mips_instr_si(n);
      Dico_SI.etage_si--; // etage -- pour SI
    }
    else if(n->type == tantqueInst) 
    {
      Dico_TQ.etage_tq++; // etage ++ pour TANT QUE
      mips_instr_tantque(n);
      Dico_TQ.etage_tq--; // etage -- pour TANT QUE
    }
    else if(n->type == faireInst) mips_instr_faire(n);
    else if(n->type == pourInst) mips_instr_pour(n); // pas à faire 
    else if(n->type == appelInst) 
    {
      mips_instr_appel(n); 
      applist_remove_last(fonction_List);
    }
    else if(n->type == retourInst) mips_instr_retour(n); 
    else if(n->type == ecrireInst) mips_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/
/**
 * gère le cas si plusieurs SI sont imbriqué par passage à code trois compteur la fonction, l'imbribrication instruction bloc, etage du si
 * @param n [instruction si]
 */
void mips_instr_si(n_instr *n)
{  
  int nonTEST;
  if(n->u.si_.sinon) nonTEST = 1;
  else nonTEST = 0;
  mips_exp(n->u.si_.test);
  code_inst_si_deb(nonTEST);
  mips_instr(n->u.si_.alors);
  code_inst_finsi();
  if(n->u.si_.sinon){
    code_inst_sinon();
    mips_instr(n->u.si_.sinon);
  }
  code_inst_si_fin();
}

/**
 * gère le cas si plusieurs si imbriqué par assage à code trois compteur la fonction, l'imbribrication instruction bloc, etage du tant que
 * @param n [instruction tant que]
 */
void mips_instr_tantque(n_instr *n)
{
  code_inst_tq_deb();
  mips_exp(n->u.tantque_.test);
  code_inst_tq_milieu();
  mips_instr(n->u.tantque_.faire);
  code_inst_tq_fin();
}

/*-------------------------------------------------------------------------*/
// 
// A FAIRE
// 

void mips_instr_faire(n_instr *n)  //         /* MODIFIE POUR EVAL */
{                                             /* MODIFIE POUR EVAL */
  mips_instr(n->u.faire_.faire);           /* MODIFIE POUR EVAL */
  mips_exp(n->u.faire_.test);              /* MODIFIE POUR EVAL */
}                                             /* MODIFIE POUR EVAL */

/*-------------------------------------------------------------------------*/
// 
// A FAIRE
// 
void mips_instr_pour(n_instr *n)                /* MODIFIE POUR EVAL */
{                                                  /* MODIFIE POUR EVAL */
  mips_instr(n->u.pour_.init);                  /* MODIFIE POUR EVAL */
  mips_exp(n->u.pour_.test);                    /* MODIFIE POUR EVAL */
  mips_instr(n->u.pour_.faire);                 /* MODIFIE POUR EVAL */
  mips_instr(n->u.pour_.incr);                  /* MODIFIE POUR EVAL */
}                                                  /* MODIFIE POUR EVAL */

/**
 * redirection d'affect par par un état affec grace une varaible globale qui designe son état 
 * @globale affect
 *                 1 etat affect 
 *                 0 etat non affect
 * @param n [instruction affecte]
 */
void mips_instr_affect(n_instr *n)
{
  mips_exp(n->u.affecte_.exp);
  affect = 1;
  mips_var(n->u.affecte_.var);
  affect = 0;
}

/**
 * redirection instruction affecte
 * @param n [instruction appel]
 */
void mips_instr_appel(n_instr *n)
{
  mips_appel(n->u.appel);
}


/**
 * gère l'appel à la fonction et l'empile dnas la la liste double chainé
 * @param n [l'appel]
 */
void mips_appel(n_appel *n)
{
    int i;
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
    code_exp_app_deb(n->fonction, argsNB);
  	
  	
  	i = rechercheExecutable(n->fonction, contexte, T_FONCTION, argsNB) ;
    fonction_List = applist_append(fonction_List,i);
    mips_l_exp(n->args);
    code_exp_app_saut(argsNB , dico.tab[i].retour,  affect, dico.tab[i].identif);



}

/**
 * Gestion de l'instruction retour et complété le dico pour savoir s'il un retour sans vérification 
 * liste doublechaine utlisé pour connaire le dico.sommet de la fonction dans decFontion
 * @param n [instruction retour]
 */
void mips_instr_retour(n_instr *n) 
{
  mips_exp(n->u.retour_.expression);
  code_inst_retour(dico.tab[applist_last_data(fonction_List)].complement);
  dico.tab[applist_last_data(fonction_List)].retour = 1;
}

/**
 * gestion de l'écriture au terminal
 * @param n [instruction ecrire]
 */
void mips_instr_ecrire(n_instr *n) 
{
  mips_exp(n->u.ecrire_.expression);
  code_exp_ecrire();
}

/**
 * Lit dans liste chainé des expression
 * @param n [lite des expressions]
 */
void mips_l_exp(n_l_exp *n) 
{
	if(n != NULL){
    	mips_exp(n->tete);
    	mips_l_exp(n->queue);
  	}
}

/**
 * redicrection de expression selon son type
 * @param n [expression en question]
 */
void mips_exp(n_exp *n) 
{

  if(n->type == varExp) mips_varExp(n);
  else if(n->type == opExp) mips_opExp(n); 
  else if(n->type == intExp) mips_intExp(n);
  else if(n->type == appelExp) mips_appelExp(n); 
  else if(n->type == lireExp) mips_lireExp(n);
}

/**
 * Redicrection vers var de l'expression soit pour affect soit pour lire dans la variable
 * géré par l'état affect [1;0]
 * @param n [expression]
 */
void mips_varExp(n_exp *n) 
{

  mips_var(n->u.var);
}

/**
 * Gestion des opérateurs selon leur type
 * court circuit de type et et ou par saut d'étiquette
 * @param n [expresion avec une opération]
 */
void mips_opExp(n_exp *n)  
{
  if(n->u.opExp_.op == ou)
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    code_op1_ou();
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op2_ou();
  }
  else if(n->u.opExp_.op == et)
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    code_op1_et();
    if( n->u.opExp_.op2 != NULL )
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op2_et(); 
  }
  else if(n->u.opExp_.op == plus)
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_plus();
  }
  else if(n->u.opExp_.op == moins) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_moins();
  }
  else if(n->u.opExp_.op == fois) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_fois();
  }
  else if(n->u.opExp_.op == divise) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_divise();
  }
  else if(n->u.opExp_.op == modulo) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_modulo();
  }
  else if(n->u.opExp_.op == egal) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_egal();
  }
  else if(n->u.opExp_.op == diff) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_diff();
  }
  else if(n->u.opExp_.op == sup) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_sup();
  }
  else if(n->u.opExp_.op == supeg) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_supeg();
  }
  else if(n->u.opExp_.op == inf) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_inf();
  }
  else if(n->u.opExp_.op == infeg) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) 
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_infeg();
  }
  else if(n->u.opExp_.op == non) 
  {
    if( n->u.opExp_.op1 != NULL ) 
    {
      mips_exp(n->u.opExp_.op1);
    }
    if( n->u.opExp_.op2 != NULL ) // déjà à NULL pour op2
    {
      mips_exp(n->u.opExp_.op2);
    }
    code_op_non();
  }
}

/**
 * Gestion de empilement d'unentier dans la pile
 * @param n [expression nombre]
 */
void mips_intExp(n_exp *n) 
{
  code_exp_int(n->u.entier);
}

/**
 * Gestion de de la lecture ( par la dernier valeur de la pile)
 * @param n [exprresion lire]
 */
void mips_lireExp(n_exp *n)
{
  code_exp_lire();
}

/**
 * Redicrection de l'expression appel
 * @param n [expression appel]
 */
void mips_appelExp(n_exp *n) 
{

  mips_appel(n->u.appel);

}

/**
 * lit dans la liste chainé de des déclaration
 * @param n [liste des déclaration]
 */
void mips_l_dec(n_l_dec *n) 
{
  if( n ){
    mips_dec(n->tete);
    mips_l_dec(n->queue);
  }
}

/**
 * Redirection de la declaration à partir de son type
 * @param n [declaration cible type]
 */
void mips_dec(n_dec *n) 
{

  if(n != NULL){
    if(n->type == foncDec) {
      mips_foncDec(n);
    }
    else if(n->type == varDec) {
      mips_varDec(n);
    }
    else if(n->type == tabDec) { 
      mips_tabDec(n);
    }
  }
}

/**
 * jal vers fin de fonction pour "main" et verifié si "main" exist
 * Gestion de la décraltion de fonction
 * @param n [declaration de fonction]
 */
void mips_foncDec(n_dec *n)
{
  int rien_tab = rechercheDeclarative(n->nom, contexte, T_FONCTION) ;
  rien_tab = 1; 

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
    
    adresseGlobaleCourante = ajouteIdentificateur(n->nom, contexte, T_FONCTION, 0, paramNB);

    fonction_List = applist_append(fonction_List,adresseGlobaleCourante); //dico.sommet = addresseGlobaleCourante

    code_dec_fct_VG(n->nom);
    entreeFonction();
    contexte = C_ARGUMENT;
  	mips_l_dec(n->u.foncDec_.param);
  	contexte = C_VARIABLE_LOCALE;
    // création de la variable de passage pour compter cb de variables globales

        n_l_dec * variablestmp = n->u.foncDec_.variables;
        int variablesNB = 0;

          // on compte pour chacun

            while (variablestmp != NULL)
            {
                variablesNB++;
                variablestmp = variablestmp->queue;
            }

    // fin 
    code_dec_var_VL(variablesNB);
  	mips_l_dec(n->u.foncDec_.variables);
    Dico_SI.fonction_si++;
    Dico_TQ.fonction_tq++;
  	mips_instr(n->u.foncDec_.corps);
  	affiche_dico(0);
    code_fin_fct(variablesNB);
    sortieFonction();
}


/**
 * Gestion de la déclaration de variable simple selon son contexte
 * Globale ecrit après le .data
 * sinon géré par le dico
 * @param n [variable à déclarer]
 */
void mips_varDec(n_dec *n) 
{
  int rien_tab = rechercheDeclarative(n->nom, contexte, T_ENTIER) ;
  rien_tab = 1;
        if( contexte == C_VARIABLE_GLOBALE)
        {
          	adresseGlobaleCourante = adresseGlobaleCourante + 1 -dico.sommet + ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseGlobaleCourante, -1);
            code_dec_var_VG(n->nom);
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
 * Gestion de la déclaration de la variable tableau
 * @param n [declaration Entier tableau]
 */
void mips_tabDec(n_dec *n)
{
   int rien_tab  = rechercheDeclarative(n->nom, contexte, T_TABLEAU_ENTIER) ;
   rien_tab = 1;
	  if( contexte == C_VARIABLE_GLOBALE)
    {
      int a = dico.sommet +1;
      adresseGlobaleCourante = adresseGlobaleCourante /*+ n->u.tabDec_.taille*/ - a+ ajouteIdentificateur(n->nom, contexte, T_TABLEAU_ENTIER, adresseGlobaleCourante, n->u.tabDec_.taille);
   	  code_dec_tab_VG(n->nom, n->u.tabDec_.taille);  
    }
}

/**
 * Redirection de var vers selon son type
 * @param n [var indice ou simple]
 */
void mips_var(n_var *n)  
{
  	if(n->type == simple) 
  	{
    	mips_var_simple(n);
  	}
  	else if(n->type == indicee) 
  	{
    	mips_var_indicee(n);
  	}
}

/**
 * Gestion de la variable simple si epilement [affect : 0] ou affectation [affect : 1]
 * @param n [var simple]
 */
void mips_var_simple(n_var *n) 
{
  int i = 0;
	i = rechercheExecutable(n->nom, contexte, T_ENTIER, 0);
  if (affect)
  {
    code_exp_affect_s(dico.tab[i].classe, dico.tab[i].complement ,dico.tab[i].adresse);
  }
  else
  {
    code_exp_s(dico.tab[i].classe, applist_last_data(fonction_List), dico.tab[i].adresse);

  }
}

/**
 * Gestion de la variable indicé si epilement [affect : 0] ou affectation [affect : 1]
 * @param n [var indicé]
 */
void mips_var_indicee(n_var *n) 
{
  int i = 0;	
  i = rechercheExecutable(n->nom, contexte, T_TABLEAU_ENTIER, 0) ;
  
  if (affect)
  {
    affect = 0;
    mips_exp( n->u.indicee_.indice );
    affect = 1;
    code_exp_affect_t(dico.tab[i].adresse);
  }
  else
  {
    mips_exp( n->u.indicee_.indice );
    code_exp_t(dico.tab[i].adresse);
  }

}