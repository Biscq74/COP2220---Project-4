/*
    Program 4 - Brandin Dooley & Aric Abella
    Program uses user input to open a file to read from and a file to write to.
    The program reads student IDs and grades associated with the IDs,
    storing this data to a dynamically created array. This data is then used
    to compute the average for each student, saving this value to the
    array associating it with the correct student. This data is then written
    to the write file specified by the user.
*/

// Global Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void readFile(char[256], char[256]);
void writeFile(char[256], int**, int, int);
float computeAverage(int*, int);
void freeAry(int**, int);
void fix_backslashes(char*);

/*
    Main function takes user input for the file to read from and write to.
    This data is then passed to the `readFile` function for processing.
*/
void main() {

    char fileName[256];
    char fileNameW[256];


    printf("Enter the file name you want to read from (EX: output.txt): ");
    scanf("%s", fileName);

    printf("Enter the file name you want to write to (EX: output.txt): ");
    scanf("%s", fileNameW);

    readFile(fileName, fileNameW);
}

/*
    Reads data from the input file, processes it, and calls the `writeFile` function
    to write the results to the output file.
*/
void readFile(char fileName[256], char fileNameW[256]) {
    char filePathWay[256];
    printf("Enter the full file path you want to read from (EX: C:\\Users\\...\\): ");
    scanf("%s", filePathWay);
    strcat(filePathWay, fileName);
    fix_backslashes(filePathWay);
    printf("(read) File name is: %s\n", filePathWay);
    
    FILE *fptr = fopen(filePathWay, "r");
    if (fptr == NULL) {
        printf("File not found.\n");
        exit(0);
    }

    // Read row and column counts
    int rows = 0, cols = 0;
    fscanf(fptr, "%d", &rows);
    fscanf(fptr, "%d", &cols);
    printf("Rows: %d\nCols: %d\n", rows, cols);

    // Create a 2D array dynamically
    int** recordsAry = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        recordsAry[i] = (int*)malloc((cols + 1) * sizeof(int));
    }

    // Fill the array with data from the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fptr, "%d", &recordsAry[i][j]);
        }
        // Compute the average and store it in the last column
        recordsAry[i][cols] = computeAverage(recordsAry[i], cols);
    }


    fclose(fptr);


    writeFile(fileNameW, recordsAry, rows, cols);


    freeAry(recordsAry, rows);
}

/*
    Writes the processed data (including averages) to the output file.
*/
void writeFile(char fileNameW[256], int** recordsAry, int rows, int cols) {
    char filePathWay[256];
    printf("Enter the full file path you want to read from (EX: C:\\Users\\...\\filename.txt): ");
    scanf("%s", filePathWay);
    strcat(filePathWay, fileNameW);
    fix_backslashes(filePathWay);
    printf("(write) File name is: %s\n", filePathWay);

    FILE* fptr = fopen(filePathWay, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        exit(0);
    }

    // Write rows and columns (including the extra column for averages)
    fprintf(fptr, "%d\n", rows);
    fprintf(fptr, "%d\n", cols + 1);

    // Write the array contents
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fptr, "%d ", recordsAry[i][j]);
        }
        fprintf(fptr, "%.2f\n", (float)recordsAry[i][cols]);
    }
    
    fclose(fptr);
}

/*
    Computes the average for a row (the student's grades) and returns it as a float.
*/
float computeAverage(int* grades, int numCols) {
    int sum = 0;
    for (int i = 1; i < numCols; i++) {
        sum += grades[i];
    }
    return (float)sum / (numCols - 1);
}

/*
    Frees dynamically allocated memory for the 2D array to avoid memory leaks.
*/
void freeAry(int** recordsAry, int rows) {
    for (int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

/*
    Fixes backslashes in a file path, ensuring proper formatting with double backslashes.
*/
void fix_backslashes(char* path) {
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '\\') {
            memmove(&path[i + 1], &path[i], strlen(path) - i + 1);
            path[i] = '\\';
            i++;
        }
    }
}
