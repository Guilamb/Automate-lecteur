#include <stdio.h>
#include "testFgets.c"
#include "automate.c"

int *traduction(char str[160]);
int transition(int depart, char symbole);//revoir le modèle des transitions 
int listeTransitions[5][5][5];

int main(int argc, char *argv[]){
	gets();
	extern char str[160][160];
	//printf("%s",argv[1] );
	int *tab =  traduction(str[0]);
	
	Automate automate;
	automate.initial = (int)str[1][0] - '0';


	printf("-------------------------------------------------\n");
	//printf("%s\n",str[4] );

	Etat listeEtats[5];
	int j = 0;
	int nbCharacteres = 0;
	int nbVirgule = 0;
	for (int i = 3; i < 8; i++){
		j = 0;
		nbVirgule=0;
		while(str[i][j] != '\0'){
			if (str[i][j] != ';' && str[i][j] != '\n')// le 10 c'est pour des lineFeed qui sont en trop
			{
				listeEtats[i].sorties[j] = (int)str[i][j] - 'a';
				listeTransitions[i-3][nbVirgule][nbCharacteres] = str[i][j];
				nbCharacteres = nbCharacteres+1;
				
			}
			if(str[i][j] == ';'){
				nbVirgule++;
				nbCharacteres = 0;
			}
			j++;//creation de la matrice de proximite
		listeTransitions[i-3][nbVirgule][nbCharacteres] = str[i][j];

	}
	listeTransitions[i-3][nbVirgule][6] = 'c';

}

	//parcours de la matrice de proximite
	int idxLigne = automate.initial;
	int idxInput = 0;
	int idxElement = 0;
	int idxColonne = 0;
	//printf("%d\n",argv[2][2] );

	while(idxLigne < 5){//comment on s'arrete ?
		idxColonne = 0;

		while(idxColonne < 5){
			idxElement = 0;

			while(listeTransitions[idxLigne][idxColonne][idxElement] != ';' || listeTransitions[idxLigne][idxColonne][idxElement] != '\0'){
				//printf("%c\n",listeTransitions[idxLigne][idxColonne][idxElement+1]);
				if(argv[2][idxInput] == listeTransitions[idxLigne][idxColonne][idxElement]){
					printf("%d\n",idxInput );
					if (argv[2][idxInput+1] == 0){ // si le prochain element est le symbole de fin alors le mot a été lu entièrement.
						
						//verifier que l'on est dans un etat acceptant
						printf("Mot reconnu par l'automate\n");
						return 0;
					}

					idxInput++;
					
					idxLigne = idxColonne; //si la lettre est presente alors on va a l'etat correspondant soit idxColonne ici
					//break;

				}else if(listeTransitions[idxLigne][idxColonne][idxElement+1] == 'c'){ //il faut trouver le dernier charcatère de la liste
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


printf("-------------------------------------------------\n");
//printf("%d nb\n", listeTransitions[1][4][6] );

for (int j = 0; j < 5; ++j)
{
	for (int k = 0; k < 5; ++k)
	{
		printf("%d %c\n",j, listeTransitions[0][j][k] );
	}
}
	
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

int transition(int depart, char symbole){
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