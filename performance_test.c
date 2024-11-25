#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern void imgCvtGrayIntToDouble(int height, int width, int* src2dArray, double* dest2dArray);

void measureExecutionTime(int height, int width) {
    double sum = 0.0;
    clock_t t;

    int* matrix = (int*)malloc(height * width * sizeof(int));
    double* matrixD = (double*)malloc(height * width * sizeof(double));

    if (matrix == NULL || matrixD == NULL) {
        printf("Memory allocation failed for %dx%d matrix.\n", height, width);
        if (matrix) free(matrix);
        if (matrixD) free(matrixD);
        return;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i * width + j] = rand() % 255 + 1;
        }
    }

    for (int i = 0; i < 30; i++) {
        t = clock();
        imgCvtGrayIntToDouble(height, width, matrix, matrixD);
        t = clock() - t;
        sum += (double)t / CLOCKS_PER_SEC;
    }

    printf("Avg time of execution for %dx%d matrix with random values is %.6f seconds\n", height, width, sum / 30);

    free(matrix);
    free(matrixD);
}

int main() {
    srand(time(NULL));  

    measureExecutionTime(10, 10);
    measureExecutionTime(100, 100);
    measureExecutionTime(1000, 1000);

    return 0;
}
