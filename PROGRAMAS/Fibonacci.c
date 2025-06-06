//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


bool esPrimo(int n);
void resolverSumaFibonacci(int k);

int main() {
    int dia, mes, anio;
    int k;
    printf("Introduce tu dia de nacimiento: ");
    scanf("%d", &dia);
    printf("Introduce tu mes de nacimiento: ");
    scanf("%d", &mes);
    printf("Introduce tu anio de nacimiento: ");
    scanf("%d", &anio);

    k = (dia * 100) + (mes * 10) + (anio % 100);

    printf("\nEl valor de K calculado es: %d\n", k);  
    resolverSumaFibonacci(k);

    return 0;
}


bool esPrimo(int n) {
    if (n <= 1) return false; 
    if (n <= 3) return true;  
    if (n % 2 == 0 || n % 3 == 0) return false; 

    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}


void resolverSumaFibonacci(int k_original) {
    long long fib_filtrado[100]; 
    int count_filtrado = 0;

    long int a = 0, b = 1;
    int indice = 0;

    printf("Secuencia de Fibonacci filtrada (sin terminos en posiciones primas):\n");
    
    while (a <= k_original) {
        if (!esPrimo(indice)) {
            fib_filtrado[count_filtrado] = a;
            printf("%ld, ", a);
            count_filtrado++;
        }
        long long siguiente = a + b;
        a = b;
        b = siguiente;
        indice++;
    }
   

    int k_restante = k_original;
    long int solucion_terminos[100]; 
    int count_solucion = 0;

    for (int i = count_filtrado - 1; i >= 0; i--) {
        if (fib_filtrado[i] <= k_restante && fib_filtrado[i] > 0) {
            k_restante -= fib_filtrado[i];
            solucion_terminos[count_solucion] = fib_filtrado[i];
            count_solucion++;
        }
    }

    while (k_restante > 0) {
        if (k_restante >= 1) {
             solucion_terminos[count_solucion] = 1;
             count_solucion++;
             k_restante--;
        }
    }


   
    printf("Solucion Optima:\n");
    if (count_solucion > 0) {
        printf("   ");
        for (int i = 0; i < count_solucion; i++) {
            printf("%ld", solucion_terminos[i]);
            if (i < count_solucion - 1) {
                printf(" + ");
            }
        }
        printf(" = %d", k_original);
        printf(" -> %d terminos.\n", count_solucion);
    } else {
        printf("No se encontro una solucion para K = %d con la secuencia generada.\n", k_original);
    }
}

