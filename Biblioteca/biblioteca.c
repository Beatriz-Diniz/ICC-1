#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct livro {
  char lista[1000], alugado[100];
  int dia, dia_alugado, total_de_livros, livros;
};
 
 
/*funcao qsort*/
int compararNome (const void *a, const void *b) {
    return strcmp (((struct livro *)a)->lista,((struct livro *)b)->lista);
}

/*função para inserir os livros*/
void lista(struct livro *liv){  
   
  int i, total;
  int *dia;
  char **nomes;

  scanf("%d", &total);
  
  dia = (int*)malloc(sizeof(int)*total);
  nomes = (char**)malloc(sizeof(char*)*total);
  for(i = 0; i<total; i++){
    nomes[i] = (char*)malloc(sizeof(char)*200);
  }
  
  /*adicionar os livros e o tempo de devolucao*/
  for(i = 0; i<total; i++){
    scanf(" %[^\r\n]s", nomes[i]);
    scanf("%d", &dia[i]);
  }
 
  /*adicionar as informacoes na struct*/
  for (i = 0; i < total; i++) {
    strcpy(liv[i].lista, nomes[i]);
    liv[i].dia = dia[i];
  }
 
  /*colocar em ordem alfabetica*/
  qsort(liv, total, sizeof(struct livro), compararNome);
  liv->total_de_livros = total;
  liv->livros = 0;
}

/*funcao para alugar um livro*/
void operacao1(struct livro *liv){

  int i = 0, j = 0, aux = 0;
  char *nome;
  nome = (char*)calloc(100, sizeof(char)); 

  printf("Digite o livro que voce procura:\n");
  scanf(" %[^\r\n]s",nome);
  
  /*procurar o livro na biblioteca se tiver ate 10 livros alugados*/
  for(i = 0; i<liv->total_de_livros; i++){
    if(strcmp(nome, liv[i].lista)==0){
      j = 1;
      /*se encontrar o livro verificar se ja nao foi alugado*/
      for(int k = 0; k<liv->livros; k++){
        if(strcmp(nome, liv[k].alugado)==0 && liv->livros<10){
          printf("Livro ja alugado\n");
          aux = 1;
        }
      }

      /*se nao tiver sido alugado, adicionarna lista de alugados*/
      if(aux == 0 && liv->livros<10){
        strcpy(liv[liv->livros].alugado, liv[i].lista);
        liv[liv->livros].dia_alugado = liv[i].dia;
        printf("%s alugado com sucesso\n", nome);
        liv->livros++;
        aux = 1;
      }   
    }
  }
 
  if(aux == 0 && liv->livros >=10 && j == 1)
    printf("Voce ja tem 10 livros alugados\n");
  
  if(j == 0)
    printf("Livro nao encontrado na biblioteca\n");

}

/*funcao para imprimir a lista de livros*/
void operacao2(struct livro *liv){

  if(liv->livros == 0)
    printf("Voce nao tem livros alugados\n");
  else{
    printf("Voce tem %d livro(s) alugado(s)\n", liv->livros);
    for(int i = 0; i<liv->livros; i++)
      printf("Livro nome: %s\nDevolve-lo daqui %d dias\n", liv[i].alugado, liv[i].dia_alugado);
  }
    
}

/*função para devolver livros*/
void operacao3(struct livro *liv){ 
  char devolucao[100];
  int i=0,j=0;
  printf("Digite o livro que deseja devolver:\n");
  scanf(" %[^\r\n]s",devolucao);
  
  for(i = 0; i<liv->livros; i++){
    if(strcmp(devolucao, liv[i].alugado)==0){
      j = 1;
      liv->livros--;
      printf("Livro %s foi devolvido com sucesso\n", liv[i].alugado);
      for(int k = i; k<=liv->total_de_livros; k++){
        strcpy(liv[k].alugado, liv[k+1].alugado);
        liv[k].dia_alugado = liv[k+1].dia_alugado;
      }
    }
  }
  if(j == 0){
    printf("Voce nao possui esse livro\n");
  }
}

/*função para finalizar o programa*/
void operacao4(struct livro *liv){  
  printf("Programa finalizado\n");
}

int main(){

  struct livro *liv;
  int tamanho=1000;
  liv = (struct livro *) malloc(sizeof(struct livro)*tamanho);
  int i=0;
  int operacao;
  
  lista(liv);
  scanf(" %d",&operacao); //para chamar o primeiro comando a ser executado 
   while(i == 0){  //para o codigo encerrar apenas quando o comando 4 for chamado
    
    /*para executar o comando 1*/
    if(operacao==1){
      operacao1(liv); 
    }
    
    /*para executar o comando 2*/
    if(operacao==2){
      operacao2(liv); 
    }
    
    /*para executar o comando 3*/
    if(operacao==3){
      operacao3(liv); 
    }
    
    /*para executar o comando 4*/
    if(operacao==4){
      operacao4(liv);
      i = 1;
    }

    scanf(" %d",&operacao); //para chamar um novo comando
  }
  
  free(liv); 
  return 0;
}