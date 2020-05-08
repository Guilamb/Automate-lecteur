#include <stdio.h>
#include <ctype.h>
int gets();
int estLettre(char str[60],char exception);
int estChiffre(char str[60]);
char str[160][160];//faudra changer le 60
int gets(char fileName[257]){ //taille max des noms de fichiers sous unix
	 
	FILE *fp;
	int nbLigne = 0;

	fp = fopen(fileName , "r");

	/* Verrification de l'ouverture*/
	if (fp == NULL){
		perror("try again");
		return -1;
	}

	while(fgets(str[nbLigne], 160, fp)!=NULL) {
		nbLigne++;	
     	
     if(nbLigne == 1){

     	if(estLettre(str[0],0) == 0){
     		puts(str[0]);
     	}


     }else if(nbLigne == 2){
     	int etatInitial =  (int)*str[1] - '0';
     	if(estChiffre(str[1]) == 0 && etatInitial>=0 && etatInitial<=4 && str[1][1]=='\n'){
     		puts(str[1]);
     	}else{
     		perror("start state error");
     	}

     	

     }else if(nbLigne == 3){
     	int etatInitial =  (int)*str[2] - '0';
     	if(estChiffre(str[2]) == 0 && etatInitial>=0 && etatInitial<=4){
     		puts(str[2]);
     	}else{
     		perror("Accepted state error");
     	}

     }else if(nbLigne>=4 && nbLigne<=9){
     	if (estLettre(str[nbLigne-1],';') == 0 )
     	{
     		puts(str[nbLigne-1]);
     	}
     }else{
     	perror("too many elemnts");
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
			perror("error not a letter");
			return -1;

		}
		j++;
	}
	return 0;
}

int estChiffre(char astr[60]){
	int j = 0;
	while(astr[j] != '\n'){
		if (isdigit(astr[j])==0)
		{	
			perror("error not a number");
			return -1;

		}
		j++;
	}
	return 0;
}