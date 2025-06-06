//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <limits.h>

int divide(int dividend, int divisor) {
    if (divisor == 0) {
        return INT_MAX;
    }
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    long long a = dividend, b = divisor;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    int quotient = 0;
    while (a >= b) {
        a -= b;
        quotient++;
    }
    return sign * quotient;
}

int main() {
    int dividend, divisor;
    printf("Introduce el dividendo: ");
    scanf("%d", &dividend);
    printf("Introduce el divisor: ");
    scanf("%d", &divisor);
    int result = divide(dividend, divisor);
    printf("El resultado de la division es: %d\n", result);
    return 0;
}
