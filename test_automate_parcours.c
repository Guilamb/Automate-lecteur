#include <stdio.h>
#include "testFgets.c"
#include "automate.c"

int *traduction(char str[160]);
int parcoursAutomate(int etatInitial, Etat listeEtats[5], char *argv[]);
int isAcceptant(int numerosEtat);
void testPrintListes();
Etat listeEtats[5];
Automate automate;

int main(int argc, char *argv[]){

	if(!gets(argv[1])){
		return 0;
	}
	extern char str[160][160];
	int *tab =  traduction(str[0]);
	
	automate.initial = (int)str[1][0] - '0'; 
	
	int idxTempon=0;

	while(str[2][idxTempon] != '\0'){
		automate.acceptant[idxTempon]=str[2][idxTempon];
		idxTempon++;
	}
	printf("%c",automate.acceptant[0]);



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
parcoursAutomate(automate.initial, listeEtats, argv);

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
		
		lettreTrouve=0;
		idxColonne = 0;
		while(lettreTrouve==0){
			idxElement=0;
			while(listeEtats[idxLigne].trans[idxColonne][idxElement] != '\0' && listeEtats[idxLigne].trans[idxColonne][idxElement] != ';'){
				//printf("il fait ça: %c ligne : %d colonne: %d element: %d\n",listeEtats[idxLigne].trans[idxColonne][idxElement], idxLigne, idxColonne, idxElement);
				
				if(listeEtats[idxLigne].trans[idxColonne][idxElement] == lettreCourante){
					idxInput++;
					idxLigne = idxColonne;
					lettreTrouve=1;
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
	if(isAcceptant(idxLigne)){
		printf("mot reconu par l'automate\n");

	}else{
		printf("mot non reconnu par l'automate\n");	
	}

	
}

int isAcceptant(int numerosEtat){
	int idxEtat = 0;
	printf("\n nb : %d ",numerosEtat);
	while(automate.acceptant[idxEtat] != 0){
		printf("acceptant : %c \n",automate.acceptant[idxEtat]);
		if(automate.acceptant[idxEtat]-'0' == numerosEtat){
			
			return 1;
		}
		idxEtat++;
	}
	return 0	;
}

void testPrintListes(){
	printf("%c nb\n", automate.acceptant[0]);
	
	/*for (int j = 0; j < 5; ++j)
	{
		for (int k = 0; k < 5; ++k)
		{
			printf("%d %c\n",j, listeEtats[0].trans[j][k] );
		}
	}*/
	
}