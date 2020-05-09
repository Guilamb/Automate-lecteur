#include <stdio.h>
#include <ctype.h>
int gets();
int estLettre(char str[60],char exception);
int estChiffre(char astr[60],char exception);
char str[160][160];//faudra changer le 60
int nbLigne = 0;
int gets(char fileName[257]){ //taille max des noms de fichiers sous unix
	 
	FILE *fp;
	

	fp = fopen(fileName , "r");

	/* Verrification de l'ouverture*/
	if (fp == NULL){
		perror("try again");
		return 0;
	}

	while(fgets(str[nbLigne], 160, fp)!=NULL) {
		nbLigne++;	
     	
     if(nbLigne == 1){

     	if(estLettre(str[0],0)){
     		puts(str[0]);
     	}


     }else if(nbLigne == 2){
     	int etatInitial =  (int)*str[1] - '0';
     	if(estChiffre(str[1],0) && etatInitial>=0 && etatInitial<=4 && str[1][1]=='\n'){
     		puts(str[1]);
     	}else{
     		printf("start state error ligne %d\n",nbLigne);
			return 0;
     	}

     	

     }else if(nbLigne == 3){
     	int etatInitial =  (int)*str[2] - '0';
     	if(estChiffre(str[2],';')  && etatInitial>=0 && etatInitial<=4){
     		puts(str[2]);
     	}else{
     		printf("Accepted state error ligne %d\n",nbLigne);
			return 0;
     	}

     }else if(nbLigne>=4 && nbLigne<=9){
     	if (estLettre(str[nbLigne-1],';') )
     	{
     		puts(str[nbLigne-1]);
     	}
     }else{
     	printf("too many elemnts ligne %d\n",nbLigne);
		return 0;
     }
   }

	fclose(fp);
	return 0;
}


int estLettre(char astr[60],char exception){
	int j = 0;
	while(astr[j] != '\n'){
		
		if (isalpha(astr[j])==0 && astr[j] != exception)
		{	
			printf("error not a letter ligne %d\n",nbLigne);
			return 0;

		}
		j++;
	}
	return 1;
}

int estChiffre(char astr[60],char exception){
	int j = 0;
	while(astr[j] != '\n'){
		if (isdigit(astr[j])==0 && astr[j] != exception)
		{	
			printf("error not a number ligne %d\n",nbLigne);
			return 0;

		}
		j++;
	}
	return 1;
}