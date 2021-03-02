#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* Struct que descreve o cabecalho do arquivo BMP */
typedef struct cabecalho{  
  char inicial1;
  char inicial2;
  unsigned int tamanho_arquivo;
  unsigned int reservado;
  unsigned int deslocamento;
  unsigned int tamanho_segundo_cabecalho;
  unsigned int largura;
  unsigned int altura;
  unsigned short int palnos;
  unsigned short int bits_pixel;
  unsigned int compressao;
  unsigned int tamanho_imagem;
  unsigned int resolucao_horizontal;
  unsigned int resolucao_vertical;
  unsigned int n_cores_usadas;
  unsigned int cores_importantes;
} cabecalho;
 
/* Struct que para armazenar as cores de um pixel */
typedef struct pixel{
  unsigned char B;
  unsigned char G;
  unsigned char R;
  unsigned char reserva;
} Pixel;
 

void ler_cabecalho(cabecalho *cabecalho, FILE* fp){

  /*encontrar as iniciais*/
  fread(&cabecalho->inicial1, sizeof(char), 1, fp);
  fread(&cabecalho->inicial2, sizeof(char), 1, fp);

  if(cabecalho->inicial1!='B' && cabecalho->inicial2!='M'){
    printf("Arquivo nao eh do formato BMP\n");
    exit(0);
  }
  
  /*encontrar o tamanho do arquivo*/
  fread(&cabecalho->tamanho_arquivo, sizeof(unsigned int), 1, fp);

  /*
  *o valor reservado deve ser sempre 0
  *o valor do deslocamento deve ser sempre 1078
  * o valor do cabecalho deve ser sempre 40
  */
  fread(&cabecalho->reservado, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->deslocamento, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->tamanho_segundo_cabecalho, sizeof(unsigned int), 1, fp);
  
  /*encontrar a largura e altura*/
  fread(&cabecalho->largura, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->altura, sizeof(unsigned int), 1, fp);

  /*
  *o valor do plano deve ser sempre 1
  *o valor de bits por pixel deve ser sempre 8
  * o valor da compressao deve ser sempre 0
  */
  fread(&cabecalho->palnos, sizeof(unsigned short int), 1, fp);
  fread(&cabecalho->bits_pixel, sizeof(unsigned short int), 1, fp);
  fread(&cabecalho->compressao, sizeof(unsigned int), 1, fp);

  /*para encontrar o tamanho da imagem e as resolucoes vertical e horizontal*/
  fread(&cabecalho->tamanho_imagem, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->resolucao_horizontal, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->resolucao_vertical, sizeof(unsigned int), 1, fp);

  /*as cores usadas e importantes devem ser sempre 0*/
  fread(&cabecalho->n_cores_usadas, sizeof(unsigned int), 1, fp);
  fread(&cabecalho->cores_importantes, sizeof(unsigned int), 1, fp);
 
  /*Imprimir o cabeçalho*/
  printf("CABECALHO:\n");
  printf("Iniciais: %c%c\n", cabecalho->inicial1, cabecalho->inicial2);
  printf("Tamanho do arquivo: %u\n", cabecalho->tamanho_arquivo);
  printf("Reservado: %u\n", cabecalho->reservado);
  printf("Deslocamento, em bytes, para o inicio da area de dados: %u\n", cabecalho->deslocamento);
  printf("Tamanho em bytes do segundo cabecalho: %u\n", cabecalho->tamanho_segundo_cabecalho);
  printf("Resolucao: %u x %u\n", cabecalho->largura, cabecalho->altura);
  printf("Numero de planos: %hu\n", cabecalho->palnos);
  printf("Bits por pixel: %d\n", cabecalho->bits_pixel);
  printf("Compressao usada: %u\n", cabecalho->compressao);
  printf("Tamanho imagem: %u\n", cabecalho->tamanho_imagem);
  printf("Resolucao horizontal: %u pixel por metro\n", cabecalho->resolucao_horizontal);
  printf("Resolucao Vertical: %u pixel por metro\n", cabecalho->resolucao_vertical);
  printf("Numero de cores usadas: %u\n", cabecalho->n_cores_usadas);
  printf("Numero de cores importantes: %u\n", cabecalho->cores_importantes);
}

struct pixel *armazenarPixel(FILE *fp){

