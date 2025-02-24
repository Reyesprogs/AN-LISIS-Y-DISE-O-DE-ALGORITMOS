//AUTOR: REYES CABALLERO JESUS EMMANUEL

#include <stdio.h>
#include <stdlib.h>

int proceso(int num) {
    int original = num;
    int invertido = 0;
    int numoperaciones = 0; 

    while (num > 0) {
        int ultdig;

        ultdig = num % 10;
        invertido = invertido * 10 + ultdig;
        num = num / 10;

        numoperaciones++; 
    }

    printf("Se realizaron %d operaciones para determinar si es un palindromo\n", numoperaciones);

    return original == invertido;
}

int main() {
    int num;
    printf("Ingresar el numero:");
    scanf("%d", &num);

    if (proceso(num)) {
        printf("El numero %d es un palindromo\n", num);
    } else {
        printf("El numero %d no es un palindromo\n", num);
    }

    return 0;
}
