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
	int ligneCourante;
	char lettreCourante;

	while(argv[2][idxInput] != 0){
		lettreCourante = argv[2][idxInput];
		
		ligneCourante= idxLigne;
		idxColonne = 0;
		while(idxColonne < 6 ||	idxLigne == ligneCourante){
			idxElement=0;

			while(listeEtats[idxLigne].trans[idxColonne][idxElement] != '\0' || listeEtats[idxLigne].trans[idxColonne][idxElement] != 26 || idxElement<5){
				printf("il fait ça: %c ligne : %d colonne: %d element: %d\n",listeEtats[idxLigne].trans[idxColonne][idxElement], idxLigne, idxColonne, idxElement);
				
				if(listeEtats[idxLigne].trans[idxColonne][idxElement] == lettreCourante){
					idxInput++;
					idxLigne = idxColonne;
					break;
				}

				idxElement++;
			}
			idxColonne++;
		}


	}

	
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