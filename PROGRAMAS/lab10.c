// Reyes Caballero Jesus Emmanuel
#include <stdio.h>

#define MAX_ITEMS 4
#define MAX_WEIGHT 4

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    
    int x, i;

    int pesos[MAX_ITEMS] = {1, 4, 3, 1};   
    int valores[MAX_ITEMS] = {1500, 3000, 2000, 2000};  
    
    int dp[MAX_ITEMS + 1][MAX_WEIGHT + 1];

  
    for (i = 0; i <= MAX_ITEMS; i++) {
        for (x = 0; x <= MAX_WEIGHT; x++) {
            if (i == 0 || x == 0)
                dp[i][x] = 0;
            else if (pesos[i - 1] <= x)
                dp[i][x] = max(valores[i - 1] + dp[i - 1][x - pesos[i - 1]], dp[i - 1][x]);
            else
                dp[i][x] = dp[i - 1][x];
        }
    }

   
    printf("Tabla de valores DP:\n");
    for (i = 0; i <= MAX_ITEMS; i++) {
        for (x = 0; x <= MAX_WEIGHT; x++) {
            printf("%5d ", dp[i][x]);
        }
        printf("\n");
    }

 
    printf("\nValor maximo que puede llevar en la mochila: $%d\n", dp[MAX_ITEMS][MAX_WEIGHT]);

    return 0;
}

