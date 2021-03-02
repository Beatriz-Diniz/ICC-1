#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
    char bin[100];
    unsigned long dec = 0;
    int i = 0;
    int s;
    
    /*armazenar o numero binario em uma string*/
    fgets(bin, sizeof(bin), stdin);
    
    /*encontrar o tamanho do numero binario*/
    s = strlen(bin);
    
    while(s--) {
        if(bin[s] == '0' || bin[s] == '1' ) {
            dec = dec + pow(2, i++) * (bin[s] - '0');
        }
    }
    
    printf("%lu\n", dec);
    return 0;
}
