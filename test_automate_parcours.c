#include <stdio.h>
#include "testFgets.c"
#include "automate.c"

int *traduction(char str[160]);
int transition(int depart, char symbole);//revoir le modèle des transitions car je m'en sert pas... 
int parcoursAutomate(int etatInitial, int listeTransitions[5][5][5], char *argv[]);
int isAcceptant(int numerosEtat);
void testPrintListes();
int listeTransitions[5][5][5];
Etat listeEtats[5];
Automate automate;

int main(int argc, char *argv[]){

	gets(argv[1]);
	extern char str[160][160];
	int *tab =  traduction(str[0]);
	
	automate.initial = (int)str[1][0] - '0'; 
	
	int idxTempon=0;

	while(str[2][idxTempon] != '\0'){
		automate.acceptant[idxTempon]=str[2][idxTempon];
		idxTempon++;
	}
	printf("%c",*automate.acceptant);



	printf("-------------------------------------------------\n");

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
				//listeEtats[i].sorties[j] = (int)str[i][j] - 'a';
				listeTransitions[i-3][nbVirgule][nbCharacteres] = str[i][j];
				listeEtats[i-3].trans[nbVirgule][nbCharacteres] = listeTransitions[i-3][nbVirgule][nbCharacteres];
				
				nbCharacteres = nbCharacteres+1;

			}
			if(str[i][j] == ';'){
				nbVirgule++;
				nbCharacteres = 0;
			}
			j++;	
		listeTransitions[i-3][nbVirgule][nbCharacteres] = str[i][j];

	}
	listeTransitions[i-3][nbVirgule][6] = 26; // on peut se permettre de designer le substitute comme un charactère de fin car il n'est pas accepté lors du parcours de la description d'automate

}
parcoursAutomate(automate.initial, listeTransitions, argv);

printf("-------------------------------------------------\n");

//testPrintListes();

	return 0;
}

int *traduction(char str[160]){
	int i=0;
	static int traduits[160];
	while(str[i] != '\n'){
		traduits[i] = (int) str[i] - 'a';
		i++;
	}
	return traduits;
}

int transition(int depart, char symbole){ //devait etre utilisé dans le while en haut, mais j'ai oublié que je l'avais faite...
	if (depart == -1){
		for(int i = 0;i<5;++i){
		for (int j = 0; j < 5; ++j){
			for (int k = 0; k < 5; ++k){
				if (listeTransitions[i][j][k] == symbole){
					return 0;
				}
			}
		}
	}
		return -1;


	}else if(depart>=0 && depart<=4){
		for (int i = 0; i < 5; ++i){
			for (int k = 0; k < 5; ++k){

			if (listeTransitions[depart][i][k] == symbole){
				return 0;
			}}}
			return -1;

	}else{
		perror("Transition depart error");
		return -1;
	}
}

int parcoursAutomate(int etatInitial, int listeTransitions[5][5][5], char *argv[]){

	//parcours de la matrice de proximite
	int idxLigne = etatInitial;
	int idxInput = 0;
	int idxElement = 0;
	int idxColonne = 0;

	while(idxLigne < 5){
		idxColonne = 0;

		while(idxColonne < 5){
			idxElement = 0;
			
			while(listeTransitions[idxLigne][idxColonne][idxElement] != ';' || listeTransitions[idxLigne][idxColonne][idxElement] != '\0'){
				printf("liste : %d %d %d %c!\n",idxLigne, idxColonne,idxElement, listeTransitions[idxLigne][idxColonne][idxElement]);
				if(argv[2][idxInput] == listeTransitions[idxLigne][idxColonne][idxElement]){

					

					if (argv[2][idxInput+1] == 0 && isAcceptant(idxLigne)){ // si le prochain element est le symbole de fin alors le mot a été lu entièrement.
						
						//verifier que l'on est dans un etat acceptant
						printf("Mot reconnu par l'automate\n");
						return 0;
					}

					idxInput++;
					
					idxLigne = idxColonne; //si la lettre est presente alors on va a l'etat correspondant soit idxColonne ici
					//break; il etait la pour qq chose mais je sais plus pq et si on le met ça marche plus donc ¯\_(ツ)_/¯

				}else if(listeTransitions[idxLigne][idxColonne][idxElement+1] == 26){ 
					printf("%d mot non reconnu par l'automate 1\n",listeTransitions[idxLigne][idxColonne][idxElement+1]);
					return 0;
				}
				else{
					idxElement++;
				}

			}
			printf("mot non reconnu par l'automate 2\n");
			return 0;
		}	
	}
	printf("mot non reconnu par l'automate 3\n");
}

int isAcceptant(int numerosEtat){
	int idxEtat = 0;
	printf("\n nb : %d",numerosEtat);
	while(automate.acceptant[idxEtat] != 0){
		printf("acceptant : %c \n",automate.acceptant[idxEtat]);
		if(automate.acceptant[idxEtat] == numerosEtat){
			
			return 0;
		}
		idxEtat++;
	}
	printf("acceptant ok \n");
	return -1;
}

void testPrintListes(){
	printf("%c nb\n", automate.acceptant[6]);
	/*
	for (int j = 0; j < 5; ++j)
	{
		for (int k = 0; k < 5; ++k)
		{
			printf("%d %c\n",j, listeEtats[0].trans[j][k] );
		}
	}*/
	
}