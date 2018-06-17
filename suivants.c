#include "symboles.h"
#include "suivants.h"

void initialise_suivants(void){
  int i,j;
  
  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      suivants[i][j] = 0;
      
        
  suivants[programme_][EPSILON] = 1;//EPSILON correspond à Bottom fin de fonction possible

  suivants[optDecVariables_][EPSILON] = 1;//EPSILON correspond à Bottom fin de fonction possible
  suivants[optDecVariables_][ID_FCT] = 1;
  suivants[optDecVariables_][ACCOLADE_OUVRANTE] = 1;

  suivants[listeDecVariables_][POINT_VIRGULE] = 1;
  suivants[listeDecVariables_][PARENTHESE_FERMANTE] = 1;

  suivants[listeDecVariablesBis_][POINT_VIRGULE] = 1;
  suivants[listeDecVariablesBis_][PARENTHESE_FERMANTE] = 1;
 
  suivants[declarationVariable_][POINT_VIRGULE] = 1;
  suivants[declarationVariable_][VIRGULE] = 1;
  suivants[declarationVariable_][PARENTHESE_FERMANTE] = 1;

  suivants[optTailleTableau_][POINT_VIRGULE] = 1;
  suivants[optTailleTableau_][VIRGULE] = 1;
  suivants[optTailleTableau_][PARENTHESE_FERMANTE] = 1;


  suivants[listeDecFonctions_][EPSILON] = 1; //EPSILON correspond à Bottom fin de fonction possible

  suivants[declarationFonction_][EPSILON] = 1;//EPSILON correspond à Bottom fin de fonction possible
  suivants[declarationFonction_][ID_FCT] = 1;

  suivants[listeParam_][ENTIER] = 1;
  suivants[listeParam_][ACCOLADE_OUVRANTE] = 1;

  suivants[optListeDecVariables_][PARENTHESE_FERMANTE] = 1;

  suivants[instruction_][POINT_VIRGULE] = 1; 
  suivants[instruction_][ID_VAR] = 1; 
  suivants[instruction_][ID_FCT] = 1;  
  suivants[instruction_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instruction_][ACCOLADE_FERMANTE] = 1; 
  suivants[instruction_][SI] = 1; 
  suivants[instruction_][TANTQUE] = 1; 
  suivants[instruction_][RETOUR] = 1; 
  suivants[instruction_][ECRIRE] = 1; 

  suivants[instructionAffect_][POINT_VIRGULE] = 1; 
  suivants[instructionAffect_][ID_VAR] = 1; 
  suivants[instructionAffect_][ID_FCT] = 1;  
  suivants[instructionAffect_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionAffect_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionAffect_][SI] = 1; 
  suivants[instructionAffect_][TANTQUE] = 1; 
  suivants[instructionAffect_][RETOUR] = 1; 
  suivants[instructionAffect_][ECRIRE] = 1; 

  suivants[instructionBloc_][POINT_VIRGULE] = 1; 
  suivants[instructionBloc_][EPSILON] = 1;//EPSILON correspond à Bottom fin de fonction possible
  suivants[instructionBloc_][ID_VAR] = 1; 
  suivants[instructionBloc_][ID_FCT] = 1;  
  suivants[instructionBloc_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionBloc_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionBloc_][SI] = 1; 
  suivants[instructionBloc_][SINON] = 1; 
  suivants[instructionBloc_][TANTQUE] = 1; 
  suivants[instructionBloc_][RETOUR] = 1; 
  suivants[instructionBloc_][ECRIRE] = 1; 
  
  suivants[listeInstructions_][ACCOLADE_FERMANTE] = 1; 

  suivants[instructionSi_][POINT_VIRGULE] = 1; 
  suivants[instructionSi_][ID_VAR] = 1; 
  suivants[instructionSi_][ID_FCT] = 1;  
  suivants[instructionSi_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionSi_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionSi_][SI] = 1; 
  suivants[instructionSi_][TANTQUE] = 1; 
  suivants[instructionSi_][RETOUR] = 1; 
  suivants[instructionSi_][ECRIRE] = 1; 

  suivants[optSinon_][POINT_VIRGULE] = 1; 
  suivants[optSinon_][ID_VAR] = 1; 
  suivants[optSinon_][ID_FCT] = 1;  
  suivants[optSinon_][ACCOLADE_OUVRANTE] = 1; 
  suivants[optSinon_][ACCOLADE_FERMANTE] = 1; 
  suivants[optSinon_][SI] = 1; 
  suivants[optSinon_][TANTQUE] = 1; 
  suivants[optSinon_][RETOUR] = 1; 
  suivants[optSinon_][ECRIRE] = 1; 

  suivants[instructionTantque_][POINT_VIRGULE] = 1; 
  suivants[instructionTantque_][ID_VAR] = 1; 
  suivants[instructionTantque_][ID_FCT] = 1;  
  suivants[instructionTantque_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionTantque_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionTantque_][SI] = 1; 
  suivants[instructionTantque_][TANTQUE] = 1; 
  suivants[instructionTantque_][RETOUR] = 1; 
  suivants[instructionTantque_][ECRIRE] = 1; 

  suivants[instructionAppel_][POINT_VIRGULE] = 1; 
  suivants[instructionAppel_][ID_VAR] = 1; 
  suivants[instructionAppel_][ID_FCT] = 1;  
  suivants[instructionAppel_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionAppel_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionAppel_][SI] = 1; 
  suivants[instructionAppel_][TANTQUE] = 1; 
  suivants[instructionAppel_][RETOUR] = 1; 
  suivants[instructionAppel_][ECRIRE] = 1; 

  suivants[instructionRetour_][POINT_VIRGULE] = 1; 
  suivants[instructionRetour_][ID_VAR] = 1; 
  suivants[instructionRetour_][ID_FCT] = 1;  
  suivants[instructionRetour_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionRetour_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionRetour_][SI] = 1; 
  suivants[instructionRetour_][TANTQUE] = 1; 
  suivants[instructionRetour_][RETOUR] = 1; 
  suivants[instructionRetour_][ECRIRE] = 1; 

  suivants[instructionEcriture_][POINT_VIRGULE] = 1; 
  suivants[instructionEcriture_][ID_VAR] = 1; 
  suivants[instructionEcriture_][ID_FCT] = 1;  
  suivants[instructionEcriture_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionEcriture_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionEcriture_][SI] = 1; 
  suivants[instructionEcriture_][TANTQUE] = 1; 
  suivants[instructionEcriture_][RETOUR] = 1; 
  suivants[instructionEcriture_][ECRIRE] = 1; 

  suivants[instructionVide_][POINT_VIRGULE] = 1; 
  suivants[instructionVide_][ID_VAR] = 1; 
  suivants[instructionVide_][ID_FCT] = 1;  
  suivants[instructionVide_][ACCOLADE_OUVRANTE] = 1; 
  suivants[instructionVide_][ACCOLADE_FERMANTE] = 1; 
  suivants[instructionVide_][SI] = 1; 
  suivants[instructionVide_][TANTQUE] = 1; 
  suivants[instructionVide_][RETOUR] = 1; 
  suivants[instructionVide_][ECRIRE] = 1; 

  suivants[expression_][POINT_VIRGULE] = 1; 
  suivants[expression_][VIRGULE] = 1; 
  suivants[expression_][CROCHET_FERMANT] = 1; 
  suivants[expression_][PARENTHESE_FERMANTE] = 1; 
  suivants[expression_][ALORS] = 1; 
  suivants[expression_][FAIRE] = 1; 

  suivants[expressionBis_][POINT_VIRGULE] = 1; 
  suivants[expressionBis_][VIRGULE] = 1; 
  suivants[expressionBis_][CROCHET_FERMANT] = 1; 
  suivants[expressionBis_][PARENTHESE_FERMANTE] = 1; 
  suivants[expressionBis_][ALORS] = 1; 
  suivants[expressionBis_][FAIRE] = 1; 

  suivants[conjonction_][POINT_VIRGULE] = 1; 
  suivants[conjonction_][VIRGULE] = 1; 
  suivants[conjonction_][CROCHET_FERMANT] = 1; 
  suivants[conjonction_][PARENTHESE_FERMANTE] = 1; 
  suivants[conjonction_][ALORS] = 1; 
  suivants[conjonction_][FAIRE] = 1;
  suivants[conjonction_][OU] = 1;

  suivants[conjonctionBis_][POINT_VIRGULE] = 1; 
  suivants[conjonctionBis_][VIRGULE] = 1; 
  suivants[conjonctionBis_][CROCHET_FERMANT] = 1; 
  suivants[conjonctionBis_][PARENTHESE_FERMANTE] = 1; 
  suivants[conjonctionBis_][ALORS] = 1; 
  suivants[conjonctionBis_][FAIRE] = 1;
  suivants[conjonctionBis_][OU] = 1;

  suivants[negation_][POINT_VIRGULE] = 1; 
  suivants[negation_][VIRGULE] = 1; 
  suivants[negation_][CROCHET_FERMANT] = 1; 
  suivants[negation_][PARENTHESE_FERMANTE] = 1; 
  suivants[negation_][ALORS] = 1; 
  suivants[negation_][FAIRE] = 1;
  suivants[negation_][OU] = 1;
  suivants[negation_][ET] = 1;

  suivants[comparaison_][POINT_VIRGULE] = 1; 
  suivants[comparaison_][VIRGULE] = 1; 
  suivants[comparaison_][CROCHET_FERMANT] = 1; 
  suivants[comparaison_][PARENTHESE_FERMANTE] = 1; 
  suivants[comparaison_][ALORS] = 1; 
  suivants[comparaison_][FAIRE] = 1;
  suivants[comparaison_][OU] = 1;
  suivants[comparaison_][ET] = 1;

  suivants[comparaisonBis_][POINT_VIRGULE] = 1; 
  suivants[comparaisonBis_][VIRGULE] = 1; 
  suivants[comparaisonBis_][CROCHET_FERMANT] = 1; 
  suivants[comparaisonBis_][PARENTHESE_FERMANTE] = 1; 
  suivants[comparaisonBis_][ALORS] = 1; 
  suivants[comparaisonBis_][FAIRE] = 1;
  suivants[comparaisonBis_][OU] = 1;
  suivants[comparaisonBis_][ET] = 1;

  suivants[expArith_][POINT_VIRGULE] = 1; 
  suivants[expArith_][VIRGULE] = 1; 
  suivants[expArith_][CROCHET_FERMANT] = 1; 
  suivants[expArith_][PARENTHESE_FERMANTE] = 1; 
  suivants[expArith_][EGAL] = 1;
  suivants[expArith_][ALORS] = 1; 
  suivants[expArith_][FAIRE] = 1;
  suivants[expArith_][OU] = 1;
  suivants[expArith_][ET] = 1;
  suivants[expArith_][INFERIEUR] = 1;
  suivants[expArith_][SUPERIEUR] = 1;
  

  suivants[expArithBis_][POINT_VIRGULE] = 1; 
  suivants[expArithBis_][VIRGULE] = 1; 
  suivants[expArithBis_][CROCHET_FERMANT] = 1; 
  suivants[expArithBis_][PARENTHESE_FERMANTE] = 1; 
  suivants[expArithBis_][EGAL] = 1;
  suivants[expArithBis_][ALORS] = 1; 
  suivants[expArithBis_][FAIRE] = 1;
  suivants[expArithBis_][OU] = 1;
  suivants[expArithBis_][ET] = 1;
  suivants[expArithBis_][INFERIEUR] = 1;
  suivants[expArithBis_][SUPERIEUR] = 1;

  suivants[terme_][POINT_VIRGULE] = 1; 
  suivants[terme_][VIRGULE] = 1; 
  suivants[terme_][CROCHET_FERMANT] = 1; 
  suivants[terme_][PARENTHESE_FERMANTE] = 1; 
  suivants[terme_][EGAL] = 1;
  suivants[terme_][ALORS] = 1; 
  suivants[terme_][FAIRE] = 1;
  suivants[terme_][OU] = 1;
  suivants[terme_][ET] = 1;
  suivants[terme_][INFERIEUR] = 1;
  suivants[terme_][SUPERIEUR] = 1;
  suivants[terme_][PLUS] = 1;
  suivants[terme_][MOINS] = 1;
  
  suivants[termeBis_][POINT_VIRGULE] = 1; 
  suivants[termeBis_][VIRGULE] = 1; 
  suivants[termeBis_][CROCHET_FERMANT] = 1; 
  suivants[termeBis_][PARENTHESE_FERMANTE] = 1; 
  suivants[termeBis_][EGAL] = 1;
  suivants[termeBis_][ALORS] = 1; 
  suivants[termeBis_][FAIRE] = 1;
  suivants[termeBis_][OU] = 1;
  suivants[termeBis_][ET] = 1;
  suivants[termeBis_][INFERIEUR] = 1;
  suivants[termeBis_][SUPERIEUR] = 1;
  suivants[termeBis_][PLUS] = 1;
  suivants[termeBis_][MOINS] = 1;
  
  suivants[facteur_][POINT_VIRGULE] = 1; 
  suivants[facteur_][VIRGULE] = 1; 
  suivants[facteur_][CROCHET_FERMANT] = 1; 
  suivants[facteur_][PARENTHESE_FERMANTE] = 1; 
  suivants[facteur_][EGAL] = 1;
  suivants[facteur_][ALORS] = 1; 
  suivants[facteur_][FAIRE] = 1;
  suivants[facteur_][OU] = 1;
  suivants[facteur_][ET] = 1;
  suivants[facteur_][INFERIEUR] = 1;
  suivants[facteur_][SUPERIEUR] = 1;
  suivants[facteur_][PLUS] = 1;
  suivants[facteur_][MOINS] = 1;

  suivants[var_][POINT_VIRGULE] = 1; 
  suivants[var_][VIRGULE] = 1; 
  suivants[var_][CROCHET_FERMANT] = 1; 
  suivants[var_][PARENTHESE_FERMANTE] = 1; 
  suivants[var_][EGAL] = 1;
  suivants[var_][ALORS] = 1; 
  suivants[var_][FAIRE] = 1;
  suivants[var_][OU] = 1;
  suivants[var_][ET] = 1;
  suivants[var_][INFERIEUR] = 1;
  suivants[var_][SUPERIEUR] = 1;
  suivants[var_][PLUS] = 1;
  suivants[var_][MOINS] = 1;
  suivants[var_][FOIS] = 1;
  suivants[var_][DIVISE] = 1;
  suivants[var_][MODULO] = 1;

  suivants[optIndice_][POINT_VIRGULE] = 1; 
  suivants[optIndice_][VIRGULE] = 1; 
  suivants[optIndice_][CROCHET_FERMANT] = 1; 
  suivants[optIndice_][PARENTHESE_FERMANTE] = 1; 
  suivants[optIndice_][EGAL] = 1;
  suivants[optIndice_][ALORS] = 1; 
  suivants[optIndice_][FAIRE] = 1;
  suivants[optIndice_][OU] = 1;
  suivants[optIndice_][ET] = 1;
  suivants[optIndice_][INFERIEUR] = 1;
  suivants[optIndice_][SUPERIEUR] = 1;
  suivants[optIndice_][PLUS] = 1;
  suivants[optIndice_][MOINS] = 1;
  suivants[optIndice_][FOIS] = 1;
  suivants[optIndice_][DIVISE] = 1;
  suivants[optIndice_][MODULO] = 1;

  suivants[appelFct_][POINT_VIRGULE] = 1; 
  suivants[appelFct_][VIRGULE] = 1; 
  suivants[appelFct_][CROCHET_FERMANT] = 1; 
  suivants[appelFct_][PARENTHESE_FERMANTE] = 1; 
  suivants[appelFct_][EGAL] = 1;
  suivants[appelFct_][ALORS] = 1; 
  suivants[appelFct_][FAIRE] = 1;
  suivants[appelFct_][OU] = 1;
  suivants[appelFct_][ET] = 1;
  suivants[appelFct_][INFERIEUR] = 1;
  suivants[appelFct_][SUPERIEUR] = 1;
  suivants[appelFct_][PLUS] = 1;
  suivants[appelFct_][MOINS] = 1;
  suivants[appelFct_][FOIS] = 1;
  suivants[appelFct_][DIVISE] = 1;
  suivants[appelFct_][MODULO] = 1;

  suivants[listeExpressions_][PARENTHESE_FERMANTE] = 1; 

  suivants[listeExpressionsBis_][PARENTHESE_FERMANTE] = 1; 

}

int est_suivant(int terminal, int non_terminal)
{
  return suivants[non_terminal][terminal];
}

int est_suivants(int terminal, int non_terminal)
{
  return suivants[non_terminal][terminal];
}
int est_sv(int terminal, int non_terminal)
{
  return suivants[non_terminal][terminal];
}
