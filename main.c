#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void ReadFile(char[256], char[256]);
void WriteFile(char[256], int**, int, int);
float ComputeAverage(int*, int);
void FreeAry(int**, int);
void FixBackslashes(char*);

// Main function
void main() {
    // Local declarations
    char fileName[256];
    char fileNameW[256];

    
    printf("Enter the file name you want to read from (EX: output.txt): \n");
    scanf("%s", fileName);
    printf("Enter the file name you want to write to (EX: output.txt): \n");
    scanf("%s", fileNameW);


    ReadFile(fileName, fileNameW);

    printf("File was processed, Goodbye! :)\n");
}

// Function to handle reading from a file
void ReadFile(char fileName[256], char fileNameW[256]) {
    char filePathWay[256];
    FILE *fptr;
    
    // Loop until a valid file is entered
    while (1) {
        printf("Enter the full file path you want to read from (EX: C:\\Users\\...\\): \n");
        scanf("%s", filePathWay);
        strcat(filePathWay, fileName);
        FixBackslashes(filePathWay);

        // Attempt to open the file
        fptr = fopen(filePathWay, "r");
        if (fptr == NULL) {
            printf("Error opening file for reading. Please try again.\n");
        } else {
            break; 
        }
    }

    // Read row and column counts
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

    // Write the data to the output file
    WriteFile(fileNameW, recordsAry, rows, cols);

    // Free the dynamically allocated memory
    FreeAry(recordsAry, rows);
}

// Function to handle writing to a file
void WriteFile(char fileNameW[256], int** recordsAry, int rows, int cols) {
    char filePathWay[256];
    FILE *fptr;

    // Loop until a valid file is entered for writing
    while (1) {
        printf("Enter the full file path you want to write to (EX: C:\\Users\\...\\filename.txt): \n");
        scanf("%s", filePathWay);
        strcat(filePathWay, fileNameW);
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

// Function to compute the average for a row (student's grades)
float ComputeAverage(int* grades, int numCols) {
    int sum = 0;
    for (int i = 1; i < numCols; i++) {
        sum += grades[i];
    }
    return (float)sum / (numCols - 1);
}

// Function to free dynamically allocated memory
void FreeAry(int** recordsAry, int rows) {
    for (int i = 0; i < rows; i++) {
        free(recordsAry[i]);
    }
    free(recordsAry);
}

// Function to fix backslashes in file paths
void FixBackslashes(char* path) {
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '\\') {
            memmove(&path[i + 1], &path[i], strlen(path) - i + 1);
            path[i] = '\\';
            i++;
        }
    }
}
