//Made by Guilhane Bourgoin et Lucas Hottin 
#include <stdio.h>
#include "Lecture.c"
#include "datastructures.c"


int parcoursAutomate(int etatInitial, Etat listeEtats[5], char *argv[]);
int isAcceptant(int numerosEtat);
void testPrintListes();

Etat listeEtats[5];
Automate automate;

int main(int argc, char *argv[]){

	if(gets(argv[1])){ //si l'axquisition du file.txt echoue, on met fin au programme
		return 0;
	}

	extern char str[160][160];
	automate.initial = (int)str[1][0] - '0'; 
	int idxTempon=0;

	//on remplie la liste des etats acceptants
	while(str[2][idxTempon] != '\0'){ 
		automate.acceptant[idxTempon]=str[2][idxTempon];
		idxTempon++;
	}



	//creation de la matrice de proximite
	int j = 0;
	int nbCharacteres = 0;
	int nbVirgule = 0;

	for (int i = 3; i < 8; i++){
		j = 0;
		nbVirgule=0;
		listeEtats[i-3].numeros = i-3;
		
		while(str[i][j] != '\0'){
			if (str[i][j] != ';' && str[i][j] != '\n')// le 10 c'est pour des lineFeed qui sont en trop
			{

				listeEtats[i-3].trans[nbVirgule][nbCharacteres] = str[i][j];
				nbCharacteres = nbCharacteres+1;

			}
			else if(str[i][j] == ';'){
				nbVirgule++;
				nbCharacteres = 0;
			}
			j++;	
		listeEtats[i-3].trans[nbVirgule][nbCharacteres] = str[i][j];

	}
	listeEtats[i-3].trans[nbVirgule][6] = 26; // on peut se permettre de designer le substitute comme un charactère de fin car il n'est pas accepté lors du parcours de la description d'automate

}

//on appele la fonction de parcours de l'automate pour savoir si le mot est reconnu par l'automate
parcoursAutomate(automate.initial, listeEtats, argv); 
return 0;
}



int parcoursAutomate(int etatInitial, Etat listeEtats[5], char *argv[]){

	//parcours de la matrice de proximite
	int idxLigne = etatInitial;
	int idxInput = 0;
	int idxElement = 0;
	int idxColonne = 0;
	int lettreTrouve;
	char lettreCourante;

	while(argv[2][idxInput] != 0){
		lettreCourante = argv[2][idxInput];
		lettreTrouve = 0;
		idxColonne = 0;

		while(lettreTrouve==0){
			idxElement=0;

			while(listeEtats[idxLigne].trans[idxColonne][idxElement] != '\0' && listeEtats[idxLigne].trans[idxColonne][idxElement] != ';'){				
				if(listeEtats[idxLigne].trans[idxColonne][idxElement] == lettreCourante){
					idxInput++;
					idxLigne = idxColonne;
					lettreTrouve = 1;
					break;
				}
				idxElement++;
			}
			idxColonne++;


			if(idxColonne==5){
				printf("mot non reconnu par l'automate\n");					
				return 0;
			}
		}
	
	}

	if(isAcceptant(idxLigne)){ //l'index de ligne correspond au numero de l'etat en cours de parcours
		printf("mot reconu par l'automate\n");

	}else{
		printf("mot non reconnu par l'automate\n");	
	}

	
}

//Fonction qui verifie si un etat est acceptant
int isAcceptant(int numerosEtat){
	int idxEtat = 0;
	while(automate.acceptant[idxEtat] != 0){
		if(automate.acceptant[idxEtat]-'0' == numerosEtat){
			
			return 1;
		}
		idxEtat++;
	}
	return 0	;
}
