/*
    Program 4 - Brandin Dooley & Aric Abella
Program uses user input to open a file to read from and a file to write to.
The program reads student ID's and grades associated with the ID's
storing this data to a dynamically created array. This data is then used
to compute the average for each student saving this value to the
array associating it with the correct student. This data is then written
to the write file specified by the user.
*/

//Global Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char[50], char[50]);
void writeFile(char[50], int**, int, int);
float computeAverage(int*, int);
void freeArray(int*, int);

/*
Takes user input for the file to read from and write to
this data is then passed to the readFile function were the
data is processed.
*/
void main() {
    //Local declarations
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
    //Creates *filePath* for read file and open file pointer
    char filePath[50] = "C:\\Users\\Biscq\\";
    strcat(filePath, fileName);
    FILE *fptr = fopen(filePath, "r");
    if (fptr == NULL) {
        printf("File not found\n");
        exit(0);
    }

    //Reads first two values containing row and col info, prints
    int rows = 0, cols = 0;
    fscanf(fptr, "%d", &rows);
    fscanf(fptr, "%d", &cols);
    printf("Rows: %d\nCols: %d\n", rows, cols);

    //Creates 2d array
    int** recordsAry = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        recordsAry[i] = (int*)malloc((cols + 1)  * sizeof(int));
    }

    //Fills 2d array with values from file
    for(int i = 0; i < rows; i++) {
       for(int j = 0; j < cols; j++) {
            fscanf(fptr, "%d", &recordsAry[i][j]);
       }
        recordsAry[i][cols] = computeAverage(recordsAry[i], cols);
    }
    //Closes read file
    fclose(fptr);

    writeFile(fileNameW, recordsAry, rows, cols);

    free(recordsAry);
}

void writeFile(char fileNameW[50],int** recordsAry, int rows, int cols){
    char filePathW[50] = "C:\\Users\\Biscq\\";
    strcat(filePathW, fileNameW);
    FILE* fptr = fopen(filePathW, "w");
    if(fptr == NULL) {
        printf("File not found\n");
    }
     fprintf(fptr, "%d\n", rows);
    fprintf(fptr, "%d\n", cols + 1);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            fprintf(fptr, "%d ", recordsAry[i][j]);
        }
        fprintf(fptr, "%.2f\n", (float)recordsAry[i][cols]);
    }
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

//Frees dynamic memory to avoid memory leak
void freeAry(int** recordsAry[], int rows){
for(int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

