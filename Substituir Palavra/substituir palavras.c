#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*palavra1 é a string que vai receber a palavra que deve ser substituida 
  palavra2 é a string que vai receber a palavra que vai substituir a palavra anterior*/
char *substituir_palavras(char *texto,char *palavra1, char *palavra2){
  char *texto_novo= (char*)malloc(100*sizeof(char)); 
  int i;

  while (*texto!='\0'){ 
    if (strstr(texto, palavra1) == texto){ //para comparar se o a palavra está contida no texto
      strcpy(&texto_novo[i], palavra2);    //para copiar a palavra nova para o texto
      i += strlen(palavra2);               //para adicionar aumentar o espaço ocupado pela palavra nova caso ela seja maior que a anterior
      texto += strlen(palavra1);           //para adicionar ao texto o espaço ocupado pela palavra antiga
    }
    texto_novo[i++] = *texto++;
  }
  return texto_novo;  
}
 
int main(){

  char *texto=(char*)malloc(100*sizeof(char));    
  char *palavra1=(char*)malloc(sizeof(char)); 
  char *palavra2=(char*)malloc(sizeof(char));  
  char *novo_texto=(char*)malloc(100*sizeof(char));;
    
  scanf("%s",palavra1);     //para inserir a palavra que deve ser trocada 
  scanf("%s",palavra2);     //para inseria a palavra que vai substituir a palavra anterior
  scanf(" %[^\n]s",texto);  //para inserir o texto que sofrerá as modificações
  
  novo_texto = substituir_palavras(texto, palavra1,palavra2); //para chamar a função e realizar a troca de palavras
  printf("%s\n", novo_texto); //para imprimir o texto modificado

  return 0; 
  free(texto);    
  free(palavra1); 
  free(palavra2);  
  free(novo_texto);
}