#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>  

int main(void) {

    int i, key;
    char palavra[1000] = { '\0' };
    char crip[1000] = { '\0' };
    char crip2[1000] = { '\0' };
    char c;
    c = getchar();


    scanf("%d ", &key); //determinar numero da chave para encriptar ou desencriptar
    scanf("%[^\n]%*c", palavra); //escrever palavra para encriptar ou desencriptar


    switch (c) {
    case '1': //para encriptar
        while (palavra[i] >= 0 && palavra[i] != '\0') {
            if (palavra[i] >= 65 && palavra[i] <= 90) { //para letras maiusculas
                crip[i] = palavra[i] + key;
            }
            if (palavra[i] >= 97 && palavra[i] <= 122) { //para letras minusculas
                crip[i] = palavra[i] + key;
            }
            if (palavra[i] >= 32 && palavra[i] <= 64) { //para caracteres especiais ficarem inalterados
                crip[i] = palavra[i];
            }
            i++;
        }
        printf("%s\n", crip);
        break;
        return 0;

    case '2': //para desencriptar
        while (palavra[i] >= 0 && palavra[i] != '\0') {

            if (palavra[i] >= 97) { //para letras minusculas
                crip[i] = palavra[i] - key;
                if (crip[i] >= 97) {
                    crip2[i] = crip[i];
                }
                if (crip[i] < 97) {
                    crip2[i] = crip[i] + 26;
                }
            }
            if (palavra[i] <= 90) { //para letras maiusculas
                crip[i] = palavra[i] - key;
                if (crip[i] >= 65 && crip[i] <= 90) {
                    crip2[i] = crip[i];
                }
                if (crip[i] < 65) {
                    crip2[i] = crip[i] + 26;
                }
            }
            if (palavra[i] >= 32 && palavra[i] <= 64) { //manter caracteres especiais inalterados
                crip[i] = palavra[i];
                crip2[i] = crip[i];
            }
            if (palavra[i] >= 123 && palavra[i] <= 127) {  //manter caracteres especiais inalterados
                crip[i] = palavra[i];
                crip2[i] = crip[i];
            }
            i++;
        }
        printf("%s\n", crip2);
        break;
    }return 0;
}
