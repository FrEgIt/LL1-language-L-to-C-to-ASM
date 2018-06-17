#include <stdio.h>
#include "code.h"
#include "dico.h"
#include "gen_mips.h"

extern int scale;
extern int OU_;
extern int ET_;
extern int TQ_;



// PARTIE DECLARATION GLOBALE 

void code_entree_VG()
{
  fprintf(stdout, "\t.data\n");
}

void code_dec_tab_VG(char *nom, int taille)
{
    fprintf(stdout, "%s: .space\t %d\n", nom, 4 * taille);
}

void code_dec_var_VG(char *nom)
{
  fprintf(stdout, "%s: .space\t %d\n", nom, 4 );
}

void code_dec_var_fin_VG()
{
  fprintf(stdout, "\n\t.text\n__start:\n\tjal\tmain\n\tli\t$v0, 10\n\tsyscall\t# stoppe l'execution du processus\n");
}

void code_dec_fct_VG(char *nom)
{
  fprintf(stdout, "%s:\n\tsubiu\t$sp, $sp, 4\t# empile registre (trame de pile)\n\tsw\t$fp, 0($sp)\n\tmove\t$fp, $sp\t# nouvelle valeur de $fp\n\tsubiu\t$sp, $sp, 4\t# empile registre (adresse de retour)\n\tsw\t$ra, 0($sp)\n", nom); // etiquette fonction actuelle créé
}

// PARTIE DECLARATION LOCALE

void code_dec_var_VL(int nb)
{
  	
  	if( nb >0 )
  		fprintf(stdout, "\tsubiu\t$sp, $sp, %d\t# allocation des variables locale\n", 4 * nb);
}

// PARTIE FIN DE FONCTION

void code_fin_fct(variablesNB)
{
	if(variablesNB>0)
		fprintf(stdout, "\taddiu\t$sp, $sp, %d\t# desallocation variables locales\n", 4 * variablesNB);
	fprintf(stdout, "\tlw\t$ra, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$fp, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tjr\t$ra\n");
}

// PARTIE INSTRUCTION RETOUR

void code_inst_retour(int argumts)
{
	int at = 4 *( 1 + argumts );
	fprintf(stdout, "\tlw\t$t0, 0($sp)\t# depile vers registre pour la valeur de retour\n\taddiu\t$sp, $sp, 4\n\tsw\t$t0, %d($fp)\t# ecriture de la valeur de retour\n\tlw\t$ra, 0($sp)\t# depile vers registre\n\taddi\t$sp, $sp, 4\n\tlw\t$fp, 0($sp)\t# depile vers registre\n\taddi\t$sp, $sp, 4\n\tjr\t$ra\n",at);
}

// PARTIE INSTRUCTION SI

void code_inst_si_deb(int nonTEST)
{
	if(nonTEST)
	{
		fprintf(stdout, "\tlw\t$t0, 0($sp)\n\taddiu\t$sp, $sp, 4\n\tbeq\t$t0, $zero, sinon_%d_%d_%d\n", Dico_SI.fonction_si, Dico_SI.imbrication_si, Dico_SI.etage_si);
	}
	else
	{
		fprintf(stdout, "\tlw\t$t0, 0($sp)\n\taddiu\t$sp, $sp, 4\n\tbeq\t$t0, $zero, suite_%d_%d_%d\n", Dico_SI.fonction_si, Dico_SI.imbrication_si, Dico_SI.etage_si);
	}
}
void code_inst_finsi()
{
	fprintf(stdout, "\tj\tsuite_%d_%d_%d\n", Dico_SI.fonction_si,  Dico_SI.imbrication_si, Dico_SI.etage_si);
}

void code_inst_sinon()
{
	fprintf(stdout, "sinon_%d_%d_%d:\n", Dico_SI.fonction_si,  Dico_SI.imbrication_si, Dico_SI.etage_si);
}

void code_inst_si_fin()
{
	fprintf(stdout, "suite_%d_%d_%d:\n", Dico_SI.fonction_si,  Dico_SI.imbrication_si, Dico_SI.etage_si);
}


// PARTIE INSTRUCTION TANT QUE
void code_inst_tq_deb()
{
	fprintf(stdout, "tq_%d_%d_%d:\n",  Dico_TQ.fonction_tq, Dico_TQ.imbrication_tq, Dico_TQ.etage_tq);
}

void code_inst_tq_milieu()
{
	fprintf(stdout, "\tlw\t$t0, 0($sp)\n\taddiu\t$sp, $sp, 4\n\tbeq\t$t0, $zero, fin_%d_%d_%d\n",  Dico_TQ.fonction_tq, Dico_TQ.imbrication_tq, Dico_TQ.etage_tq);
}

