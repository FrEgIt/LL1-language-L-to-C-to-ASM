#ifndef __CODE__
#define __CODE__

// PARTIE DECLARATION VARIABLES GLOBALE
void code_entree_VG();

void code_dec_tab_VG(char *nom, int taille);

void code_dec_var_VG(char *nom);

void code_dec_var_fin_VG();

void code_dec_fct_VG(char *nom);


// PARTIE FIN DE FONCTION
void code_fin_fct(int variablesNB);


//PARTIE DECLARATION DE VARIABLE LOCAL
void code_dec_var_VL(int nb);


// PARTIE INSTRUCTION DE L'AFFECTATION DE LA VALEUR RETOUR
void code_inst_retour(int argumts);


// PARTIE INSTRUCTION SI
void code_inst_si_deb(int nonTEST);

void code_inst_finsi();

void code_inst_sinon();

void code_inst_si_fin();


// PARTIE INSTRUCTION TANT QUE
void code_inst_tq_deb();

void code_inst_tq_milieu();

void code_inst_tq_fin();



// PARTIE EXPRESSION
void code_exp_lire();

void code_exp_ecrire();

void code_exp_int(int nombre);

void code_exp_affect_s(int classe, int arg, int adresse);

void code_exp_affect_t(int adresse);

void code_exp_s(int classe, int arg, int adresse);

void code_exp_t( int adresse);


// EXPRESSION APPEL FONCTION

void code_exp_app_deb(char *nom, int paramNB);

void code_exp_app_saut(int paramNB, int retour, int affect, char *nom);



// PARTIE OPERATION 

	void code_op1_ou();

	void code_op2_ou();

	void code_op1_et();

	void code_op2_et();

									void code_op_plus();

									void code_op_moins();

									void code_op_fois();

									void code_op_divise();

									void code_op_modulo();

	void code_op_egal();

	void code_op_diff();

	void code_op_sup();

	void code_op_supeg();

	void code_op_inf();

	void code_op_infeg();

	void code_op_non();


#endif
