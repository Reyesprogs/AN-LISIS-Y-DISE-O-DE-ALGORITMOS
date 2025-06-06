//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETICIONES 1000

int** crearMatriz(int n) {
    int** m = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        m[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
    }
    return m;
}

void liberarMatriz(int** m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void sumar(int** A, int** B, int** R, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void restar(int** A, int** B, int** R, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2, i, j;
    int **A11 = crearMatriz(m), **A12 = crearMatriz(m), **A21 = crearMatriz(m), **A22 = crearMatriz(m);
    int **B11 = crearMatriz(m), **B12 = crearMatriz(m), **B21 = crearMatriz(m), **B22 = crearMatriz(m);
    int **M1 = crearMatriz(m), **M2 = crearMatriz(m), **M3 = crearMatriz(m), **M4 = crearMatriz(m);
    int **M5 = crearMatriz(m), **M6 = crearMatriz(m), **M7 = crearMatriz(m);
    int **T1 = crearMatriz(m), **T2 = crearMatriz(m);

  
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            A11[i][j] = A[i][j];           A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];       A22[i][j] = A[i + m][j + m];
            B11[i][j] = B[i][j];           B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];       B22[i][j] = B[i + m][j + m];
        }

  
    sumar(A11, A22, T1, m); sumar(B11, B22, T2, m); strassen(T1, T2, M1, m);
    sumar(A21, A22, T1, m); strassen(T1, B11, M2, m);
    restar(B12, B22, T1, m); strassen(A11, T1, M3, m);
    restar(B21, B11, T1, m); strassen(A22, T1, M4, m);
    sumar(A11, A12, T1, m); strassen(T1, B22, M5, m);
    restar(A21, A11, T1, m); sumar(B11, B12, T2, m); strassen(T1, T2, M6, m);
    restar(A12, A22, T1, m); sumar(B21, B22, T2, m); strassen(T1, T2, M7, m);

   
    int **C11 = crearMatriz(m), **C12 = crearMatriz(m), **C21 = crearMatriz(m), **C22 = crearMatriz(m);
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C12[i][j] = M3[i][j] + M5[i][j];
            C21[i][j] = M2[i][j] + M4[i][j];
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }

    liberarMatriz(A11, m); liberarMatriz(A12, m); liberarMatriz(A21, m); liberarMatriz(A22, m);
    liberarMatriz(B11, m); liberarMatriz(B12, m); liberarMatriz(B21, m); liberarMatriz(B22, m);
    liberarMatriz(M1, m); liberarMatriz(M2, m); liberarMatriz(M3, m);
    liberarMatriz(M4, m); liberarMatriz(M5, m); liberarMatriz(M6, m); liberarMatriz(M7, m);
    liberarMatriz(C11, m); liberarMatriz(C12, m); liberarMatriz(C21, m); liberarMatriz(C22, m);
    liberarMatriz(T1, m); liberarMatriz(T2, m);
}

int main() {
    int n;
    printf("Tamano de la matriz (potencia de 2): ");
    scanf("%d", &n);

    srand(time(NULL));
    int** A = crearMatriz(n), **B = crearMatriz(n), **C = crearMatriz(n);

    clock_t ini = clock();
    for (int i = 0; i < REPETICIONES; i++)
        strassen(A, B, C, n);
    clock_t fin = clock();

    printf("Tiempo total: %.6f segundos\n", (double)(fin - ini) / CLOCKS_PER_SEC);

    liberarMatriz(A, n); liberarMatriz(B, n); liberarMatriz(C, n);
    return 0;
}
