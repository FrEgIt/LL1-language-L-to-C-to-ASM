#ifndef __SYMBOLES__
#define __SYMBOLES__

#define ERREUR -1

#define EPSILON 0

/* symboles non terminaux */

#define NB_NON_TERMINAUX 42

#define listeDecVariables_ 1
#define listeDecFonctions_ 2
#define declarationVariable_ 3
#define declarationFonction_ 4
#define listeParam_ 5
#define listeInstructions_ 6
#define instruction_ 8
#define instructionAffect_ 9
#define instructionBloc_ 10
#define instructionSi_ 11
#define instructionTantque_ 12
#define instructionAppel_ 13
#define instructionRetour_ 14
#define instructionEcriture_ 15
#define instructionVide_ 16
#define var_ 17
#define expression_ 18
#define appelFct_ 19
#define conjonction_ 20
#define negation_ 21
#define comparaison_ 22
#define expArith_ 23
#define terme_ 24
#define facteur_ 25
#define argumentsEffectifs_ 26
#define listeExpressions_ 27
#define listeExpressionsBis_ 7
#define programme_ 28
#define conjonctionBis_ 29
#define optTailleTableau_ 30
#define expArithBis_ 31
#define optSinon_ 32
#define comparaisonBis_ 33
#define optDecVariables_ 34
#define optIndice_ 35
#define listeDecVariablesBis_ 36
#define termeBis_ 38
#define expressionBis_ 39
#define instructionFaire_ 40
#define optListeDecVariables_ 41



/* symboles terminaux */
#define NB_TERMINAUX 33

#define POINT_VIRGULE 1
#define PLUS 2
#define MOINS 3
#define FOIS 4
#define DIVISE 5
#define MODULO 6
#define PARENTHESE_OUVRANTE 7
#define PARENTHESE_FERMANTE 8
#define CROCHET_OUVRANT 9
#define CROCHET_FERMANT 10
#define ACCOLADE_OUVRANTE 11
#define ACCOLADE_FERMANTE 12
#define EGAL 13
#define INFERIEUR 14
#define SUPERIEUR 15
#define ET 16
#define OU 17
#define NON 18
#define SI 19
#define ALORS 20
#define SINON 21
#define TANTQUE 22
#define FAIRE 23
#define ENTIER 24
#define RETOUR 25
#define LIRE 26
#define ECRIRE 27
#define ID_VAR 28
#define ID_FCT 29
#define NOMBRE 30
#define FIN 31
#define VIRGULE 32


#endif
