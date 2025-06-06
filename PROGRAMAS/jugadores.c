//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int dividePlayers(int* skill, int skillSize) {
    qsort(skill, skillSize, sizeof(int), compare);
    
    int total = 0;
    int target = skill[0] + skill[skillSize - 1];

    for (int i = 0; i < skillSize / 2; ++i) {
        int left = skill[i];
        int right = skill[skillSize - 1 - i];

        if (left + right != target)
            return -1;

        total += left * right;
    }

    return total;
}

int main() {
    int skill[] = {3, 2, 5, 1, 3, 4};
    int n = sizeof(skill) / sizeof(skill[0]);
    printf("%d\n", dividePlayers(skill, n));
    return 0;
}
