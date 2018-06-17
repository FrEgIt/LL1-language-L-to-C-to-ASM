#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "premiers.h"
#include "suivants.h"
#include "util.h"
#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"

extern FILE *yyin;

int uniteCourante =-1;


/**
 * test le cas si uc appartient à premier de la fonction courante
 * @param  uc uniteCourante dans le fichier *.l à lire créé depuis analyseur_lexical.c dans yylex();
 * @return    le test
 */
int comparer(int uc)
{
    return uc == uniteCourante;
}

/**
 * test le cas si EPSILON appartient à premier de la fonction courante et donc regarde les suivants (premiers.c)
 * test le cas si EPSILON appartient à permier et suivant de la fonction courante et si la c'est la FIN (premiers.c suivants.c symboles.c)
 * @param  fonction fonction courante depuis le fichier symbole.h
 * @return          le test
 */
int suiv(int fonction)
{
    return 
    (
        est_premier(EPSILON,fonction) 
            &&
                (
                    est_suivant(uniteCourante, fonction) 

                        || 

                            (   
                                est_suivant(EPSILON,fonction) && comparer(FIN) 
                            )
                )
    );
}

/**
 * test si l'uniteCourante appartient aux premiers de la fonction avec la fonction est_premier(int terminal, int non_terminal) (premiers.c)
 * @param  fonction fonction fonction courante depuis le fichier symbole.h
 * @return          le test
 */
int prem(int fonction)
{
    return est_premier(uniteCourante,fonction);
}

/**
 * effectue la lecture de la prochaine uniteCourante du fichier *.l
 * uniteCourante : créé depuis analyseur_lexical.c avec yylex();
 */
void Avancer()
{
    uniteCourante = yylex();
}


/**
 * test effectué dans le main pour l'analyseur syntaxique
 */
void test_yysynt_internal()
{
    initialise_premiers();
    initialise_suivants();
    Avancer();
    while(uniteCourante != FIN)
    {
        programme();
    }
    return;
}

/**
 * "1"
 * Partie gauche : Programe -> optDecVariables listeDecFonctions
 * Premier : EPSILON ;  ENTIER ;  ID_FCT ;
 * Suivant : BOTTOM ;
 */
