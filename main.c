#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

extern void imgCvtGrayIntToDouble(int height, int width, int* src2dArray, double* dest2dArray);
void print_header();
void system_pause();
void print_choices();
void print_header_test();
void convert();
void imgCvtGrayIntToDouble_C(int height, int width, int* matrix, double* matrixD_C);
void performance_test(int height, int width);

int main(){
    srand(time(NULL));  
    bool keepRunning = true;
    int choice;
    while (keepRunning){
        print_choices();
        printf("Enter choice: ");
        while (scanf("%d", &choice)!=1 || choice < 1 || choice > 3){
            printf("Invalid input. Please enter a number from 1-3 only.\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
        } 

        switch (choice){
        case 1:
            system("cls");
            convert();
            system_pause();
            system("cls");
            break;
        case 2:
            system("cls");
            print_header_test();
            performance_test(10, 10);
            performance_test(100, 100);
            performance_test(1000, 1000);
            system_pause();
            system("cls");
            break;
        case 3:
            keepRunning = false;
            break;
        }
    }
    return 0;
}

void convert(){
    int height, width;

    printf("Input height and width, separated by a space: ");
    scanf("%d %d", &height, &width);

    int totalElements = height * width;

    int* src2dArray = (int*)malloc(height*width*sizeof(int));
    double* dest2dArray = (double*)malloc(height*width*sizeof(double));

    printf("Enter %d integers range[1-255] for the matrix (row by row and separated by space):\n", totalElements);
    for(int i = 0; i < totalElements; i++){
        if(scanf("%d", &src2dArray[i]) != 1 || src2dArray[i] < 1 || src2dArray[i] > 255){
            printf("Invalid input. Please integer from 1-255 only.\n");
            free(src2dArray);
            free(dest2dArray);
            return;
        }
    }

    imgCvtGrayIntToDouble(height, width, src2dArray, dest2dArray);

    print_header();
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            printf("%.2f ", dest2dArray[i*width+j]);
        }
        printf("\n");
        
    }

    free(src2dArray);
    free(dest2dArray);
}

void performance_test(int height, int width){
    double sum = 0.0;
    clock_t t;

    int* matrix = (int*)malloc(height * width * sizeof(int));
    double* matrixD = (double*)malloc(height * width * sizeof(double));
    double* matrixD_C = (double*)malloc(height * width * sizeof(double));

    if (matrix == NULL || matrixD == NULL || matrixD_C == NULL) {
        printf("Memory allocation failed for %dx%d matrix.\n", height, width);
        if (matrix) free(matrix);
        if (matrixD) free(matrixD);
        if (matrixD_C) free(matrixD_C);
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

    imgCvtGrayIntToDouble_C(height, width, matrix, matrixD_C);

    bool matricesEqual = true;
    for (int i = 0; i < height * width; i++) {
        if (fabs(matrixD[i] - matrixD_C[i]) > 1e-9) { // Allow small floating-point tolerance
            matricesEqual = false;
            break;
        }
    }


    printf("-------------------------------------------------\n");
    printf("Matrix Shape: %dx%d\n", height, width);
    printf("Avg time of execution is %.6f seconds\n", sum / 30);
    if (matricesEqual) {
        printf("Verification successful: Matrices are identical.\n");
    } else {
        printf("Verification failed: Matrices differ.\n");
    }
    printf("-------------------------------------------------\n");

    free(matrix);
    free(matrixD);
    free(matrixD_C);
}

void imgCvtGrayIntToDouble_C(int height, int width, int* matrix, double* matrixD_C){
    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            matrixD_C[i*width+j] = (double)matrix[i*width+j]/255.0;
        }
    }

}

void print_choices(){
    printf("\n\n");
    printf("-------------------------------------------------\n");
    printf("      [1] Convert Image                          \n");
    printf("      [2] Performance Test                       \n");
    printf("      [3] Exit                                   \n");
    printf("-------------------------------------------------\n");
}

void print_header(){
    printf("\n\n");
    printf("-------------------------------------------------\n");
    printf("  Image Conversion from Gray Int to Gray Double  \n");
    printf("-------------------------------------------------\n");
}

void print_header_test(){
    printf("\n\n");
    printf("-------------------------------------------------\n");
    printf("                 PERFORMANCE TEST                \n");
    printf("-------------------------------------------------\n");
}

void system_pause(){
    printf("\n\n");
    system("pause");
}