void code_inst_tq_fin()
{
	fprintf(stdout, "\tj\ttq_%d_%d_%d\nfin_%d_%d_%d:\n",  Dico_TQ.fonction_tq,  Dico_TQ.imbrication_tq, Dico_TQ.etage_tq,  Dico_TQ.fonction_tq, Dico_TQ.imbrication_tq, Dico_TQ.etage_tq);
}


// PARTIE EXPRESSION 

void code_exp_int(int nombre)
{
	fprintf(stdout, "\tli\t$t0, %d\n\tsubiu\t$sp, $sp, 4\t# empile registre (la valeur nombre)\n\tsw\t$t0, 0($sp)\n", nombre); 
}

void code_exp_lire()
{
	fprintf(stdout, "\tli\t$v0, 5\n\tsyscall\t\t\t# lire\n\tsubiu\t$sp, $sp, 4\n\tsw\t$v0, 0($sp)\n\tli\t$a0, '\\n'\n\tli\t$v0, 11\n\tsyscall\t\t\t# ecrire char\n");
}

void code_exp_ecrire()
{
	fprintf(stdout, "\tlw\t$a0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$v0, 1\n\tsyscall\t\t\t# ecriture\n\tli\t$a0, '\\n'\n\tli\t$v0, 11\n\tsyscall\t\t\t# ecrire char\n");
}

void code_exp_affect_s(int classe, int arg, int adresse)
{
	int at;
	if (classe == C_VARIABLE_LOCALE)
	{
		at = (-1) *(8 + 4 * adresse);
		fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre de la valeur a affecter\n\taddiu\t$sp, $sp, 4\n\tsw\t$t1, %d($fp)\t# stocke le registre dans la variable locale\n", at);
	}
	if ( classe == C_ARGUMENT )
	{
		at = 4 * arg - 4 * adresse; 
		fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre de la valeur a affecter\n\taddiu\t$sp, $sp, 4\n\tsw\t$t1, %d($fp)\t# stocke le registre dans l'argument'\n", at);
	}
	if ( classe == C_VARIABLE_GLOBALE)
	{
		at = adresse;
		fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre de la valeur a affecter\n\taddiu\t$sp, $sp, 4\n\tsw\t$t1, %s\t\t# stocke le registre dans la variable GLOBALE\n", dico.tab[at].identif);
	}
}

void code_exp_affect_t( int adresse)
{
	int at = adresse;
	fprintf(stdout, "\tlw\t$t0, 0($sp)\t# depile vers registre (indice du tableau)\n\taddiu\t$sp, $sp, 4\n\taddu\t$t0, $t0, $t0\n\taddu\t$t0, $t0, $t0\n\tlw\t$t1, 0($sp)\t# depile vers registre de la valeur a affecter\n\taddiu\t$sp, $sp, 4\n\tsw\t$t1, %s($t0)\t# stocke le registre la variable GLOBALE indicer\n", dico.tab[at].identif);
}

void code_exp_s(int classe, int FCTcourante, int adresse)
{
	int at;
	if (classe == C_VARIABLE_LOCALE)
	{
		at = (-1)*(8 + 4 * adresse);
		fprintf(stdout, "\tlw\t$t1, %d($fp)\t# stocke la variable locale dans le registre\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t1, 0($sp)\t# empile la variable local dans le registre\n", at);
	}
	if ( classe == C_ARGUMENT )
	{
		at = 4 * dico.tab[FCTcourante].complement - 4 * adresse;
		fprintf(stdout, "\tlw\t$t1, %d($fp)\t# stocke l'argument dans le registre\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t1, 0($sp)\t# empile l'argument dansle registre\n", at);
	}
	if ( classe == C_VARIABLE_GLOBALE)
	{
		fprintf(stdout, "\tlw\t$t1, %s\t\t# stocke la variable GLOBALE dans le registre\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t1, 0($sp)\t# empile la variable dans le GLOBALE\n", dico.tab[adresse].identif);
	}
}
void code_exp_t( int adresse)
{
	//int at = 4 * adresse;
	fprintf(stdout, "\tlw\t$t0, 0($sp)\t# depile vers registre (indice du tableau)\n\taddiu\t$sp, $sp, 4\n\taddu\t$t0, $t0, $t0\n\taddu\t$t0, $t0, $t0\n\tlw\t$t1, %s($t0)\t# stocke la variable GLOBALE indicer dans le registre\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t1, 0($sp)\t# empile la variable GLOBALE indicer\n", dico.tab[adresse].identif);
}
		// EXPRESSION SOUS PARTIE APPEL FONCTION manque fin d'appel fonction pour la valeur retour
		void code_exp_app_deb(char *nom, int paramNB )
		{
			fprintf(stdout,"\tsubiu\t$sp, $sp, 4\t# allocation valeur de retour pour %s\n", nom);
		}

		void code_exp_app_saut(int paramNB , int retour, int affect, char *nom)
		{
			fprintf(stdout, "\tjal\t%s\n",nom );
			if(paramNB>0) 
				fprintf(stdout, "\taddiu\t$sp, $sp, %d\t# desallocation parametres\n", 4 * paramNB); // je sais pas si je dois écraser retour sinon utlisé ?
			if (!retour)
				{
					if (affect)
					{
						fprintf(stdout, "\tlw $t4, $zero\n\tsw\t$t4, 0($sp)\t# pas valeur de retour mais mis a zero car affecter\n" ); 
					}
					else
					{
						fprintf(stdout, "\taddiu\t$sp, $sp, 4\t# pas valeur de retourner et a affecter DONC desallocation\n" ); 
					}	
				}
		}