void programme()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(programme_))
    {
       optDecVariables();
       listeDecFonctions();
    }
    else if(suiv(programme_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "2"
 * Partie gauche : optDecVariables -> listeDecVariables POINT_VIRGULE | EPSILON
 * Premier : EPSILON ;  ENTIER ;
 * Suivant : BOTTOM  ; ID_FCT  ; ACCOLADE_OUVRANTE ;
 */
void optDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(optDecVariables_))
    {
       listeDecVariables();

       if( !comparer(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();
    }
    else if(suiv(optDecVariables_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "3"
 * Partie gauche : listeDecVariables -> declarationVariable listeDecVariablesBis
 * Premier : ENTIER ;
 * Suivant : POINT_VIRGULE  ; PARENTHESE_FERMANTE ;
 */
void listeDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeDecVariables_))
    {
       declarationVariable();
       listeDecVariablesBis();
    }
    else if(suiv(listeDecVariables_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "4"
 * Partie gauche : listeDecVariablesBis -> VIRGULE declarationVariable listeDecVariablesBis | EPSILON
 * Premier : EPSILON ;  VIRGULE ;
 * Suivant : POINT_VIRGULE  ; PARENTHESE_FERMANTE ;
 */
void listeDecVariablesBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeDecVariablesBis_))
    {
       if( !comparer(VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","VIRGULE",1);
       Avancer();

       declarationVariable();
       listeDecVariablesBis();
    }
    else if(suiv(listeDecVariablesBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "5"
 * Partie gauche : declarationVariable -> ENTIER ID_VAR optTailleTableau
 * Premier : ENTIER ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; PARENTHESE_FERMANTE ;
 */
void declarationVariable()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(declarationVariable_))
    {
       //un seul terminal = ENTIER
       affiche_element("mot_clef","ENTIER",1);
       Avancer();

       if( !comparer(ID_VAR) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("id_variable",yytext,1);
       Avancer();

       optTailleTableau();
    }
    else if(suiv(declarationVariable_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "6"
 * Partie gauche : optTailleTableau -> CROCHET_OUVRANT NOMBRE CROCHET_FERMANT | EPSILON
 * Premier : EPSILON ;  CROCHET_OUVRANT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; PARENTHESE_FERMANTE ;
 */
void optTailleTableau()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(optTailleTableau_))
    {
       //un seul terminal CROCHET_OUVRANT
       affiche_element("symbole","CROCHET_OUVRANT",1);
       Avancer();

       if( !comparer(NOMBRE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("nombre",yytext,1);
       Avancer();

       if( !comparer(CROCHET_FERMANT) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","CROCHET_FERMANT",1);
       Avancer();
    }
    else if(suiv(optTailleTableau_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "7"
 * Partie gauche : listeDecFonctions -> declarationFonction listeDecFonctions | EPSILON
 * Premier : EPSILON ;  ID_FCT ;
 * Suivant : BOTTOM ;
 */
void listeDecFonctions()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeDecFonctions_))
    {
       declarationFonction();
       listeDecFonctions();
    }
    else if(suiv(listeDecFonctions_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}


/**
 * "8"
 * Partie gauche : declarationFonction -> ID_FCT listeParam optDecVariables instructionBloc
 * Premier : ID_FCT ;
 * Suivant : BOTTOM  ; ID_FCT ;
 */
void declarationFonction()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(declarationFonction_))
    {
       //un seul terminal ID_FCT
       affiche_element("id_fonction",yytext,1);
       Avancer();

       listeParam();
       optDecVariables();
       instructionBloc();
    }
    else if(suiv(declarationFonction_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "9"
 * Partie gauche : listeParam -> PARENTHESE_OUVRANTE optListeDecVariables PARENTHESE_FERMANTE
 * Premier : PARENTHESE_OUVRANTE ;
 * Suivant : ENTIER  ; ACCOLADE_OUVRANTE ;
 */
void listeParam()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeParam_))
    {
       //un seul terminal PARENTHESE_OUVANTE
       affiche_element("symbole","PARENTHESE_OUVANTE",1);
       Avancer();

       optListeDecVariables();

       if ( !comparer(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","PARENTHESE_FERMANTE",1);
       Avancer();
    }
    else if(suiv(listeParam_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}


/**
 * "10"
 * Partie gauche : optListeDecVariables -> listeDecVariables | EPSILON
 * Premier : EPSILON ;  ENTIER ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
void optListeDecVariables()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem( optListeDecVariables_))
    {
       listeDecVariables();
    }
    else if(suiv(optListeDecVariables_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "11"
 * Partie gauche : instruction -> instructionAffect | instructionBloc | instructionSi | instructionTantque | instructionAppel | instructionRetour | instructionEcriture | instructionVide
 * Premier : POINT_VIRGULE ;  ID_VAR ;  ID_FCT ;  ACCOLADE_OUVRANTE ;  SI ;  TANTQUE ;  RETOUR ;  ECRIRE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instruction()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instruction_))
    {
       if(prem(instructionAffect_)) instructionAffect();
       else if(prem(instructionBloc_) ) instructionBloc();
       else if(prem(instructionSi_)) instructionSi();
       else if(prem(instructionTantque_)) instructionTantque();
       else if(prem(instructionAppel_)) instructionAppel();
       else if(prem(instructionRetour_)) instructionRetour();
       else if(prem(instructionEcriture_)) instructionEcriture();
       else if(prem(instructionVide_)) instructionVide();
    }
    else if(suiv(instruction_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "12"
 * Partie gauche : instructionAffect -> var EGAL expression POINT_VIRGULE
 * Premier : ID_VAR ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionAffect()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionAffect_))
    {
       var();

       if( !comparer(EGAL) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","EGAL",1);
       Avancer();

       expression();

       if( !comparer(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();

    }
    else if(suiv(instructionAffect_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "13"
 * Partie gauche : instructionBloc -> ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE
 * Premier : ACCOLADE_OUVRANTE ;
 * Suivant : POINT_VIRGULE  ; BOTTOM  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; SINON  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionBloc()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionBloc_))
    {
    
       // un seul terminal ACCOLADE_OUVRANTE
       affiche_element("symbole","ACCOLADE_OUVRANTE",1);
       Avancer();

       listeInstructions();

       if( !comparer(ACCOLADE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","ACCOLADE_FERMANTE",1);
       Avancer();

    }
    else if(suiv(instructionBloc_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "14"
 * Partie gauche : listeInstructions -> instruction listeInstructions | EPSILON
 * Premier : POINT_VIRGULE ;  EPSILON ;  ID_VAR ;  ID_FCT ;  ACCOLADE_OUVRANTE ;  SI ;  TANTQUE ;  RETOUR ;  ECRIRE ;
 * Suivant : ACCOLADE_FERMANTE ;
 */
void listeInstructions()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeInstructions_))
    {
       instruction();
       listeInstructions();
    }
    else if(suiv(listeInstructions_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "15"
 * Partie gauche : instructionSi -> SI expression ALORS instructionBloc optSinon
 * Premier : SI ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionSi()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionSi_))
    {
    
       // un seul terminal SI
       affiche_element("mot_clef","SI",1);
       Avancer();

       expression();

       if( !comparer(ALORS) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("mot_clef","ALORS",1);
       Avancer();

       instructionBloc();
       optSinon();

    }
    else if(suiv(instructionSi_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "16"
 * Partie gauche : optSinon -> SINON instructionBloc | EPSILON
 * Premier : EPSILON ;  SINON ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void optSinon()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(optSinon_))
    {
    
       // un seul terminal SINON
       affiche_element("mot_clef","SINON",1);
       Avancer();

       instructionBloc();
    }
    else if(suiv(optSinon_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "17"
 * Partie gauche : instructionTantque -> TANTQUE expression FAIRE instructionBloc
 * Premier : TANTQUE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionTantque()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionTantque_))
    {
       // un seul terminal TANTQUE
       affiche_element("mot_clef","TANTQUE",1);
       Avancer();

       expression();

       if( !comparer(FAIRE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("mot_clef","FAIRE",1);
       Avancer();

       instructionBloc();

    }
    else if(suiv(instructionTantque_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "18"
 * Partie gauche : instructionAppel -> appelFct POINT_VIRGULE
 * Premier : ID_FCT ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionAppel()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionAppel_))
    {
       appelFct();

       if( !comparer(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();

    }
    else if(suiv(instructionAppel_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "19"
 * Partie gauche : instructionAppel -> RETOUR expression POINT_VIRGULE
 * Premier : RETOUR ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionRetour()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionRetour_))
    {
       // un seul terminal RETOUR
       affiche_element("mot_clef","RETOUR",1);
       Avancer();

       expression();

       if( !comparer(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();
       
    }
    else if(suiv(instructionRetour_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "20"
 * Partie gauche : instructionEcriture -> ECRIRE PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE POINT_VIRGULE
 * Premier : ECRIRE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionEcriture()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionEcriture_))
    {
       // un seul terminal ECRIRE
       affiche_element("mot_clef","ECRIRE",1);
       Avancer();

       if( !comparer(PARENTHESE_OUVRANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","PARENTHESE_OUVRANTE",1);
       Avancer();

       expression();

       if( !comparer(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","PARENTHESE_FERMANTE",1);
       Avancer();

       if( !comparer(POINT_VIRGULE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();
       
    }
    else if(suiv(instructionEcriture_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "21"
 * Partie gauche : instructionVide -> POINT_VIRGULE
 * Premier : POINT_VIRGULE ;
 * Suivant : POINT_VIRGULE  ; ID_VAR  ; ID_FCT  ; ACCOLADE_OUVRANTE  ; ACCOLADE_FERMANTE  ; SI  ; TANTQUE  ; RETOUR  ; ECRIRE ;
 */
void instructionVide()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(instructionVide_))
    {
       // un seul terminal POINT_VIRGULE
       affiche_element("symbole","POINT_VIRGULE",1);
       Avancer();
       
    }
    else if(suiv(instructionVide_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "22"
 * Partie gauche : expression -> conjonction expressionBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE ;
 */
void expression()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(expression_))
    {
       conjonction();
       expressionBis();
       
    }
    else if(suiv(expression_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "23"
 * Partie gauche : expressionBis -> OU conjonction expressionBis | EPSILON
 * Premier : EPSILON ;  OU ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE ;
 */
void expressionBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(expressionBis_))
    {
       // un seul terminal OU
       affiche_element("symbole","OU",1);
       Avancer();
       
       conjonction();
       expressionBis();

    }
    else if(suiv(expressionBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "24"
 * Partie gauche : conjonction -> negation conjonctionBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU ;
 */
void conjonction()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(conjonction_))
    {
       negation();
       conjonctionBis();

    }
    else if(suiv(conjonction_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "25"
 * Partie gauche : conjonctionBis -> ET negation conjonctionBis | EPSILON
 * Premier : EPSILON ;  ET ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU ;
 */
void conjonctionBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(conjonctionBis_))
    {
       // un seul terminal ET
       affiche_element("symbole","ET",1);
       Avancer();

       negation();
       conjonctionBis();

    }
    else if(suiv(conjonctionBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "26"
 * Partie gauche : negation -> NON comparaison | comparaison
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 */
void negation()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(negation_))
    {
       if(comparer(NON))
       {
            // si le terminal NON
            affiche_element("symbole","NON",1);
            Avancer();
       }

       comparaison();
    }
    else if(suiv(negation_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "27"
 * Partie gauche : comparaison -> expArith comparaisonBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 */
void comparaison()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(comparaison_))
    {
       expArith();
       comparaisonBis();
    }
    else if(suiv(comparaison_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "28"
 * Partie gauche : comparaisonBis -> EGAL expArith comparaisonBis | INFERIEUR expArith comparaisonBis | SUPERIEUR expArith comparaisonBis | EPSILON
 * Premier : EPSILON ;  EGAL ;  INFERIEUR ;  SUPERIEUR ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; ALORS  ; FAIRE  ; OU  ; ET ;
 */
void comparaisonBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(comparaisonBis_))
    {
       // les seuls terminal à comsommer sont  EGAL, SUPERIEUR, INFERIEUR

       if(comparer(EGAL))
       {
            // si le terminal EGAL
            affiche_element("symbole","EGAL",1);
            Avancer();
       }
       else if(comparer(INFERIEUR))
       {
            // si le terminal INFERIEUR
            affiche_element("symbole","INFERIEUR",1);
            Avancer();
       }
       else if(comparer(SUPERIEUR))
       {
            // si le terminal SUPERIEUR
            affiche_element("symbole","SUPERIEUR",1);
            Avancer();
       }

       expArith();
       comparaisonBis();
    }
    else if(suiv(comparaisonBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "29"
 * Partie gauche : expArith -> terme expArithBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR ;
 */
void expArith()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(expArith_))
    {
       terme();
       expArithBis();
    }
    else if(suiv(expArith_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 * "30"
 * Partie gauche : expArithBis -> PLUS terme expArithBis | MOINS terme expArithBis | EPSILON
 * Premier : EPSILON ;  PLUS ;  MOINS ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR ;
 */
void expArithBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(expArithBis_))
    {
       // les seuls terminal à comsommer sont PLUS et MOINS

       if(comparer(PLUS))
       {
            // si le terminal PLUS
            affiche_element("symbole","PLUS",1);
            Avancer();
       }
       else if(comparer(MOINS))
       {
            // si le terminal MOINS
            affiche_element("symbole","MOINS",1);
            Avancer();
       }

       terme();
       expArithBis();
    }
    else if(suiv(expArithBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "31"
 * Partie gauche : terme -> facteur termeBis
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS ;
 */
void terme()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(terme_))
    {
       facteur();
       termeBis();
    }
    else if(suiv(terme_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "32"
 * Partie gauche : termeBis -> FOIS facteur termeBis | DIVISE facteur termeBis | MODULO facteur termeBis | EPSILON
 * Premier : EPSILON ;  FOIS ;  DIVISE ;  MODULO ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS ;
 */
void termeBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(termeBis_))
    {
       // les seuls terminal à comsommer sont FOIS, DIVISE et MODULO

       if(comparer(FOIS))
       {
            // si le terminal FOIS
            affiche_element("symbole","FOIS",1);
            Avancer();
       }
       else if(comparer(DIVISE))
       {
            // si le terminal DIVISE
            affiche_element("symbole","DIVISE",1);
            Avancer();
       }
       else if(comparer(MODULO))
       {
            // si le terminal MODULO
            affiche_element("symbole","MODULO",1);
            Avancer();
       }

       facteur();
       termeBis();
    }
    else if(suiv(termeBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "33"
 * Partie gauche : facteur -> PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE | NOMBRE | appelFct | var | LIRE PARENTHESE_OUVRANTE PARENTHESE_FERMANTE 
 * Premier : ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  LIRE ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
void facteur()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(facteur_))
    {
       // les seuls terminals à comsommer sont PARENTHESE_OUVRANTE, NOMBRE, LIRE, ID_FCT et ID_VAR

       if(comparer(PARENTHESE_OUVRANTE))
       {
            // si le terminal PARENTHESE_OUVRANTE
            affiche_element("symbole","PARENTHESE_OUVRANTE",1);
            Avancer();

            expression();

            if(comparer(PARENTHESE_FERMANTE))
                {
                 affiche_element("symbole","PARENTHESE_FERMANTE",1);
                 Avancer();
                }
        }
       else if(comparer(NOMBRE))
       {
            // si le terminal DIVISE
            affiche_element("nombre",yytext,1);
            Avancer();
       }
       else if(comparer(LIRE))
       {
            // si le terminal LIRE
            affiche_element("mot_clef","LIRE",1);
            Avancer();

            if ( !comparer(PARENTHESE_OUVRANTE)) erreur_1d_synt(__FUNCTION__,uniteCourante);
            affiche_element("symbole","PARENTHESE_OUVRANTE",1);
            Avancer();

            if ( !comparer(PARENTHESE_FERMANTE)) erreur_1d_synt(__FUNCTION__,uniteCourante);
            affiche_element("symbole","PARENTHESE_FERMANTE",1);
            Avancer();
       }
       else if(comparer(ID_VAR))
       {
            // si le terminal ID_VAR
            var();
       }
       else if(comparer(ID_FCT))
       {
            // si le terminal ID_FCT
            appelFct();
       }
    }
    else if(suiv(facteur_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "34"
 * Partie gauche : var -> ID_VAR optIndice
 * Premier : ID_VAR ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
void var()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(var_))
    {
       // le seul terminal à comsommer est ID_VAR
       affiche_element("id_variable",yytext,1);
       Avancer();

       optIndice();
    }
    else if(suiv(var_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "35"
 * Partie gauche : optIndice -> CROCHET_OUVRANT expression CROCHET_FERMANT | EPSILON
 * Premier : EPSILON ;  CROCHET_OUVRANT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
void optIndice()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(optIndice_))
    {
       // le seul terminal à comsommer est CROCHET_OUVRANT
       affiche_element("symbole","CROCHET_OUVRANT",1);
       Avancer();

       expression();

       if( !comparer(CROCHET_FERMANT) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","CROCHET_FERMANT",1);
       Avancer();

    }
    else if(suiv(optIndice_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "36"
 * Partie gauche : appelFct -> ID_FCT PARENTHESE_OUVRANTE listeExpressions PARENTHESE_FERMANTE
 * Premier : ID_FCT ;
 * Suivant : POINT_VIRGULE  ; VIRGULE  ; CROCHET_FERMANT  ; PARENTHESE_FERMANTE  ; EGAL  ; ALORS  ; FAIRE  ; OU  ; ET  ; INFERIEUR  ; SUPERIEUR  ; PLUS  ; MOINS  ; FOIS  ; DIVISE  ; MODULO ;
 */
void appelFct()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(appelFct_))
    {
       // le seul terminal à comsommer est ID_FCT
       affiche_element("id_fonction",yytext,1);
       Avancer();

       if( !comparer(PARENTHESE_OUVRANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","PARENTHESE_OUVRANTE",1);
       Avancer();

       listeExpressions();

       if( !comparer(PARENTHESE_FERMANTE) ) erreur_1d_synt(__FUNCTION__,uniteCourante);
       affiche_element("symbole","PARENTHESE_FERMANTE",1);
       Avancer();

    }
    else if(suiv(appelFct_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "37"
 * Partie gauche : listeExpressions -> expression listeExpressionsBis | EPSILON
 * Premier : EPSILON ;  ID_VAR ;  NOMBRE ;  ID_FCT ;  PARENTHESE_OUVRANTE ;  NON ;  LIRE ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
void listeExpressions()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeExpressions_))
    {
       expression();
       listeExpressionsBis();

    }
    else if(suiv(listeExpressions_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}

/**
 *  "38"
 * Partie gauche : listeExpressionsBis -> VIRGULE expression listeExpressionsBis | EPSILON
 * Premier : EPSILON ;  VIRGULE ;
 * Suivant : PARENTHESE_FERMANTE ;
 */
void listeExpressionsBis()
{
    affiche_balise_ouvrante(__FUNCTION__,1);
    if (prem(listeExpressionsBis_))
    {
       // le seul terminal à comsommer est VIRGULE
       affiche_element("symbole","VIRGULE",1);
       Avancer();

       expression();
       listeExpressionsBis();

    }
    else if(suiv(listeExpressionsBis_));
    else
    {
        erreur_1d_synt(__FUNCTION__,uniteCourante);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return ;
}