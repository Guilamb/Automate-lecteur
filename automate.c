#include <stdio.h>

typedef struct Etats{
	int numero;
	int entrees[5];
	int sorties[5];

}Etat; 


typedef struct Automates{
	Etat etats[5];
	int initial; //on prends que son numeros, on peut le retrouver apres dans la liste des etats
	int transitions[5][5][5];

}Automate;