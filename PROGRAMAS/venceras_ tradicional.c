//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETICIONES 100000

void multiplicarMatrices(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int** crearMatriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
    }
    return matriz;
}

void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

int main() {
    int n;
    printf("Tamano de la matriz (potencia de 2): ");
    scanf("%d", &n);

    srand(time(NULL));
    int** A = crearMatriz(n);
    int** B = crearMatriz(n);
    int** C = crearMatriz(n);

    clock_t inicio = clock();
    for (int i = 0; i < REPETICIONES; i++)
        multiplicarMatrices(A, B, C, n);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo total de ejecucion: %.6f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
