//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100


int sonAnagramas(char *s1, char *s2) {
    if (strlen(s1) != strlen(s2)) return 0;
    
    int frecuencia[256] = {0}; 

    for (int i = 0; s1[i]; i++) {
        frecuencia[(unsigned char)s1[i]]++;
        frecuencia[(unsigned char)s2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (frecuencia[i] != 0) return 0;
    }

    return 1;
}

int esVersionDesordenada(char *s1, char *s2) {
    if (strcmp(s1, s2) == 0) return 1;
    if (!sonAnagramas(s1, s2)) return 0;

    int len = strlen(s1);

    for (int i = 1; i < len; i++) {
        char s1_izq[i + 1], s1_der[len - i + 1];
        char s2_izq[i + 1], s2_der[len - i + 1];

        strncpy(s1_izq, s1, i);
        s1_izq[i] = '\0';
        strcpy(s1_der, s1 + i);

        strncpy(s2_izq, s2, i);
        s2_izq[i] = '\0';
        strcpy(s2_der, s2 + i);

        if (esVersionDesordenada(s1_izq, s2_izq) && esVersionDesordenada(s1_der, s2_der))
            return 1;

        if (esVersionDesordenada(s1_izq, s2_der) && esVersionDesordenada(s1_der, s2_izq))
            return 1;
    }

    return 0;
}

int main() {
    char s1[MAX], s2[MAX];

    printf("Introduce la primera cadena: ");
    scanf("%s", s1);

    printf("Introduce la segunda cadena: ");
    scanf("%s", s2);

    if (esVersionDesordenada(s1, s2))
        printf("\n\"%s\" es una version desordenada de \"%s\".\n", s2, s1);
    else
        printf("\n\"%s\" no es una version desordenada de \"%s\".\n", s2, s1);

    return 0;
}