  /*Armazenar as intensidades de cada cor em cada pixel*/
  struct pixel* pixel = calloc(256, sizeof(struct pixel));
  for(int i=0; i<256; i++){
    fread(&pixel[i].B, sizeof(char), 1, fp);
    fread(&pixel[i].G, sizeof(char), 1, fp);
    fread(&pixel[i].R, sizeof(char), 1, fp);
    fread(&pixel[i].reserva, sizeof(char), 1, fp);
  }

  /*Imprmir a paleta de cores da foto original*/
  printf("PALETA ORIGINAL:\n");
  for(int i=0; i<256; i++){
    printf("Paleta[%d]: R:%d G:%d B:%d\n", i, pixel[i].R , pixel[i].G , pixel[i].B);
  }  

  return pixel;
}
 
int main (){
    
  int filtro,i;
  char nome_arquivo[50];
  long long int *soma_linha;
  FILE *foto_original;
  FILE *foto_modificada;
  cabecalho cabecalho;
  Pixel * pixel_antigo = calloc(256, sizeof(struct pixel));
  Pixel * pixel_novo = calloc(256, sizeof(struct pixel));

  scanf("%s", nome_arquivo);
  /*abrir foto para ser modificada*/
  foto_original = fopen (nome_arquivo, "rb");
  
  /*caso nao seja possivel abrir o arquivo*/
  if (foto_original == NULL){
    printf("Erro no arquivo\n");
    return 0;
  }

  for(i=0; i<strlen(nome_arquivo); i++){
    if(nome_arquivo[i]=='.' && nome_arquivo[i+1]!='b'){
      printf("Arquivo nao eh do formato BMP\n");
      return 0;
    }
  }

  /*escolher o filtro*/
  scanf("%d", &filtro);

  /*chamar a funcao que le o cabecalho*/
  ler_cabecalho(&cabecalho, foto_original);

  /*chamar a funcao que le os pixels*/
  pixel_antigo=armazenarPixel(foto_original);

  switch (filtro){

    /*filtro negativo*/
    case 1:
      /*para criar o arquivo da foto com filtro*/
      for(i=strlen(nome_arquivo); i>0; i--){
        if(nome_arquivo[i]=='.'){
          nome_arquivo[i]='\0';
        }
      }
      strcat(nome_arquivo, "Negativo.bmp");
      foto_modificada=fopen(nome_arquivo, "wb"); 

      /*para aplicar o filtro negativo*/
      printf("PALETA NOVA:\n");
      for(i=0; i<256; i++){
        pixel_novo[i].R=(pixel_antigo[i].R-255)*(-1);
        pixel_novo[i].G=(pixel_antigo[i].G-255)*(-1);
        pixel_novo[i].B=(pixel_antigo[i].B-255)*(-1);
        printf("Paleta[%d]: R:%d G:%d B:%d\n", i, pixel_novo[i].R ,pixel_novo[i].G , pixel_novo[i].B);
      }
      break;

    /*filtro preto e branco*/
    case 2:

      /*para criar o arquivo da foto com o filtro*/
      for(i=strlen(nome_arquivo); i>0; i--){
        if(nome_arquivo[i]=='.'){
          nome_arquivo[i]='\0';
        }
      }
      strcat(nome_arquivo, "PretoBranco.bmp");
      foto_modificada=fopen(nome_arquivo, "wb"); 

      /*para aplicar o filtro preto e branco*/
      printf("PALETA NOVA:\n");
      for(i=0; i<256; i++){
        pixel_novo[i].R=((pixel_antigo[i].R+pixel_antigo[i].G+pixel_antigo[i].B)/3);
        pixel_novo[i].G=((pixel_antigo[i].R+pixel_antigo[i].G+pixel_antigo[i].B)/3);
        pixel_novo[i].B=((pixel_antigo[i].R+pixel_antigo[i].G+pixel_antigo[i].B)/3);
        printf("Paleta[%d]: R:%d G:%d B:%d\n", i, pixel_novo[i].R ,pixel_novo[i].G , pixel_novo[i].B);
      }
      break;
  }
      
  /*para escrever as iniciais do arquivo*/
  fwrite(&cabecalho.inicial1, sizeof(char), 1, foto_modificada);
  fwrite(&cabecalho.inicial2, sizeof(char), 1, foto_modificada);
      
  /*escrever o tamanho do arquivo*/
  fwrite(&cabecalho.tamanho_arquivo, sizeof(unsigned int), 1, foto_modificada);

  /*
  *o valor reservado deve ser sempre 0
  *o valor do deslocamento deve ser sempre 1078
  * o valor do cabecalho deve ser sempre 40
  */
  fwrite(&cabecalho.reservado, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.deslocamento, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.tamanho_segundo_cabecalho, sizeof(unsigned int), 1, foto_modificada);
  
  /*escrever a largura e altura*/
  fwrite(&cabecalho.largura, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.altura, sizeof(unsigned int), 1, foto_modificada);

  /*Para retirar o lixo da imagem caso a largura nao seja multiplo de 4*/
  int espaco_extra=0;
  if((cabecalho.largura%4)!=0){
    while((cabecalho.largura%4)!=0){
      cabecalho.largura=cabecalho.largura+1;
      espaco_extra++;
    }
  } 
  
  /*
  *o valor do plano deve ser sempre 1
  *o valor de bits por pixel deve ser sempre 8
  *o valor da compressao deve ser sempre 0
  */
  fwrite(&cabecalho.palnos, sizeof(unsigned short int), 1, foto_modificada);
  fwrite(&cabecalho.bits_pixel, sizeof(unsigned short int), 1, foto_modificada);
  fwrite(&cabecalho.compressao, sizeof(unsigned int), 1, foto_modificada);

  /*para escrever o tamanho da imagem e as resolucoes vertical e horizontal*/
  fwrite(&cabecalho.tamanho_imagem, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.resolucao_horizontal, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.resolucao_vertical, sizeof(unsigned int), 1, foto_modificada);

  /*as cores usadas e importantes devem ser sempre 0*/
  fwrite(&cabecalho.n_cores_usadas, sizeof(unsigned int), 1, foto_modificada);
  fwrite(&cabecalho.cores_importantes, sizeof(unsigned int), 1, foto_modificada);
      
  /*para escrever as intensidades dos pixels*/
  for(int i=0; i<256; i++){
    fwrite(&pixel_novo[i].B, sizeof(char), 1, foto_modificada);
    fwrite(&pixel_novo[i].G, sizeof(char), 1, foto_modificada);
    fwrite(&pixel_novo[i].R, sizeof(char), 1, foto_modificada);
    fwrite(&pixel_novo[i].reserva, sizeof(char), 1, foto_modificada);
  }

  soma_linha=(long long int*)malloc((cabecalho.altura*cabecalho.largura)*sizeof(long long int));
  /*para escrever a matriz de pixel*/
  unsigned char **matriz_da_imagem = calloc(cabecalho.altura, sizeof(char));
  for(i=0; i<cabecalho.altura; i++){
    matriz_da_imagem[i]=calloc(cabecalho.largura, sizeof(char));
  }

  
  for(i=cabecalho.altura-1; i>=0; i--){
    soma_linha[i]=0;
    for(int j=0; j<cabecalho.largura; j++){
      /*para ler e armazenar a matriz da foto original*/
      fread(&matriz_da_imagem[i][j], sizeof(char), 1, foto_original);
      /*para criar a matriz da nova foto*/
      fwrite(&matriz_da_imagem[i][j], sizeof(char), 1, foto_modificada);
      
      /*para deixar com 0 o espaco extra adicionado, o valor maximo que pode ser adicionado para virar multiplo de 4 eh 3*/
      if(j==cabecalho.largura-espaco_extra && espaco_extra>0){
        matriz_da_imagem[i][j]=0;     
      }
      if(j==cabecalho.largura-espaco_extra+1 && espaco_extra>0){
        matriz_da_imagem[i][j]=0;     
      }
      if(j==cabecalho.largura-espaco_extra+2 && espaco_extra>0){
        matriz_da_imagem[i][j]=0;     
      }
      if(j==cabecalho.largura-espaco_extra+3 && espaco_extra>0){
        matriz_da_imagem[i][j]=0;     
      }

      /*para realizar a soma de todos os elementos de cada linha*/
      soma_linha[i] += (matriz_da_imagem[i][j]);
      //printf("Soma linha %d: %lld\n", i, soma_linha[i]);
    }
  }
  
  /*para imprimir a soma das linhas*/
  for(i=0; i<cabecalho.altura; i++){
    soma_linha[i]=soma_linha[i]-espaco_extra;
    printf("Soma linha %d: %lld\n", i, soma_linha[i]);
  }
  printf("%s\n", nome_arquivo); 
  
  fclose(foto_original);
  free(pixel_novo);
  free(pixel_antigo);
  return 0;
}