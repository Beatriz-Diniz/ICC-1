#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char imprime(char **tabuleiro){
    int i,j;
  
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c   |", tabuleiro[i][j]);  //para separar os numeros com espaco seguido de |
        }
        printf("\n----+----+-----");  //para desenhar a linha que sepra as linhas
        printf("\n"); //para pular uma linha toda vez que for começar uma nova coluna
    } 
    return **tabuleiro;
}

/*funcao para verificar se alguem ganhou*/
int verificar(char **tabuleiro, int *i){
    *i = 0;
  
    /*verificar se alguma linha foi preenchida por X ou O*/
    if(tabuleiro[0][0] == tabuleiro [0][1] && tabuleiro[0][1] == tabuleiro[0][2]){
        *i = 1;
        return 1;
    }
    if(tabuleiro[1][0] == tabuleiro [1][1] && tabuleiro[1][1] == tabuleiro[1][2]){
        *i = 1;
        return 1;
    }
    if(tabuleiro[2][0] == tabuleiro [2][1] && tabuleiro[2][1] == tabuleiro[2][2]){
        *i = 1;
        return 1;
    }

    /*verificar se alguma coluna foi preenchida por X ou O*/
    if(tabuleiro[0][0] == tabuleiro [1][0] && tabuleiro[1][0] == tabuleiro[2][0]){
        *i = 1;
        return 1;
    }
    if(tabuleiro[0][1] == tabuleiro [1][1] && tabuleiro[1][1] == tabuleiro[1][2]){
        *i = 1;
        return 1;
    }
    if(tabuleiro[0][2] == tabuleiro [1][2] && tabuleiro[1][2] == tabuleiro[2][2]){
        *i = 1;
        return 1;
    }

    /*verificar se alguma diagonal foi preenchida por X ou O*/
    if(tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2]){
        *i = 1;
        return 1;
    }
    if(tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0]){
        *i = 1;
        return 1;
    }

    /*verificar se deu velha*/
    if(tabuleiro[0][0] != '1' && tabuleiro[0][1] != '2' && tabuleiro[0][2] != '3' && tabuleiro[1][0] != '4' && tabuleiro[1][1] != '5' && tabuleiro[1][2] != '6' && tabuleiro[2][0] != '7' && tabuleiro[2][1] != '8' && tabuleiro[2][2] != '9'){
        *i = 2;
        return 1;
    }

    return 0;
}

/*funcao para preencher a posicao escolhida com X ou O*/
void preencher(char **tabulerio, int *coluna, int *linha, int jogada){
    
    if(jogada==1){ 
        *linha = 1;
        *coluna = 1;
    }
    if(jogada == 2){
        *linha = 1;
        *coluna = 2;
    }
    if(jogada == 3){
        *linha = 1;
        *coluna = 3;
    }
    if(jogada == 4){
        *linha = 2;
        *coluna = 1;
    }
    if(jogada == 5){
        *linha = 2;
        *coluna = 2;
    }
    if(jogada == 6){
        *linha = 2;
        *coluna = 3;
    }   
    if(jogada == 7){
        *linha = 3;
        *coluna = 1;
    }
    if(jogada == 8){
        *linha = 3;
        *coluna = 2;
    }
    if(jogada==9){
        *linha=3;
        *coluna=3;
    }
}

void rodadas(char **tabuleiro){
    int i = 0, linha, coluna, rodada, jogada, n=3;
    imprime(tabuleiro);
    printf("Jogo da velha!\n"); 
    
    for(rodada = 0; rodada <= 8; rodada++){
        do{
            printf("Escolha um número para jogar, jogador X!\n");
            scanf("%d", &jogada);
            preencher(tabuleiro, &coluna, &linha, jogada);
        
            /*verificar se a posicao escolhida ja foi preenchida*/
            if(tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O'){
                while(tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O'){
                    printf("Jogada inválida! Escolha outra casa.\n");
                    scanf("%d", &jogada);
                    preencher(tabuleiro, &coluna, &linha, jogada);
                }    
            }   
        }while(linha < 1 || linha > 3 || coluna < 1 || coluna > 3 ||    tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O');
        
        tabuleiro[linha-1][coluna-1] = 'X';    
        imprime(tabuleiro);
        
        verificar(tabuleiro, &i);
        if(i == 1){
            printf("Fim do jogo! O jogador X venceu!");
            break;
        }

        if(i == 2){
            printf("Deu velha!\n");  
            break;  
        }
        
        do{
            printf("Escolha um número para jogar, jogador O!\n");
            scanf("%d", &jogada);
            preencher(tabuleiro, &coluna, &linha, jogada);
        
            /*verificar se a posicao escolhida ja foi preenchida*/
            if(tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O'){
                while(tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O'){
                    printf("Jogada inválida! Escolha outra casa.\n");
                    scanf("%d", &jogada);
                    preencher(tabuleiro, &coluna, &linha, jogada);
                }   
            }   
        }while(linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tabuleiro[linha-1][coluna-1] == 'X' || tabuleiro[linha-1][coluna-1] == 'O');
    
        tabuleiro[linha-1][coluna-1] = 'O';
        imprime(tabuleiro);
    
        verificar(tabuleiro, &i);
        if(i == 1){
            printf("Fim do jogo! O jogador O venceu!");
            break;
        }
    }
}

int main(){
  
    int i,j,linha,n=3;
    char **tabuleiro;

    tabuleiro=(char**)malloc(n*sizeof(char));
    for(i=0;i<n;i++){
        tabuleiro[i]=(char*)malloc(n*sizeof(char));
    } 

    /*preencher tabuleiro*/
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            tabuleiro[0][0] = '1';
            tabuleiro[0][1] = '2';
            tabuleiro[0][2] = '3';
            tabuleiro[1][0] = '4';
            tabuleiro[1][1] = '5';
            tabuleiro[1][2] = '6';
            tabuleiro[2][0] = '7';
            tabuleiro[2][1] = '8';
            tabuleiro[2][2] = '9';
        }
    }
  
    rodadas(tabuleiro);
    free(tabuleiro);
    return 0;
}