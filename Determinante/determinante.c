#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main()
{
	int linha, coluna,determinante,i,j;
	int matriz2[2][2],matriz3[3][3];

	scanf("%d", &linha);
	scanf("%d", &coluna);

	if(linha>3 || coluna>3){	//o programa não irá calcular matrizes de ordem maior que 3
		printf("Entradas invalidas!\n");
	}
	if(linha==1 && coluna==1){	//o determinate de uma matriz quadrada de ordem 1 é o próprio valor da matriz
		scanf("%d",&determinante);
		printf("O determinante da matriz de entrada equivale a %d e tem ordem 1\n", determinante);
	}
	if(linha==2 && coluna==2){	//para receber os valores da matriz quadrada de ordem 2
		for(i=0; i<2; i++){
			for(j=0; j<2; j++){
				scanf("%d", &matriz2[i][j]);
	    	}	
		}
		//para calcular o determinante de uma matriz quadrada de ordem 2	
		determinante=matriz2[0][0]*matriz2[1][1] - (matriz2[0][1]*matriz2[1][0]);	
		printf("O determinante da matriz de entrada equivale a %d e tem ordem 2\n",determinante);
	}
	if(linha==3 && coluna==3){	//para receber os valores da matriz quadrada de ordem 3
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				scanf("%d", &matriz3[i][j]);
	    	}	
		}
		//para calcular o determinante de uma matriz quadrada de ordem 3	
		determinante=matriz3[0][0]*matriz3[1][1]*matriz3[2][2] + matriz3[0][1]*matriz3[1][2]*matriz3[2][0] + matriz3[1][0]*matriz3[2][1]*matriz3[0][2] - (matriz3[0][2]*matriz3[1][1]*matriz3[2][0] + matriz3[1][2]*matriz3[2][1]*matriz3[0][0] + matriz3[0][1]*matriz3[1][0]*matriz3[2][2]);
		printf("O determinante da matriz de entrada equivale a %d e tem ordem 3\n",determinante);

	}
	if(linha<=3 && coluna<=3 && linha!=coluna){	//matrizes não quadradas não possui determinante
		printf("A matriz de entrada nao possui determinante!\n");
	}
}