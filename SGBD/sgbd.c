#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fields{   
  char *nome_arquivo;
  char *tipo;
  char *chave;
  char *field_name;
  char *field_type;
  char *aux;

  char *c;
  int *i;
  float *f;
  double *d;
}fields;

typedef struct tamanho_bytes{   
  int codigo;
  int tamanho;
}tamanho_bytes;
/*funcao qsort*/
int comparar_inteiro (const void *a, const void *b) {
    /*retornar 0 quando as palavras forem iguais*/ 
    if((*(struct tamanho_bytes *)a).codigo == (*(struct tamanho_bytes *)b).codigo){
      return 0;
    }
    /*retornar -1 quando a a primeira palvra for menor que a segunda palavra*/
    else if((*(struct tamanho_bytes *)a).codigo < (*(struct tamanho_bytes *)b).codigo){
      return -1;
      /*retornar 1 quando a segunda palavra for maior que a primeira*/
    }else{
      return 1;
    }
}

/*funcao readline que finaliza a leitura quando enconta a ,*/
char *readline(FILE *stream) {
  char *string = NULL;
  int pos = 0;    
  do {
    string = (char *) realloc(string, pos+400);
    string[pos] = (char) fgetc(stdin);
    if(string[pos]=='\n' || string[pos]=='\r' || string[pos]=='"' ){  //para ignorara as quebras de linha
      string[pos]='\0';
      pos--;
    }
    if(string[0]==' '){
      string[0]='\0';
      pos--;
    }
    pos++;
  }while (string[pos-1] != ',' && !feof(stdin));  //crtiterio de parada 
  string[pos-1]='\0'; 
  return string;
}

/*funcao para adicionar cada palavra do arquivo em uma posicao da string palavra*/
void arquivo_para_string(char **palavra, long int  *quantidade_de_linhas, FILE *fp){
  long int i=0;
  while(fgets(palavra[i], 400, fp) != NULL){ 
  i++;
  /*para calcluar a quantia de linhas dentro do arquivo*/
  *quantidade_de_linhas=i;
  }
}

/*para salvar apenas os nomes dos field-name e field-type*/
void nome_extraido(char *nome){
  int tam=strlen(nome);
  char aux[200];
  int i=0, j=0, k=0;
  
  for(i=tam;i>=0;i--){
    
    /*para salvar em uma variavel auxiliar tudo o que estiver antes do espaco*/
    if(nome[i]==' '){
      j=i+1;
      while(j<tam-1){
        strcpy(&aux[k],&nome[j]);
        k++;
        j++;
      }
    }
     
    /*para deletar o \n e o .*/
    if(nome[i]=='\n' || nome[i]=='.'){
      nome[i]='\0';
    }
  }

  /*para salvar na vaiavel inicial aquilo que foi salvo na variavel auxiliar*/
  for(i=0; i<k; i++){
    strcpy(&nome[i], &aux[i]);
  }
}

/*funcao readline para parar a leitura quando encontrar o \n*/
char *ReadLine(FILE *stream) {
  char *string = NULL;
  int pos = 0;    
  do {
    string = (char *) realloc(string, pos+500);
    string[pos] = (char) fgetc(stdin);
    if(string[pos]=='"' ){  //para ignorara as quebras de linha
      string[pos]='\0';
      pos--;
    }
    if(string[0]==' '){
      string[0]='\0';
      pos--;
    }
    pos++;
  }while (string[pos-1] != '\n' && !feof(stdin));
  string[pos-1] = '\0';
  return string;
}

