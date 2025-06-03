#include <stdio.h>
//Reyes Caballero Jesus Emmanuel
int trap(int height[], int n) {
    if (n == 0) return 0;
    
    int left_max[n], right_max[n], water = 0;

    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        left_max[i] = (height[i] > left_max[i - 1]) ? height[i] : left_max[i - 1];
    }


    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        right_max[i] = (height[i] > right_max[i + 1]) ? height[i] : right_max[i + 1];
    }


    for (int i = 0; i < n; i++) {
        water += (left_max[i] < right_max[i] ? left_max[i] : right_max[i]) - height[i];
    }

    return water;
}

int main() {
    int height[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int n = sizeof(height) / sizeof(height[0]);
    
    printf("Agua atrapada: %d\n", trap(height, n));
    
    return 0;
}
