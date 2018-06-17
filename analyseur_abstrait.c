#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "premiers.h"
#include "suivants.h"
#include "util.h"
#include "analyseur_lexical.h"
#include "analyseur_abstrait.h"
#include "affiche_arbre_abstrait.h"
#include "analyseur_semantique.h"
#include "gen_mips.h"

extern FILE *yyin;


int uC;
int affdico;
int testdico;
int mips;
int naffect;
int ajouter;


int test_tab(int x)
{
  return (x == -1);
}


/**
 * test le cas si uc appartient à premier de la fonction courante
 * @param  uc uniteCourante dans le fichier *.l à lire créé depuis analyseur_lexical.c dans yylex();
 * @return    le test
 */
int comparer_(int uc)
{
    return uc == uC;
}

/**
 * test le cas si EPSILON appartient à premier de la fonction courante et donc regarde les suivants (premiers.c)
 * test le cas si EPSILON appartient à permier et suivant de la fonction courante et si la c'est la FIN (premiers.c suivants.c symboles.c)
 * @param  fonction fonction courante depuis le fichier symbole.h
 * @return          le test
 */
int suivs(int fonction)
{
    return 
    (
        est_premiers(EPSILON,fonction) 
            &&
                (
                    est_suivants(uC, fonction) 

                        || 

                            (   
                                est_suivants(EPSILON,fonction) && comparer_(FIN) 
                            )
                )
    );
}

/**
 * test si l'uniteCourante appartient aux premiers de la fonction avec la fonction est_premier(int terminal, int non_terminal) (premiers.c)
 * @param  fonction fonction fonction courante depuis le fichier symbole.h
 * @return          le test
 */
int prems(int fonction)
{
    return est_premiers(uC,fonction);
}

/**
 * effectue la lecture de la prochaine uniteCourante du fichier *.l
 * uniteCourante : créé depuis analyseur_lexical.c avec yylex();
 */
void Consommer()
{
    uC = yylex();
}

/**
 * test effectué dans le main pour l'analyseur Abstrait
 */
void test_yyasynt_internal()
{
    initialise_premiers();
    initialise_suivants();
    affdico = 0;
    mips = 0;
    testdico = 0;
    ajouter = 0;
    uC = -3;
    Consommer();
    n_prog *x= NULL;
    while(uC != FIN)
    {
        x = programme$();
    }
    affiche_n_prog(x);
    return;
}

/**
 * test effectué dans le main pour l'analyseur Sémantique
 */
void test_yytab_internal()
{
    initialise_premiers();
    initialise_suivants();
    Consommer();
    n_prog *x= NULL;
    affdico = 1;
    testdico = 1;
    mips = 0;
    while(uC != FIN)
    {
        x = programme$();
    }
    tab_n_prog(x);
    return;
}

/**
 * générateur MIPS effectué dans le main avec la vérification des analyseurs
 */
void test_yymips_internal()
{
    initialise_premiers();
    initialise_suivants();
    affdico = 0;
    testdico = 1;
    mips = 1;
    naffect = 1;
    Consommer();
    n_prog *x= NULL;
    while(uC != FIN)
    {
        x = programme$();
    }
    mips_n_prog(x);
    return;
}

/**
 * "1"
 * Partie gauche : Programe -> optDecVariables listeDecFonctions
 * Premier : EPSILON ;  ENTIER ;  ID_FCT ;
 * Suivant : BOTTOM ;
 */
n_prog * programme$()
{
    n_prog *prog = NULL;
    n_l_dec *variables = NULL;
    n_l_dec *fonctions = NULL;
    if (prems(programme_))
    {
       variables = optDecVariables$();
       fonctions = listeDecFonctions$();
       prog = cree_n_prog(variables,fonctions);
       return prog;
    }
    else if(suivs(programme_))
        return prog;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return prog;
}