int main() {
  fields *fields = NULL;
  tamanho_bytes *tamanho_bytes = NULL;
  int i, j, k, cont,busca, tam_vetor[20];
  int c=2, aux_c=0,aux_inteiro=0,aux_d=0,aux_f=0,d=1, inteiro=1, f=1;
  int tam_char[20]={'\0'}, tam_int=0, tam_double=0, tam_float=0, tam_total=0;
  int index=0;
  char arquivo[11], **frase, *comando, *aux1;
  long int quantidade_de_linhas=0;
  FILE *fp;
  FILE *novo_arquivo;

  /*escolher o arquivo para abrir*/
  scanf("%s", arquivo);
  fp=fopen(arquivo, "r");

  if(fp==NULL){
    printf("Nao foi possivel abrir o arquivo\n");
    return 0;
  }

  frase=(char**)malloc(400*sizeof(char*));
  for(i=0; i<300; i++){
    frase[i]=(char*)malloc(400*sizeof(char));
  }

  /*armazenar cada frase do arquivo em um vetor da string*/
  arquivo_para_string(frase, &quantidade_de_linhas, fp);

  fields=(struct fields*)malloc((quantidade_de_linhas*1000)*sizeof(struct fields));

  tamanho_bytes = (struct tamanho_bytes*)malloc((quantidade_de_linhas*1000)*sizeof(struct tamanho_bytes));

  /*salvar o nome do arquivo*/
  fields->nome_arquivo=frase[0];
  /*salvar a chave do arquivo*/
  fields->chave=frase[1];
  /*salvar o tipo da chave*/
  fields->tipo=frase[2];
  
  i=0, j=3, cont=0;
  while(j<quantidade_de_linhas){
    /*salvar os nomes das variaveis*/
    fields[i].field_name=frase[j];
    /*salvar os tipos das variaveis*/
    fields[i].field_type=frase[j+1];
    i++;
    j=j+2;
    cont++;
  }
  aux1 = (char*)malloc(200*sizeof(char));
  k=1;
  for(i=0; i<cont; i++){
    aux1=NULL;
    /*verificar se o type eh um char*/
    aux1 = strstr(fields[i].field_type, "char");
    
    /*se o type eh um char retirar os [] e salvar o valor do vetor*/
    if(aux1!=NULL){
      for(j=0; j<strlen(aux1); j++){
        /*salvar o tamanho do vetor*/
        if(aux1[j+1]=='0' || aux1[j+1]=='1' || aux1[j+1]=='2' || aux1[j+1]=='3' || aux1[j+1]=='4' || aux1[j+1]=='5' || aux1[j+1]=='6' || aux1[j+1]=='7' || aux1[j+1]=='8' || aux1[j+1]=='9'){
          if(aux1[j+3]==']'){
            tam_vetor[k] = (aux1[j+1]-48)*10;
          }
          if(aux1[j+2]==']'){
            tam_vetor[k] = (aux1[j+1]-48);
          }
          if(aux1[j+3]!=']' && aux1[j+4]==']' ){
            tam_vetor[k] = (aux1[j+1]-48)*100;
          }
        }
        /*salvar apenas o char*/
        if(aux1[j]=='['){
           aux1[j]='\0';
        }
        strcpy(fields[i].field_type, aux1);
      }
    }

    /*se o type nao for um char, verificar se eh um int*/
    if(aux1==NULL){
      aux1 = strstr(fields[i].field_type, "int");
      /*para retirar o \n*/
      if(aux1!=NULL){
        for(j=0; j<strlen(aux1); j++){
          if(aux1[j]=='\n'){
            aux1[j]='\0';
          } 
        }
        strcpy(fields[i].field_type, aux1);
      }

      /*se o type nao for um int, verificar se eh um double*/
      if(aux1==NULL){
        aux1 = strstr(fields[i].field_type, "double");
        /*para retirar o \n*/
        if(aux1!=NULL){
          for(j=0; j<strlen(aux1); j++){
            if(aux1[j]=='\n'){
              aux1[j]='\0';
            } 
          }
          strcpy(fields[i].field_type, aux1);
        }

        /*se o type nao for um double, verificar se eh um float*/
        if(aux1==NULL){
          aux1 = strstr(fields[i].field_type, "float");
          /*para retirar o \n*/
          if(aux1!=NULL){
            for(j=0; j<strlen(aux1); j++){
              if(aux1[j]=='\n'){
              aux1[j]='\0';
              }  
            }
            strcpy(fields[i].field_type, aux1);
          }      
        }
      }
    }
    /*salvar o tipo do type em uma variavel auxiliar*/
    fields[k].aux=aux1;
    k++;
  }

  /*extrair o nome do arquivo e o codigo*/
  nome_extraido(fields->nome_arquivo);
  nome_extraido(fields->chave);

  i=0;
  /*extrair os nomes das variaveis*/
  while(i<cont){
    nome_extraido(fields[i].field_name);
    i++;
  }

  comando = (char*)malloc(7*sizeof(char));
  
  char virgula;
  int quantia_inserts=0;
  i=0;
  k=1;
  int l=0;
  do{
    scanf("%s", comando);
    /*comando para inserir os dados*/
    if(strcmp(comando, "insert")==0){

      scanf("%d", &tamanho_bytes[i].codigo);
      scanf("%s", &virgula);
      for(j=1; j<cont+1; j++){
        /*para verfificar se a variavel de armazenamento deve ser do tipo char*/
        if(strcmp(fields[j].aux, "char")==0){
          
          if(quantia_inserts==0){
            tam_char[c] = tam_vetor[l+1];
            l++;
          }

          /*para parar a leitura quando encontra a ,*/
          if(j<cont){
            fields[c].c=readline(stdin);
          }
          /*para parar a leitura quando encontra o \n*/
          else{
            fields[c].c=ReadLine(stdin);
          }
          c++;
          /*variavel auxiliar para ser usada no comando search 
          para ajudar a determinar a partir de qual posicao deve ser imprimida*/
          aux_c++;
        }
        /*para verfificar se a variavel de armazenamento deve ser do tipo int*/
        if(strcmp(fields[j].aux,"int")==0){
          if(quantia_inserts==0){
            tam_int+=4;
          }
          fields[inteiro].i=calloc(100, sizeof(int));
          scanf("%d", fields[inteiro].i);
          /*para inserir a virgula que separa os dados*/
          if(j<cont){
            scanf("%s", &virgula);
          }
          inteiro++;
          /*variavel auxiliar para ser usada no comando search 
          para ajudar a determinar a partir de qual posicao deve ser imprimida*/
          aux_inteiro++;
        } 
        
        /*para verfificar se a variavel de armazenamento deve ser do tipo double*/
        if(strcmp(fields[j].aux,"double")==0){
          if(quantia_inserts==0){
            tam_double+=8;
          }

          fields[k].d=calloc(100, sizeof(double));
          scanf("%lf", fields[d].d);
          /*para inserir a virgula que separa os dados*/
          if(j<cont){
            scanf("%s", &virgula);
          }
          d++;
          /*variavel auxiliar para ser usada no comando search 
          para ajudar a determinar a partir de qual posicao deve ser imprimida*/
          aux_d++;
        }
        
        /*para verfificar se a variavel de armazenamento deve ser do tipo float*/
        if(strcmp(fields[j].aux,"float")==0){
          if(quantia_inserts==0){
            tam_float+=4;
          }
          
          fields[k].f=calloc(100, sizeof(float));
          scanf("%f", fields[f].f);
          /*para inserir a virgula que separa os dados*/
          if(j<cont){
            scanf("%s", &virgula);
          }
          f++;
          /*variavel auxiliar para ser usada no comando search 
          para ajudar a determinar a partir de qual posicao deve ser imprimida*/
          aux_f++;
        }         
      }
      i++;
      /*variavel que calcula qunatas vezes o comando foi usado
      e para ser usada no comando search para ajudar 
      a determinar a partir de qual posicao deve ser imprimida*/
      quantia_inserts++;
      k++;
    }
    
    /*comando para realizar a busca dos dados*/
    if(strcmp(comando, "search")==0){
      scanf("%d", &busca);
      j=0;
      k=1;

      /*para encontrar em qual posicao esta armazenado o codigo buscado*/
      for(i=0; i<quantia_inserts; i++){
        if(busca==tamanho_bytes[i].codigo){
          printf("%s: %d\n",fields->chave, tamanho_bytes[i].codigo);

          /*para calcluar a posicao do primeiro dado referente ao codigo pesquisado*/
          c=(2+((aux_c)/quantia_inserts)*i);
          inteiro=(1+((aux_inteiro)/quantia_inserts)*i);
          d=(1+((aux_d)/quantia_inserts)*i);
          f=(1+((aux_f)/quantia_inserts)*i);
          
          /*para impimir os dados pesquisados*/
          while(j<cont){
            printf("%s: ", fields[j].field_name);
            if(strcmp(fields[k].aux, "char")==0){
                printf("%s\n", fields[c].c);
                c++;
            }
            
            if(strcmp(fields[k].aux, "int")==0){
              printf("%d\n", *fields[inteiro].i);
              inteiro++;
            }
            
            if(strcmp(fields[k].aux, "double")==0){
              printf("%.2f\n", *fields[d].d);
              d++;
            }
            if(strcmp(fields[k].aux, "float")==0){
              printf("%.2f\n", *fields[f].f);
              f++;
            }
            j++;
            k++;
            
          }
        printf("\n");
        } 
      }  
    }

    /*comando para criar um arquivo binario com o tamanho dos dados inseridos*/
    if(strcmp(comando, "index")==0){
      if(index==0){
        i=2;
        /*para calcular a quantia de bytes da segunda chave*/
        while(i<l+2){
          tam_total += tam_char[i];
          i++;
        }
        tam_total=tam_total+tam_int+tam_float+tam_double+4;

        j=0;
        /*para clacular a quantia de bytes de cada chave*/
        for(i=0; i<quantia_inserts; i++){
          tamanho_bytes[i].tamanho=tam_total*j;
          j++;
        }
      
        /*para colocar os dados em ordem crescente no arquivo*/
        qsort(tamanho_bytes, quantia_inserts, sizeof(tamanho_bytes), comparar_inteiro);

        /*para criar o arquivo*/
        strcat(fields->nome_arquivo, ".idx");
        novo_arquivo=fopen(fields->nome_arquivo, "w+"); 

        if(novo_arquivo==NULL){
          printf("Nao foi possivel criar o arquivo\n");
        }
      
        /*para escrever os dados no arquivo*/
        for(i=0; i<quantia_inserts; i++){
          fprintf(novo_arquivo, "%d\t", tamanho_bytes[i].codigo);
          fprintf(novo_arquivo, "%d\n", tamanho_bytes[i].tamanho);
        }
        index++;
        fclose(novo_arquivo);
        }else{
          
        }
    }

    /*para avisar se o comando inserido eh invalido*/
    if(strcmp(comando, "index")!=0 && strcmp(comando, "search")!=0 && strcmp(comando, "insert")!=0 && strcmp(comando, "exit")!=0){
      printf("Comando invalido, digite novamente!\n");
    }

  /*para encerrar quando for inserido o comando exit*/
  }while(strcmp(comando, "exit")!=0);

  free(frase);
  free(fields);
  free(tamanho_bytes);
  free(comando);
  fclose(fp);
  return 0;
}