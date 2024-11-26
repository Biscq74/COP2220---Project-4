/*
    Program 4 - Brandin Dooley & Aric Abella
Program uses user input to open a file to read from and a file to write to.
The program reads student ID's and grades associated with the ID's
storing this data to a dynamically created array. This data is then used 
to compute the average for each student saving this value to the 
array associating it with the correct student. This data is then written
to the write file specified by the user.
*/

//Global Declerations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char[50], char[50]);
float computeAverage(int*, int);

/*
Takes user input for the file to read from and write to 
this data is then passed to the readFile function were the 
data is proccessed.
*/
void main() {
    //Local declerations
    char fileName[50];
    char fileNameW[50];
    
    //Local statements
    printf("Enter the file name you want to read from: ");
    scanf("%s", fileName);
    printf("Enter the file name you want to write to: ");
    scanf("%s", fileNameW);
    readFile(fileName, fileNameW);

}


void readFile(char fileName[50], char fileNameW[50]){
    char filePath[50] = "C:\\Users\\Biscq\\";
    char filePathW[50] = "C:\\Users\\Biscq\\";
    strcat(filePath, fileName);
    FILE *fptr = fopen(filePath, "r");
    if (fptr == NULL) {
        printf("File not found\n");
        exit(0);
    }

    int rows = 0, cols = 0;
    fscanf(fptr, "%d", &rows);
    fscanf(fptr, "%d", &cols);

    printf("Rows: %d\nCols: %d\n", rows, cols);

    int** recordsAry = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        recordsAry[i] = (int*)malloc((cols + 1)  * sizeof(int));
    }

    for(int i = 0; i < rows; i++) {
       for(int j = 0; j < cols; j++) {
            fscanf(fptr, "%d", &recordsAry[i][j]);
       }
        recordsAry[i][cols] = computeAverage(recordsAry[i], cols);
    }
    fclose(fptr);

    strcat(filePathW, fileNameW);
    fptr = fopen(filePathW, "w");
    if(fptr == NULL) {
        printf("File not found\n");
    }
    fprintf(fptr, "%d\n", rows);
    fprintf(fptr, "%d\n", cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(j == 0) {
                fprintf(fptr, "User ID ");
            }
            fprintf(fptr, "%d ", recordsAry[i][j]);
        }
        fprintf(fptr, "Average: %.2f\n", (float)recordsAry[i][cols]);
    }

    fclose(fptr);
    for(int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

/*
Computes the average for the row(the student) and returns
this value as a float.
*/
float computeAverage(int* grades, int numCols) {
    int sum = 0;
    for(int i = 1; i < numCols; i++) {
        sum = sum + grades[i];
    }
    return (float)(sum / (numCols - 1));
}
