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
				//printf("%c nbC:%d\n",str[i][j],nbCharacteres );
				nbCharacteres = nbCharacteres+1;

				/* le probleme est que j avance quand on a une lettre 
				car sans ca il ne peut lire str, 
				mais du coup les lettres sont alors dans des cases differentes. 
				d'où l'utilisation de nbVirgule.*/

				
			}
			if(str[i][j] == ';'){
				//printf(" virgule:%d val:%c\n", nbVirgule, listeTransitions[i-3][nbVirgule][nbCharacteres] );
				nbVirgule++;
				nbCharacteres = 0;
			}
			j++;//creation de la matrice de proximite
			
	}

	//parcours de la matrice de proximite
	int idxLigne = automate.initial;
	int idxInput,idxElement,idxColonne = 0;
	int transitionExistante = 0;

	while(idxLigne < 5 && transitionExistante == 0){//comment on s'arrete ?
		idxColonne = 0;

		while(idxColonne < 5){
			idxElement = 0;

			while(listeTransitions[idxLigne][idxColonne][idxElement] != ';' || listeTransitions[idxLigne][idxColonne][idxElement] != '\0'){
				if(argv[1][idxInput] == listeTransitions[idxLigne][idxColonne][idxElement]){
					
					idxLigne = idxColonne; //si la lettre est presente alors on va a l'etat correspondant soit idxColonne ici
					
					if (argv[1][idxInput+1] == '\0'){ // si le prochain element est le symbole de fin alors le mot a été lu entièrement.
						
						//verifier que l'on est dans un etat acceptant
						printf("Mot reconnu par l'automate\n");
						return 0;
					}
					break;

				}else{
					idxElement++;
				}

			}
			printf("mot non reconnu par l'automate\n");
			return 0;
		}	
	}
	printf("mot non reconnu par l'automate\n");

}
/*
printf("-------------------------------------------------\n");
printf("%c\n", listeTransitions[1][1][0] );

for (int j = 0; j < 5; ++j)
{
	for (int k = 0; k < 5; ++k)
	{
		printf("%d %c\n",j, listeTransitions[0][j][k] );
	}
}*/
	
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