// PARTIE OPERATION

void code_op1_ou() // court circuit à ma manière par pile
{
	fprintf(stdout, "\tlw\t$t0, 0($sp)\n\tbne\t$t0, $zero, ou%d\n\taddiu\t$sp, $sp 4\n", OU_); // pas besoin d'empiler le resultat déjà fait sinon dépile
}

void code_op2_ou() // court circuit à ma manière par pile
{
	fprintf(stdout, "ou%d:\n", OU_); // pas besoin d'empiler le resultat déjà fait final création d l'étiquette pour sauter l'op2
    OU_++;
}

void code_op1_et() // court circuit à ma manière par pile
{
	fprintf(stdout, "\tlw\t$t0, 0($sp)\n\tbeq\t$t0, $zero, et%d\n\taddiu\t$sp, $sp 4\n", ET_); // pas besoin d'empiler le resultat déjà fait sinon dépile
}

void code_op2_et() // court circuit à ma manière par pile
{
	fprintf(stdout, "et%d:\n", ET_); // pas besoin d'empiler le resultat déjà fait final création d l'étiquette pour sauter l'op2
    ET_++;
}

void code_op_plus()
{
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\taddu\t$t2, $t0, $t1\t# plus\n\tsubiu\t$sp, $sp, 4\t# empile registre\n\tsw\t$t2, 0($sp)\n");
}

void code_op_moins()
{
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tsubu\t$t2, $t0, $t1\t# moins\n\tsubiu\t$sp, $sp, 4\t# empile registre\n\tsw\t$t2, 0($sp)\n");
}

void code_op_fois()
{
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tmult\t$t0, $t1\n\tmflo\t$t2\t# fois\n\tsubiu\t$sp, $sp, 4\t# empile registre\n\tsw\t$t2, 0($sp)\n");
}

void code_op_divise()
{
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tdiv\t$t0, $t1\n\tmflo\t$t2\t# divise\n\tsubi  $sp, $sp, 4\t# empile registre\n\tsw\t$t2, 0($sp)\n");
}

void code_op_modulo()
{
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t0, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tdiv\t$t0, $t1\n\tmfhi\t$t2\t# modulo\n\tsubi  $sp, $sp, 4\t# empile registre\n\tsw\t$t2, 0($sp)\n");
}

void code_op_egal()
{
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tbeq\t$t1, $t2, e%d\t# egal\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
}

void code_op_diff()
{
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tbne\t$t1, $t2, e%d\t# différent\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
}

void code_op_sup()
{
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tbgt\t$t1, $t2, e%d\t# supérieur\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
}

void code_op_supeg()
{
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tbge\t$t1, $t2, e%d\t# supérieur ou egal\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
}

void code_op_inf()
{ 
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tblt\t$t1, $t2, e%d\t# inférieur\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
}

void code_op_infeg()
{ 
	fprintf(stdout, "\tlw\t$t2, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t\t# enregistre vraie dans $t0\n\tble\t$t1, $t2, e%d\t# inférieur ou egal\n\tli\t$t0, 0\t\t# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\n",
			scale, scale);
    scale++;
  }

void code_op_non()
{ 
	fprintf(stdout, "\tlw\t$t1, 0($sp)\t# depile vers registre\n\taddiu\t$sp, $sp, 4\n\tli\t$t0, -1\t# enregistre vraie dans $t0\n \tbeq\t$t1, $zero, e%d\t# non\n\tli\tstocke la valeur dans la variable GLOBALE$t0, 0\tstocke la valeur dans la variable GLOBALE# enregistre faux dans $t0 sinon\ne%d:\n\tsubiu\t$sp, $sp, 4\n\tsw\t$t0, 0($sp)\t#stocke la valeur dans la variable GLOBALE\n",
			scale, scale);
    scale++;
}  
