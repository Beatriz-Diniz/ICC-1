#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>

struct texto{
  char *texto,*aux, *copia;
  int num;
}texto[200];

int comparar_inteiro (const void *a, const void *b) { //funcao qsort
    int posicao1 = ((struct texto *)a)->num;
    int posicao2 = ((struct texto *)b)->num;
    return (posicao1 - posicao2);
}
 
char *readline(FILE *stream) {
  char *string = NULL;
  int pos = 0;    

  do {
    string = (char *) realloc(string, pos+500);
    string[pos] = (char) fgetc(stdin);
    pos++;
  }while (string[pos-1] != '\n' && !feof(stdin));
  string[pos-1] = '\0';
  
  return string;
}


void operacao1(struct texto *text){ //funcao para colocar em ordem alfabetica
  int i=0, j=0, k=0, l=0;
  long int num[500]={'\0'};
  char aux1[100];

  do{
    text[i].texto=readline(stdin); 
    i++;
  } while (!feof(stdin)); //para a readlineterimanar qaundo a leitura do arquivo chegar no fim
  
  for (j = 1; j < i; j++) { //loop para colocar em ordem alfabetica
    for (l = j+1; l < i; l++) {
      if (strcmp(text[j].texto, text[l].texto)>0) {
        strcpy(aux1, text[j].texto);
        strcpy(text[j].texto, text[l].texto);
        strcpy(text[l].texto, aux1);
      }
    }
  }


  for(j=1; j<i; j++){ //loop para criar um inteiro com os numeros da string
    text[j].aux=text[j].texto;
    while (text[j].aux) {
      if (isdigit(*text[j].aux)) {
        num[j] = strtol(text[j].aux, &text[j].aux, 10); //coloca os inteiros da string num vetor de inteiros
        break;
      } else {
          text[j].aux++;
      }
    }
  }
 
  for(j=1; j<i; j++){ //loop para eliminar o inteiro da string
    l=strlen(text[j].texto);
    text->texto=text[j].texto;
    for(k=l;k>0;k--){
      if(text->texto[k]>='0' && text->texto[k]<='9'){ //criteiro para remover da string
        text->texto[k]='\0';
        if(text->texto[k-1]=='-'){ 
          text->texto[k-1]='\0';
          num[j]=num[j]*-1; //para transformar os inteiros em negativo quando eles aparecerem negativo na string
          text[j].texto=text->texto;
        }
      }
    }
  }

  for(j=1; j<i; j++){   //loop para imprimir o texto em ordem alfebetica
    printf("%ld\t%s\n", num[j], text[j].texto);
  }
}

void operacao2(struct texto text[500]){ //funcao para colocar em ordem alfabetica
  
  int i=0, j=0, k=0, l=0;
  long int num[500]={'\0'};

  do{
    text[i].texto=readline(stdin); 
    i++;
  } while (!feof(stdin)); //para a readlineterimanar qaundo a leitura do arquivo chegar no fim

  for(j=1; j<i; j++){ //loop para criar um inteiro com os numeros da string
    text[j].aux=text[j].texto;
    while (text[j].aux) {
      if (isdigit(*text[j].aux)) {  
        num[j] = strtol(text[j].aux, &text[j].aux, 10); //para pregar os numeros da string e colocar em um vetor de inteiros
        break;
      } else {
          text[j].aux++;
      }
    }
  }
 
  for(j=1; j<i; j++){ //loop para eliminar o inteiro do fim do texto
    l=strlen(text[j].texto); 
    text->texto=text[j].texto;
    for(k=l;k>0;k--){
      if(text->texto[k]>='0' && text->texto[k]<='9'){ //criteiro para eliminar da string
        text->texto[k]='\0';
        if(text->texto[k-1]=='-'){ 
          text->texto[k-1]='\0';
          num[j]=num[j]*-1; //para transformar os inteiros em negativos quando ele aparce negativo na string
          text[j].texto=text->texto;
        }
      }
    }
  }

 for(j=0; j<i; j++){ //para passar os valores do vetor de inteiros para a struct
    text[j].num=num[j];
  }

  qsort(text, i, sizeof(struct texto), comparar_inteiro); //chamar a funcao qsort
  
  for (j = 1; j < i; j++) { //imprimir em ordem numerica 
    if(i>100) {
      if(text[j].num==0){
        for(j=0; j<i-11; j++){
          printf("%d\t%s\n",text[j].num, text[j].texto);
        }
        for(j=i-10; j<i; j++){
          printf("%d\t%s\n",text[j].num, text[j].texto);
        }
      }
    }else{
        printf("%d\t%s\n",text[j].num, text[j].texto);
    }
  }
}

int main() {
  
  char op=getchar();  //para escolher a opcao
  
  struct texto *text; //para usar a struct
  text=(struct texto*)malloc(7000*sizeof(struct texto));

  switch(op){
    
    case '1':
    operacao1(text);  //para chamar a opcao 1 (ordenar em   ordem alfabetica)
          
    case'2':
    operacao2(text);  //para chamar a opcao 2 (ordenar em ordem numerica)
  }
  free(text);
  return 0;
}