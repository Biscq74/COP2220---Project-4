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
void ReadFile(char[256], char[256]);
void WriteFile(char[256], int**, int, int);
float ComputeAverage(int*, int);
void FreeAry(int**, int);
void FixBackslashes(char*);

/*
    Main function takes user input for the file to read from and write to.
    This data is then passed to the `readFile` function for processing.
*/
void main() {
    //Local declarations
    char fileName[256];
    char fileNameW[256];
    int cont = 1;

    //Local statements
    printf("Enter the file name you want to read from (EX: output.txt): \n");
    scanf("%s", fileName);
    printf("Enter the file name you want to write to (EX: output.txt): \n");
    scanf("%s", fileNameW);

    ReadFile(fileName, fileNameW);

    printf("File was processed, Goodbye! :)");
}

/*
    Reads data from the input file, processes it, and calls the `writeFile` function
    to write the results to the output file.
*/
void ReadFile(char fileName[256], char fileNameW[256]) {
    /*
     *Takes user defined filepath and combines it with the filename, this string is then adjusted to have the
     *correct amount of backslashes so that the file can be accessed
    */
    char filePathWay[256];
    printf("Enter the full file path you want to read from (EX: C:\\Users\\...\\): \n");
    scanf("%s", filePathWay);
    strcat(filePathWay, fileName);
    FixBackslashes(filePathWay);
    // Opens file
    FILE *fptr = fopen(filePathWay, "r");
    if (fptr == NULL) {
        printf("Error opening file for reading\n");
        exit(0);
    }

    // Reads row and column counts
    int rows = 0, cols = 0;
    fscanf(fptr, "%d", &rows);
    fscanf(fptr, "%d", &cols);

    // Create a 2D array dynamically using row and col info
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
        recordsAry[i][cols] = ComputeAverage(recordsAry[i], cols);
    }

    fclose(fptr);

    //Call writeFile function in order to write the data to a user define file
    WriteFile(fileNameW, recordsAry, rows, cols);

    FreeAry(recordsAry, rows);
}

/*
    Writes the processed data (including averages) to the output file.
*/
void WriteFile(char fileNameW[256], int** recordsAry, int rows, int cols) {
    /*
   *Takes user defined filepath and combines it with the filename, this string is then adjusted to have the
   *correct amount of backslashes so that the file can be accessed
  */
    char filePathWay[256];
    printf("Enter the full file path you want to write to (EX: C:\\Users\\...\\filename.txt): \n");
    scanf("%s", filePathWay);
    strcat(filePathWay, fileNameW);
    FixBackslashes(filePathWay);
    // Opens file
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
float ComputeAverage(int* grades, int numCols) {
    int sum = 0;
    for (int i = 1; i < numCols; i++) {
        sum += grades[i];
    }
    return (float)sum / (numCols - 1);
}

/*
    Frees dynamically allocated memory for the 2D array to avoid memory leaks.
*/
void FreeAry(int** recordsAry, int rows) {
    for (int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

/*
    Fixes backslashes in a file path, ensuring proper formatting with double backslashes.
*/
void FixBackslashes(char* path) {
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '\\') {
            memmove(&path[i + 1], &path[i], strlen(path) - i + 1);
            path[i] = '\\';
            i++;
        }
    }
}
