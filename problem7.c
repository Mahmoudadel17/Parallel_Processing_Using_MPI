#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>




double squareRoot(double num) {
    double epsilon = 0.00001;
    double guess = num / 2.0;

    while ((guess * guess - num) > epsilon) {
        guess = (guess + num / guess) / 2.0;
    }

    return guess;
}


int main() {
    int array_size;
    printf("Array size: ");
    scanf("%d", &array_size);

    int *array = (int *) malloc(array_size * sizeof(int));
    printf("Array elements: ");
    int i = 0;
    for ( ;i < array_size; i++) {
        scanf("%d", &array[i]);
    }

    double mean = 0.0;
    double squared_diff_sum = 0.0;

    #pragma omp parallel for reduction(+:mean)
    for (i = 0; i < array_size; i++) {
        mean += array[i];
    }

    mean /= array_size;

    #pragma omp parallel for reduction(+:squared_diff_sum)
    for (i = 0; i < array_size; i++) {
        double diff = array[i] - mean;
        squared_diff_sum += diff * diff;
    }

    double variance = squared_diff_sum / array_size;
    double standard_deviation = squareRoot(variance);

    printf("Mean = %.1f, Variance = %.4f, Standard deviation = %.4f\n", mean, variance, standard_deviation);

    free(array);

    return 0;
}
