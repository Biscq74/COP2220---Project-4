#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fix_backslashes(char *path) {
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '\\') {
            memmove(&path[i + 1], &path[i], strlen(path) - i + 1);
            path[i] = '\\';
            i++;  
        }
    }
}

float computeAverage(int* grades, int numCols) {
    int sum = 0;
    for (int i = 1; i < numCols; i++) {
        sum = sum + grades[i];
    }
    return (float)sum / (numCols - 1);
}

void readFile(char fileName[50], char fileNameW[50]) {
    char filePath[256];
    char filePathW[256] = "C:\\Users\\Biscq\\";


    printf("Enter the file pathway to read from (e.g., C:\\Users\\name\\): ");
    fgets(filePath, sizeof(filePath), stdin);
    filePath[strcspn(filePath, "\n")] = 0;
    fix_backslashes(filePath);
    strcat(filePath, fileName);

  
    FILE *fptr = fopen(filePath, "r");
    if (fptr == NULL) {
        printf("File not found.\n");
        exit(0);
    }

    int rows = 0, cols = 0;
    fscanf(fptr, "%d", &rows);
    fscanf(fptr, "%d", &cols);

    printf("Rows: %d\nCols: %d\n", rows, cols);

    int** recordsAry = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        recordsAry[i] = (int*)malloc((cols + 1) * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fptr, "%d", &recordsAry[i][j]);
        }
        recordsAry[i][cols] = computeAverage(recordsAry[i], cols);
    }
    fclose(fptr);

 
    fix_backslashes(filePathW);
    strcat(filePathW, fileNameW);

   
    fptr = fopen(filePathW, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        exit(0);
    }
    fprintf(fptr, "%d\n", rows);
    fprintf(fptr, "%d\n", cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == 0) {
                fprintf(fptr, "User ID ");
            }
            fprintf(fptr, "%d ", recordsAry[i][j]);
        }
        fprintf(fptr, "Average: %.2f\n", (float)recordsAry[i][cols]);
    }
    fclose(fptr);

    for (int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

int main() {
    char fileName[50];
    char fileNameW[50];

    printf("Enter the file name you want to read from: ");
    scanf("%s", fileName);
    getchar();  
    printf("Enter the file name you want to write to: ");
    scanf("%s", fileNameW);
    getchar(); 

    readFile(fileName, fileNameW);
    return 0;
}
