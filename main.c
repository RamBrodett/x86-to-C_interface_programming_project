#include <stdio.h>
#include <stdlib.h>

extern imgCvtGrayIntToDouble(int height, int width, int* src2dArray, int* dest2dArray);

int main(){
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
            return 1;
        }
    }

    imgCvtGrayIntToDouble(height, width, src2dArray, dest2dArray);

    printf("Converted Image value:\n");
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            printf("%.2f ", dest2dArray[i*width+j]);
        }
        printf("\n");
        
    }

    free(src2dArray);
    free(dest2dArray);
    return 0;
}