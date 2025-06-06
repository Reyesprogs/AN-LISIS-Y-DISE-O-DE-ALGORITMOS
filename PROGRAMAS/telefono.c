#include <stdio.h>
#include <string.h>

char *teclado[] = {
    "", "", "abc", "def",
    "ghi", "jkl", "mno",
    "pqrs", "tuv", "wxyz"
};

void generarCombinaciones(char *digitos, int pos, char *resultado) {
    if (digitos[pos] == '\0') {
        resultado[pos] = '\0'; 
        printf("%s\n", resultado);
        return;
    }

    char *letras = teclado[digitos[pos] - '0'];
    for (int i = 0; letras[i] != '\0'; i++) {
        resultado[pos] = letras[i];
        generarCombinaciones(digitos, pos + 1, resultado);
    }
}

int main() {
    char digitos[5];
    printf("Ingresa digitos del 2 al 9: ");
    scanf("%s", digitos);

    if (strspn(digitos, "23456789") != strlen(digitos)) {
        printf("Entrada invalida.\n");
        return 1;
    }

    char resultado[5];
    generarCombinaciones(digitos, 0, resultado);
    return 0;
}