/**
 * "2"
 * Partie gauche : optDecVariables -> listeDecVariables POINT_VIRGULE | EPSILON
 * Premier : EPSILON ;  ENTIER ;
 * Suivant : BOTTOM  ; ID_FCT  ; ACCOLADE_OUVRANTE ;
 */
n_l_dec * optDecVariables$()
{
    n_l_dec * ldv = NULL;
    if (prems(optDecVariables_))
    {
       ldv = listeDecVariables$();

       if( !comparer_(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return ldv;
    }
    else if(suivs(optDecVariables_))return ldv;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return ldv;
}

/**
 * "3"
 * Partie gauche : listeDecVariables -> declarationVariable listeDecVariablesBis
 * Premier : ENTIER ;
 * Suivant : POINT_VIRGULE  ; PARENTHESE_FERMANTE ;
 */
n_l_dec * listeDecVariables$()
{
    n_dec *tete = NULL;
    n_l_dec *queue = NULL;
    n_l_dec *res = NULL;
    if (prems(listeDecVariables_))
    {
       tete = declarationVariable$();
       queue = listeDecVariablesBis$();
       res = cree_n_l_dec(tete,queue);
       return res;
    }
    else if(suivs(listeDecVariables_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return res; 
}

/**
 * "4"
 * Partie gauche : listeDecVariablesBis -> VIRGULE declarationVariable listeDecVariablesBis | EPSILON
 * Premier : EPSILON ;  VIRGULE ;
 * Suivant : POINT_VIRGULE  ; PARENTHESE_FERMANTE ;
 */
n_l_dec * listeDecVariablesBis$()
{
    n_l_dec *queue = NULL;
    n_dec *tete = NULL;
    n_l_dec *res = NULL;
    if (prems(listeDecVariablesBis_))
    {
       if( !comparer_(VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       tete = declarationVariable$();
       queue = listeDecVariablesBis$(tete); // null
       res = cree_n_l_dec(tete,queue); // tete b

       return res;
    }
    else if(suivs(listeDecVariablesBis_)) 
    {
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "5"
 * Partie gauche : declarationVariable -> ENTIER ID_VAR optTailleTableau
 * Premier : ENTIER ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; PARENTHESE_FERMANTE ;
 */
n_dec * declarationVariable$()
{
    n_dec *dv = NULL;
    char *nom_var = malloc(50*sizeof(char));
    if (prems(declarationVariable_))
    {
       //un seul terminal = ENTIER
       Consommer();

       if( !comparer_(ID_VAR) ) erreur_1d_synt(__FUNCTION__,uC);
       strcpy(nom_var,yytext);
       Consommer();
       dv = optTailleTableau$(nom_var);
       return dv;
    }
    else if(suivs(declarationVariable_))return dv;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }  
    return dv;  
}

/**
 * "6"
 * Partie gauche : optTailleTableau -> CROCHET_OUVRANT NOMBRE CROCHET_FERMANT | EPSILON
 * Premier : EPSILON ;  CROCHET_OUVRANT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; PARENTHESE_FERMANTE ;
 */
n_dec * optTailleTableau$(char *nom)
{
    n_dec *ott = NULL;
    if (prems(optTailleTableau_))
    {
       //un seul terminal CROCHET_OUVRANT
       Consommer();

       int taille = 0;

       if( !comparer_(NOMBRE) ) erreur_1d_synt(__FUNCTION__,uC);
       taille = atoi(yytext);
       Consommer();

       if( !comparer_(CROCHET_FERMANT) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       ott = cree_n_dec_tab(nom,taille);
       
       return ott;
    }
    else if(suivs(optTailleTableau_))
    { 
        ott = cree_n_dec_var(nom);
        return ott;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return ott;
}

/**
 * "7"
 * Partie gauche : listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
 * Premier : EPSILON ;  ID_FCT ;
 * Suivant : BOTTOM ;
 */
n_l_dec * listeDecFonctions$()
{
    n_dec   * tete  = NULL;
    n_l_dec * queue = NULL;
    n_l_dec * res   = NULL;
    if (prems(listeDecFonctions_))
    {
       tete = declarationFonction$();
       queue = listeDecFonctions$(tete);
       res = cree_n_l_dec(tete, queue);
       return res;


    }
    else if(suivs(listeDecFonctions_))
    {
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "8"
 * Partie gauche : declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
 * Premier : ID_FCT ;
 * Suivant : BOTTOM  ; ID_FCT ;
 */
n_dec * declarationFonction$()
{
    n_l_dec * param     = NULL ;
    n_l_dec * variables = NULL ;
    n_instr * corps     = NULL ;
    n_dec   * res       = NULL ;
    char    * nom       = malloc(100 * sizeof(char));
    if (prems(declarationFonction_))
    {
       //un seul terminal ID_FCT
        strcpy(nom,yytext);
        
        Consommer();

       param = listeParam$();
       variables = optDecVariables$();
       
       corps = instructionBloc$();
       
       res = cree_n_dec_fonc(nom,param,variables,corps);
       
       
       return res;

    }
    else if(suivs(declarationFonction_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "9"
 * Partie gauche : listeParam -> PARENTHESE_OUVRANTE optListeDecVariables PARENTHESE_FERMANTE
 * Premier : PARENTHESE_OUVRANTE ;
 * Suivant : ENTIER  ; ACCOLADE_OUVRANTE ;
 */
n_l_dec * listeParam$()
{
    n_l_dec * oldv = NULL;
    if (prems(listeParam_))
    {
       //un seul terminal PARENTHESE_OUVANTE
       Consommer();

       oldv = optListeDecVariables$();

       if ( !comparer_(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return oldv;
    }
    else if(suivs(listeParam_))return oldv;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return oldv;
}

/**
 * "10"
 * Partie gauche : optListeDecVariables -> listeDecVariables | EPSILON
 * Premier : EPSILON ;  ENTIER ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
n_l_dec * optListeDecVariables$()
{
    n_l_dec * ldv = NULL;
    if (prems( optListeDecVariables_))
    {
       ldv = listeDecVariables$();
       return ldv;
    }
    else if(suivs(optListeDecVariables_))return ldv;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return ldv; 
}

/**
 * "11"
 * Partie gauche : instruction -> instructionAffect | instructionBloc | instructionSi | instructionTantque | instructionAppel | instructionRetour | instructionEcriture | instructionVide
 * Premier : POINT_VIRGULE ;  ID_VAR ;  ID_FCT ;  ACCOLADE_OUVRANTE ;  SI ;  TANTQUE ;  RETOUR ;  ECRIRE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instruction$()
{
    n_instr *inst = NULL;
    if (prems(instruction_))
    {
       if(prems(instructionAffect_)) inst = instructionAffect$();
       else if(prems(instructionBloc_) ) inst = instructionBloc$();
       else if(prems(instructionSi_)) inst = instructionSi$();
       else if(prems(instructionTantque_)) inst = instructionTantque$();
       else if(prems(instructionAppel_)) inst = instructionAppel$();
       else if(prems(instructionRetour_)) inst = instructionRetour$();
       else if(prems(instructionEcriture_)) inst = instructionEcriture$();
       else if(prems(instructionVide_)) inst = instructionVide$();
       return inst;
    }
    else if(suivs(instruction_))return inst;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return inst; 
}

/**
 * "12"
 * Partie gauche : instructionAffect -> var EGAL expression POINT_VIRGULE
 * Premier : ID_VAR ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionAffect$()
{
    n_var   * varx = NULL ;
    n_exp   * exp = NULL ;
    n_instr * res = NULL ;
    if (prems(instructionAffect_))
    {
       naffect = 0;

       varx = var$();

       naffect = 1;

       if( !comparer_(EGAL) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       exp = expression$();

       if( !comparer_(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       res = cree_n_instr_affect(varx, exp);

       return res;

    }
    else if(suivs(instructionAffect_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return res;
}

/**
 * "13"
 * Partie gauche : instructionBloc -> ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE
 * Premier : ACCOLADE_OUVRANTE ;
 * Suivant : POINT_VIRGULE  ; BOTTOM  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; SINON  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionBloc$()
{
    n_l_instr * liste = NULL ;
    n_instr   * res   = NULL ;
    if (prems(instructionBloc_))
    {
       // un seul terminal ACCOLADE_OUVRANTE
       Consommer();

       liste = listeInstructions$();
       res   = cree_n_instr_bloc(liste);

       if( !comparer_(ACCOLADE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return res;

    }
    else if(suivs(instructionBloc_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return res;
}

/**
 * "14"
 * Partie gauche : listeInstructions -> instruction listeInstructions | EPSILON
 * Premier : POINT_VIRGULE ;  EPSILON ;  ID_VAR ;  ID_FCT ;  ACCOLADE_OUVRANTE ;  SI ;  TANTQUE ;  RETOUR ;  ECRIRE ;
 * Suivant : ACCOLADE_FERMANTE ;
 */
n_l_instr * listeInstructions$()
{
    n_instr   * tete  = NULL ;
    n_l_instr * queue = NULL ;
    n_l_instr * res   = NULL ;
    if (prems(listeInstructions_))
    {
       tete = instruction$();
       queue = listeInstructions$();
       res   = cree_n_l_instr(tete, queue);
       return res;
    }
    else if(suivs(listeInstructions_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return res;
}

/**
 * "15"
 * Partie gauche : instructionSi -> SI expression ALORS instructionBloc optSinon
 * Premier : SI ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionSi$()
{
    n_exp   * test  = NULL ;
    n_instr * alors = NULL ;
    n_instr * sinon = NULL ;
    n_instr * res   = NULL ;
    if (prems(instructionSi_))
    {
       // un seul terminal SI
       Consommer();

       test = expression$();

       if( !comparer_(ALORS) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       alors = instructionBloc$();
       sinon = optSinon$();
       res = cree_n_instr_si(test, alors, sinon);
       return res;

    }
    else if(suivs(instructionSi_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "16"
 * Partie gauche : optSinon -> SINON instructionBloc | EPSILON
 * Premier : EPSILON ;  SINON ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * optSinon$()
{
    n_instr * ib = NULL ;
    if (prems(optSinon_))
    {
    
       // un seul terminal SINON
       Consommer();

       ib = instructionBloc$();
       return ib;

    }
    else if(suivs(optSinon_))return ib;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return ib; 
}

/**
 * "17"
 * Partie gauche : instructionTantque -> TANTQUE expression FAIRE instructionBloc
 * Premier : TANTQUE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionTantque$()
{
    n_exp   * test  = NULL ;
    n_instr * faire = NULL ;
    n_instr * res   = NULL ;
    if (prems(instructionTantque_))
    {
       // un seul terminal TANTQUE
       Consommer();

       test = expression$();

       if( !comparer_(FAIRE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       faire = instructionBloc$();
       res = cree_n_instr_tantque(test, faire);
       return res;

    }
    else if(suivs(instructionTantque_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return res;
}

/**
 * "18"
 * Partie gauche : instructionAppel -> appelFct POINT_VIRGULE
 * Premier : ID_FCT ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionAppel$()
{
    n_appel * appf  = NULL ;
    n_instr * res = NULL ;
    if (prems(instructionAppel_))
    {
       appf = appelFct$();
       res = cree_n_instr_appel(appf);

       if( !comparer_(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return res;

    }
    else if(suivs(instructionAppel_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "19"
 * Partie gauche : instructionAppel -> RETOUR expression POINT_VIRGULE
 * Premier : RETOUR ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionRetour$()
{
    n_exp * exp = NULL ;
    n_instr * res = NULL ;
    if (prems(instructionRetour_))
    {
       // un seul terminal RETOUR
       Consommer();

       exp = expression$();
       res = cree_n_instr_retour(exp);

       if( !comparer_(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return res;
    }
    else if(suivs(instructionRetour_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }  
    return res;  
}

/**
 * "20"
 * Partie gauche : instructionEcriture -> ECRIRE PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE POINT_VIRGULE
 * Premier : ECRIRE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionEcriture$()
{
    n_exp   * exp = NULL;
    n_instr * res = NULL;
    if (prems(instructionEcriture_))
    {
       // un seul terminal ECRIRE
       Consommer();

       if( !comparer_(PARENTHESE_OUVRANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       exp = expression$();
       res = cree_n_instr_ecrire(exp);

       if( !comparer_(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       if( !comparer_(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       return res;
    }
    else if(suivs(instructionEcriture_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "21"
 * Partie gauche : instructionVide -> POINT_VIRGULE
 * Premier : POINT_VIRGULE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
n_instr * instructionVide$()
{
    n_instr * res = NULL ;
    if (prems(instructionVide_))
    {
       // un seul terminal POINT_VIRGULE
       Consommer();
       res = cree_n_instr_vide();
       return res;
    }
    else if(suivs(instructionVide_)) return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "22"
 * Partie gauche : expression -> conjonction expressionBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE ;
 *
 * Père : tete 
 */
n_exp * expression$()
{
    n_exp * tete = NULL ;
    n_exp * queue = NULL ;
    n_exp * res  = NULL ;
    if (prems(expression_))
    {
       tete = conjonction$();
       queue = expressionBis$(tete);
       if (!queue) res = tete; // si queue est vide et fonctionne avec un argument aussi car renvoie le meme de condition ou autre
       else  res = queue;
       return res;
    }
    else if(suivs(expression_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "23"
 * Partie gauche : expressionBis -> OU conjonction expressionBis | EPSILON
 * Premier : EPSILON ;  OU ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE ;
 *
 * Père : h
 * Fils : x
 */
n_exp * expressionBis$(n_exp *h)
{
    n_exp *x = NULL;
    n_exp *res= NULL;
    n_exp *hf = NULL;
    if (prems(expressionBis_))
    {
       // un seul terminal OU
       Consommer();
       
       x = conjonction$();
       hf = cree_n_exp_op(ou, h, x);
       res =expressionBis$(hf);// pas besoin queue car boucler avec suivant avec "h"
       return res;
    }
    else if(suivs(expressionBis_)) 
    {
        res = h;
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "24"
 * Partie gauche : conjonction -> negation conjonctionBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU ;
 *
 * Père : tete
 */
n_exp * conjonction$()
{
    n_exp * tete = NULL ;
    n_exp * queue = NULL ;
    n_exp * res  = NULL ;
    if (prems(conjonction_))
    {
       tete = negation$();
       queue = conjonctionBis$(tete);
       if (!queue) res = tete; // si queue est vide
       else res = queue;
       return res;

    }
    else if(suivs(conjonction_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return res; 
}

/**
 * "25"
 * Partie gauche : conjonctionBis -> ET negation conjonctionBis | EPSILON
 * Premier : EPSILON ;  ET ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU ;
 *
 * Père : h
 * Fils ; x
 */
n_exp * conjonctionBis$(n_exp *h)
{
    n_exp *x = NULL;
    n_exp *res= NULL;
    n_exp *hf = NULL;
    if (prems(conjonctionBis_))
    {
       // un seul terminal ET
       Consommer();
       x = negation$();
       hf = cree_n_exp_op(et, h, x);
       res = conjonctionBis$(hf); // pas de queue vu que suivant est là avec "h"
       

    }
    else if(suivs(conjonctionBis_)) 
    {
        res = h;
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "26"
 * Partie gauche : negation -> NON comparaison | comparaison
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 *
 * etat : nont
 */
n_exp * negation$()
{
    n_exp * res = NULL;
    n_exp * hf = NULL;
    n_exp * not = NULL;
    int nont = 0;
    if (prems(negation_))
    {
       if(comparer_(NON))
       {
            // si le terminal NON
            Consommer();
            nont = 1;
       }
        hf = comparaison$();
        res = hf ;
        if(nont) res = cree_n_exp_op(non, hf, not); // 2 argument demandé 1 non NULL
        return res;
    }
    else if(suivs(negation_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "27"
 * Partie gauche : comparaison -> expArith comparaisonBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 *
 * Père : tete
 */
n_exp *comparaison$()
{
    n_exp * tete = NULL ;
    n_exp * queue = NULL ;
    n_exp * res  = NULL ;
    if (prems(comparaison_))
    {
       tete = expArith$();
       queue = comparaisonBis$(tete);
       if (!queue) res = tete; // si queue est vide
       else res = queue;
       return res;
    }
    else if(suivs(comparaison_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}


/**
 * "28"
 * Partie gauche : comparaisonBis -> EGAL expArith comparaisonBis | INFERIEUR expArith comparaisonBis | SUPERIEUR expArith comparaisonBis | EPSILON
 * Premier : EPSILON ;  EGAL ;  INFERIEUR ;  SUPERIEUR ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 *
 * Père: h
 * Fils : x
 */
n_exp * comparaisonBis$(n_exp *h)
{
    n_exp *x = NULL;
    n_exp *hf = NULL;
    n_exp * res = NULL;
    int ega = 0;
    int supe = 0;
    int infe = 0;

    if (prems(comparaisonBis_))
    {
       // les seuls terminal à comsommer sont  EGAL, SUPERIEUR, INFERIEUR

       if(comparer_(EGAL))
       {
            // si le terminal EGAL
            Consommer();
            ega = 1;
       }
       else if(comparer_(INFERIEUR))
       {
            // si le terminal INFERIEUR
            Consommer();
            infe = 1;
       }
       else if(comparer_(SUPERIEUR))
       {
            // si le terminal EGAL
            Consommer();
            supe = 1;
       }

       x = expArith$();
       if(ega) hf = cree_n_exp_op(egal,h,x);
       else if (infe) hf = cree_n_exp_op(inf,h,x);
       else /*if (supe)*/ hf = cree_n_exp_op(sup,h,x);
       res = comparaisonBis$(hf); // pas de queue vu que suivant est là avec "h"
       return res;
    }
    else if(suivs(comparaisonBis_))
    {
        res = h;
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "29"
 * Partie gauche : expArith -> terme expArithBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR ;
 *
 * Père : tete
 */
n_exp * expArith$()
{
    n_exp * tete = NULL ;
    n_exp * queue = NULL ;
    n_exp * res  = NULL ;
    if (prems(expArith_))
    {
       tete = terme$();
       queue = expArithBis$(tete);
       if (!queue) res = tete; // si queue est vide
       else res = queue;
       return res;
    }
    else if(suivs(expArith_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 * "30"
 * Partie gauche : expArithBis -> PLUS terme expArithBis | MOINS terme expArithBis | EPSILON
 * Premier : EPSILON ;  PLUS ;  MOINS ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR ;
 * 
 * Père : h
 * Fils : x
 */
n_exp * expArithBis$(n_exp *h)
{
    n_exp * x = NULL;
    n_exp * res = NULL;
    n_exp * hf = NULL;
    int pl = 0;
    int mo = 0;
    if (prems(expArithBis_))
    {
       // les seuls terminal à comsommer sont PLUS et MOINS

       if(comparer_(PLUS))
       {
            // si le terminal PLUS
            Consommer();
            pl = 1;
       }
       else if(comparer_(MOINS))
       {
            // si le terminal MOINS
            Consommer();
            mo = 1;
       }

       x = terme$();
       if(pl) hf = cree_n_exp_op(plus,h,x);
       else hf = cree_n_exp_op(moins,h,x);
       res = expArithBis$(hf);
       return res;
    }
    else if(suivs(expArithBis_))
    {
        res = h;
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 *  "31"
 * Partie gauche : terme -> facteur termeBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS ;
 *
 * Père : tete
 */
n_exp * terme$()
{
    n_exp * tete = NULL ;
    n_exp * queue = NULL ;
    n_exp * res  = NULL ;
    if (prems(terme_))
    {
       tete = facteur$();
       queue = termeBis$(tete);
       if (!queue) res = tete; // si queue est vide
       else res = queue;
       return res;
    }
    else if(suivs(terme_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 *  "32"
 * Partie gauche : termeBis -> FOIS facteur termeBis | DIVISE facteur termeBis | MODULO facteur termeBis | EPSILON
 * Premier : EPSILON ;  FOIS ;  DIVISE ;  MODULO ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS ;
 *
 * Père : h
 * Fils : x
 */
n_exp * termeBis$(n_exp *h)
{
    n_exp * res = NULL;
    n_exp * x = NULL;
    n_exp * hf = NULL;
    int f = 0;
    int d = 0;
    int m = 0;
    if (prems(termeBis_))
    {
       // les seuls terminal à comsommer sont FOIS, DIVISE et MODULO

       if(comparer_(FOIS))
       {
            // si le terminal FOIS
            Consommer();
            f = 1;
       }
       else if(comparer_(DIVISE))
       {
            // si le terminal DIVISE
            Consommer();
            d = 1;
       }
       else if(comparer_(MODULO))
       {
            // si le terminal MODULO
            Consommer();
            m = 1;
       }

       x = facteur$();
       if(f) hf = cree_n_exp_op(fois,h,x);
       else if(d) hf = cree_n_exp_op(divise,h,x);
       else hf = cree_n_exp_op(modulo,h,x);
       res = termeBis$(hf);
       return res;
    }
    else if(suivs(termeBis_))
    {
        res = h;
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 *  "33"
 * Partie gauche : facteur -> PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE | NOMBRE | appelFct | var | LIRE PARENTHESE_OUVRANTE PARENTHESE_FERMANTE 
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
n_exp * facteur$()
{
    n_var   * varx  = NULL ;
    n_appel * appf = NULL ;
    n_exp   * res  = NULL ;
    int nb;
    if (prems(facteur_))
    {
       // les seuls terminals à comsommer sont PARENTHESE_OUVRANTE, NOMBRE, LIRE, ID_FCT et ID_VAR

       if(comparer_(PARENTHESE_OUVRANTE))
       {
            // si le terminal PARENTHESE_OUVRANTE
            Consommer();

            res = expression$();

            if(comparer_(PARENTHESE_FERMANTE))
                {
                 Consommer();
                }
        }
       else if(comparer_(NOMBRE))
       {
            // si le terminal NOMBRE
            nb = atoi(yytext);
            Consommer();
            res = cree_n_exp_entier(nb);
       }
       else if(comparer_(LIRE))
       {
            // si le terminal LIRE
            Consommer();

            if ( !comparer_(PARENTHESE_OUVRANTE)) erreur_1d_synt(__FUNCTION__,uC);
            Consommer();

            if ( !comparer_(PARENTHESE_FERMANTE)) erreur_1d_synt(__FUNCTION__,uC);
            Consommer();

            res = cree_n_exp_lire();
       }
       else if(comparer_(ID_VAR))
       {
            // si le terminal ID_VAR
            varx = var$();
            res = cree_n_exp_var(varx);
       }
       else if(comparer_(ID_FCT))
       {
            // si le terminal ID_FCT
            appf = appelFct$();
            res = cree_n_exp_appel(appf);
       }
       return res;
    }
    else if(suivs(facteur_)) return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 *  "34"
 * Partie gauche : var -> ID_VAR optIndice
 * Premier : ID_VAR ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
n_var * var$()
{
    n_var *varx= NULL;
    if (prems(var_))
    {
        char *nom = malloc(50*sizeof(char));
       // le seul terminal à comsommer est ID_VAR
       strcpy(nom,yytext);
       Consommer();
       if(!comparer_(CROCHET_OUVRANT))
        {
            varx = cree_n_var_simple(nom);
        }
       else varx = optIndice$(nom);
       return varx;
    }
    else if(suivs(var_))return varx;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return varx;
}


/**
 *  "35"
 * Partie gauche : optIndice -> CROCHET_OUVRANT expression CROCHET_FERMANT | EPSILON
 * Premier : EPSILON ;  CROCHET_OUVRANT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
n_var * optIndice$(char *nom)
{
    n_exp *indice = NULL;
    n_var *var = NULL;
    if (prems(optIndice_))
    {
       // le seul terminal à comsommer est CROCHET_OUVRANT
       Consommer();

       indice = expression$(); // pas de epsilon donc indicé

       if( !comparer_(CROCHET_FERMANT) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();
       var = cree_n_var_indicee(nom,indice);
      //if ( testdico && rechercheExecutable(nom, contexte, T_TABLEAU_ENTIER, 0) == -1 )  erreur_1d_tab_dec(nom, uC);
       return var;
    }
    else if(suivs(optIndice_))return var;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }    
    return var;
}

/**
 *  "36"
 * Partie gauche : appelFct -> ID_FCT PARENTHESE_OUVRANTE listeExpressions PARENTHESE_FERMANTE
 * Premier : ID_FCT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
n_appel * appelFct$()
{
    char *fonction = malloc(50*sizeof(char));
    n_l_exp *args = NULL;
    n_appel *res = NULL;
    if (prems(appelFct_))
    {
       // le seul terminal à comsommer est ID_FCT
       strcpy(fonction,yytext);
       Consommer();

       if( !comparer_(PARENTHESE_OUVRANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       args = listeExpressions$();

       if( !comparer_(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uC);
       Consommer();

       res = cree_n_appel(fonction,args);
       // création de la variable de passage pour compter cb de argument
            n_l_exp * argstmp = args;
            int argsNB = 0;
            // on compte pour chacun
                while (argstmp !=NULL)
                {
                  argsNB++;
                  argstmp = argstmp->queue;
                }
        // fin 
       //if ( testdico && rechercheExecutable(fonction, contexte, T_FONCTION, argsNB) == -1 ) erreur_1d_tab_dec(fonction, uC);
       return res;
    }
    else if(suivs(appelFct_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }   
    return res; 
}

/**
 *  "37"
 * Partie gauche : listeExpressions -> expression listeExpressionsBis | EPSILON
 * Premier : EPSILON ;  ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
n_l_exp * listeExpressions$()
{
    n_exp *tete = NULL;
    n_l_exp *queue = NULL;
    n_l_exp *res = NULL;
    if (prems(listeExpressions_))
    {
       tete = expression$();
       queue = listeExpressionsBis$();
       res = cree_n_l_exp(tete,queue);
       return res;
    }
    else if(suivs(listeExpressions_))return res;
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}

/**
 *  "38"
 * Partie gauche : listeExpressionsBis -> VIRGULE expression listeExpressionsBis | EPSILON
 * Premier : EPSILON ;  VIRGULE ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
n_l_exp * listeExpressionsBis$()
{
    n_exp *tete = NULL;
    n_l_exp *queue = NULL;
    n_l_exp *res = NULL;
    if (prems(listeExpressionsBis_))
    {
       // le seul terminal à comsommer est VIRGULE
       Consommer();

       tete = expression$();
       queue = listeExpressionsBis$(tete);
       res = cree_n_l_exp(tete,queue);
       return res;
    }
    else if(suivs(listeExpressionsBis_)) 
    {
        return res;
    }
    else
    {
        erreur_1d_synt(__FUNCTION__,uC);
    }
    return res;
}
