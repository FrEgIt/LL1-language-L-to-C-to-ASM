"CC = gcc

LIBS = -lm
CCFLAGS = -Wall -ggdb

OBJ = code.o gen_mips.o analyseur_semantique.o analyseur_lexical.o util.o analyseur_syntaxique.o analyseur_abstrait.o syntabs.o premiers.o suivants.o affiche_arbre_abstrait.o dico.o
ELT = zip -r ABDELNABI_X.zip *.h *.c

all: test_yylex

test_yylex: test_yylex.c $(OBJ)
	$(CC) $(CCFLAGS) -o test_yylex test_yylex.c $(OBJ)

analyseur_lexical.o: analyseur_lexical.c analyseur_lexical.h
	$(CC) $(CCFLAGS) -c $^

util.o: util.c util.h
	$(CC) $(CCFLAGS) -c $^

analyseur_syntaxique.o: analyseur_syntaxique.c analyseur_syntaxique.h
	$(CC) $(CCFLAGS) -c $^

premiers.o: premiers.c premiers.h
	$(CC) $(CCFLAGS) -c $^

suivants.o: suivants.c suivants.h
	$(CC) $(CCFLAGS) -c $^

syntabs.o: syntabs.c syntabs.h 
	$(CC) $(CCFLAGS) -c $^

analyseur_abstrait.o: analyseur_abstrait.c analyseur_abstrait.h
	$(CC) $(CCFLAGS) -c $^

affiche_arbre_abstrait.o: affiche_arbre_abstrait.c affiche_arbre_abstrait.h
	$(CC) $(CCFLAGS) -c $^

dico.o: dico.c dico.h
	$(CC) $(CCFLAGS) -c $^

analyseur_semantique.o: analyseur_semantique.c analyseur_semantique.h
	$(CC) $(CCFLAGS) -c $^

gen_mips.o: gen_mips.c gen_mips.h
	$(CC) $(CCFLAGS) -c $^

code.o: code.c code.h
	$(CC) $(CCFLAGS) -c $^

tape:
	tar cfvj ABDELNABI_KACHKOCH.tar.gz *.c *.h Makefile README Grammaire\ LL\(1\)\ perso *.csv

ZIP:
	zip ABDELNABI_KACHKOCH.zip *.c *.h Makefile README Grammaire\ LL\(1\)\ perso *.csv

.PHONY : clean

clean:
	- rm -f $(OBJ) *.h.gch
	- rm -f test_yylex
