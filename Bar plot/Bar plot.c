#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	
	int numeroBarras, i=0, j=0, numerosInseridos, numeros[10000], posicao[200];
  	char barra[200];

	scanf("%d", &numeroBarras);	    //determinar o número de colunas 
	scanf("%d", &numerosInseridos);	//determinar a quantia de dados que serão inseridos
	
	for(i=0; i<numerosInseridos; i++){
		scanf("%d", &numeros[i]);	      //loop para inseriar a quantia de dados desejados 
		for(j=0; j<numeroBarras; j++){	//loop para verificar quais forão os valores inseridos e armazenar em suas respectiva posições
			if(j==numeros[i]){
				posicao[j]++;
			}
		}
	}
  	
	  for(j=0; j<numeroBarras; j++){	
    	barra[posicao[j]]=numeros[i];	  //para atribuir a quantia de repetições de cada número para a variavel barra
    	memset(barra, '#',posicao[j]);	//para substituir o números de repetições por #
    	printf("%d - %s\n",j,barra );
	}
	return 0;
}
