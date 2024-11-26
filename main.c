/*
    Program 4 - Brandin Dooley & Aric Abella
    Program uses user input to open a file to read from and a file to write to.
    The program reads student IDs and grades associated with the IDs,
    storing this data to a dynamically created array. This data is then used
    to compute the average for each student, saving this value to the
    array associating it with the correct student. This data is then written
    to the write file specified by the user.
*/

//Global declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void ReadFile();
void WriteFile(int**, int, int);
float ComputeAverage(int*, int);
void FreeAry(int**, int);
void FixBackslashes(char*);

//Calls readFile function which calls all other needed functions
void main() {
    // Local statements

    // Local declarations
    ReadFile();
    printf("File was processed, Goodbye! :)\n");
}

/*
    Reads data from the input file, processes it, and calls the `writeFile` function
    to write the results to the output file.
*/
void ReadFile() {
    char filePathWay[256];
    FILE *fptr;

    // Loop until a valid file is entered
    while (1) {
        printf("Enter the full file path you want to read from (EX: C:\\Users\\...\\): \n");
        scanf("%s", filePathWay);
        FixBackslashes(filePathWay);

        // Attempt to open the file
        fptr = fopen(filePathWay, "r");
        if (fptr == NULL) {
            printf("Error opening file for reading. Please try again.\n");
        } else {
            break;
        }
    }

    // Reads row and column from file
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

    // Writes the data to the output file
    WriteFile(recordsAry, rows, cols);

    // Free the dynamically allocated memory
    FreeAry(recordsAry, rows);
}

/*
    Writes the processed data (including averages) to the output file.
*/
void WriteFile( int** recordsAry, int rows, int cols) {
    char filePathWay[256];
    FILE *fptr;

    // Loop until a valid file is entered for writing
    while (1) {
        printf("Enter the full file path you want to write to or create a new one using the pathway and the desired name of the file \n(EX: C:\\Users\\...\\filename.txt): \n");
        scanf("%s", filePathWay);
        FixBackslashes(filePathWay);

        // Attempt to open the file
        fptr = fopen(filePathWay, "w");
        if (fptr == NULL) {
            printf("Error opening file for writing. Please try again.\n");
        } else {
            break;
        }
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
