#include "symboles.h"
#include "premiers.h"

void initialise_premiers(void){
  int i,j;
  
  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
  {
    for(j=0; j <= NB_TERMINAUX; j++)
    {
        premiers[i][j] = 0;
    }
  }
  premiers[programme_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[programme_][ENTIER] = 1;
  premiers[programme_][ID_FCT] = 1;

  premiers[optDecVariables_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[optDecVariables_][ENTIER] = 1;

  premiers[listeDecVariables_][ENTIER] = 1;

  premiers[listeDecVariablesBis_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[listeDecVariablesBis_][VIRGULE] = 1;

  premiers[declarationVariable_][ENTIER] = 1;

  premiers[optTailleTableau_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[optTailleTableau_][CROCHET_OUVRANT] = 1;

  premiers[listeDecFonctions_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[listeDecFonctions_][ID_FCT] = 1;

  premiers[declarationFonction_][ID_FCT] = 1;
  premiers[declarationFonction_][EPSILON] = 1;//EPSILON terminal effaçable

  premiers[listeParam_][PARENTHESE_OUVRANTE] = 1;

  premiers[optListeDecVariables_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[optListeDecVariables_][ENTIER] = 1;

  premiers[instruction_][POINT_VIRGULE] = 1;
  premiers[instruction_][ID_VAR] = 1;
  premiers[instruction_][ID_FCT] = 1;
  premiers[instruction_][ACCOLADE_OUVRANTE] = 1;
  premiers[instruction_][SI] = 1;
  premiers[instruction_][TANTQUE] = 1;
  premiers[instruction_][RETOUR] = 1;
  premiers[instruction_][ECRIRE] = 1;

  premiers[instructionAffect_][ID_VAR] = 1;

  premiers[instructionBloc_][ACCOLADE_OUVRANTE] = 1;


  premiers[listeInstructions_][POINT_VIRGULE] = 1;
  premiers[listeInstructions_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[listeInstructions_][ID_VAR] = 1;
  premiers[listeInstructions_][ID_FCT] = 1;
  premiers[listeInstructions_][ACCOLADE_OUVRANTE] = 1;
  premiers[listeInstructions_][SI] = 1;
  premiers[listeInstructions_][TANTQUE] = 1;
  premiers[listeInstructions_][RETOUR] = 1;
  premiers[listeInstructions_][ECRIRE] = 1;

  premiers[instructionSi_][SI] = 1;

  premiers[optSinon_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[optSinon_][SINON] = 1;

  premiers[instructionTantque_][TANTQUE] = 1;

  premiers[instructionAppel_][ID_FCT] = 1;

  premiers[instructionRetour_][RETOUR] = 1;

  premiers[instructionEcriture_][ECRIRE] = 1;

  premiers[instructionVide_][POINT_VIRGULE] = 1;

  premiers[expression_][ID_VAR] = 1;
  premiers[expression_][NOMBRE] = 1;
  premiers[expression_][ID_FCT] = 1;
  premiers[expression_][PARENTHESE_OUVRANTE] = 1;
  premiers[expression_][NON] = 1;
  premiers[expression_][LIRE] = 1;


  premiers[expressionBis_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[expressionBis_][OU] = 1;

  premiers[conjonction_][ID_VAR] = 1;
  premiers[conjonction_][NOMBRE] = 1;
  premiers[conjonction_][ID_FCT] = 1;
  premiers[conjonction_][PARENTHESE_OUVRANTE] = 1;
  premiers[conjonction_][NON] = 1;
  premiers[conjonction_][LIRE] = 1;

  premiers[conjonctionBis_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[conjonctionBis_][ET] = 1;

  premiers[negation_][ID_VAR] = 1;
  premiers[negation_][NOMBRE] = 1;
  premiers[negation_][ID_FCT] = 1;
  premiers[negation_][PARENTHESE_OUVRANTE] = 1;
  premiers[negation_][NON] = 1;
  premiers[negation_][LIRE] = 1;

  premiers[comparaison_][ID_VAR] = 1;
  premiers[comparaison_][NOMBRE] = 1;
  premiers[comparaison_][ID_FCT] = 1;
  premiers[comparaison_][PARENTHESE_OUVRANTE] = 1;
  premiers[comparaison_][LIRE] = 1;

  premiers[comparaisonBis_][EPSILON] = 1;
  premiers[comparaisonBis_][EGAL] = 1;
  premiers[comparaisonBis_][INFERIEUR] = 1;
  premiers[comparaisonBis_][SUPERIEUR] = 1;

  premiers[expArith_][ID_VAR] = 1;
  premiers[expArith_][NOMBRE] = 1;
  premiers[expArith_][ID_FCT] = 1;
  premiers[expArith_][PARENTHESE_OUVRANTE] = 1;
  premiers[expArith_][LIRE] = 1;

  premiers[expArithBis_][EPSILON] = 1;
  premiers[expArithBis_][PLUS] = 1;
  premiers[expArithBis_][MOINS] = 1;

  premiers[terme_][ID_VAR] = 1;
  premiers[terme_][NOMBRE] = 1;
  premiers[terme_][ID_FCT] = 1;
  premiers[terme_][PARENTHESE_OUVRANTE] = 1;
  premiers[terme_][LIRE] = 1;

  premiers[termeBis_][EPSILON] = 1;
  premiers[termeBis_][FOIS] = 1;
  premiers[termeBis_][DIVISE] = 1;
  premiers[termeBis_][MODULO] = 1;

  premiers[facteur_][ID_VAR] = 1;
  premiers[facteur_][NOMBRE] = 1;
  premiers[facteur_][ID_FCT] = 1;
  premiers[facteur_][PARENTHESE_OUVRANTE] = 1;
  premiers[facteur_][LIRE] = 1;

  premiers[var_][ID_VAR] = 1;

  premiers[optIndice_][EPSILON] = 1;
  premiers[optIndice_][CROCHET_OUVRANT] = 1;

  premiers[appelFct_][ID_FCT] = 1;

  premiers[listeExpressions_][EPSILON] = 1;
  premiers[listeExpressions_][ID_VAR] = 1;
  premiers[listeExpressions_][NOMBRE] = 1;
  premiers[listeExpressions_][ID_FCT] = 1;
  premiers[listeExpressions_][PARENTHESE_OUVRANTE] = 1;
  premiers[listeExpressions_][NON] = 1;
  premiers[listeExpressions_][LIRE] = 1;
  premiers[listeExpressions_][EPSILON] = 1;//EPSILON terminal effaçable

  premiers[listeExpressionsBis_][EPSILON] = 1;//EPSILON terminal effaçable
  premiers[listeExpressionsBis_][VIRGULE] = 1;
}

int est_premier(int terminal, int non_terminal)
{
  return premiers[non_terminal][terminal];
}
int est_premiers(int terminal, int non_terminal)
{
  return premiers[non_terminal][terminal];
}
int est_pm(int terminal, int non_terminal)
{
  return premiers[non_terminal][terminal];
}

