#include <stdio.h>

typedef struct Etats{
	int numeros; //ok
	char trans[5][5];
}Etat; 


typedef struct Automates{
	Etat etats[5];
	int initial; //on prends que son numeros, on peut le retrouver apres dans la liste des etats
	int acceptant[5];//ok

}Automate;