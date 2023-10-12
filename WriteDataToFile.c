#include "WriteDataToFile.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Writes the table to the file - works
void writeDataToFile(char*** table, int numberOfCollumns, int numberOfRows, char* fileName){

    char* fullStr = (char*) malloc (100 * sizeof(char));
    snprintf(fullStr, 100, "%s.txt", fileName);
    
    FILE* file = fopen(fullStr, "w");

    if(file == NULL){

        printf("There was an error writing to file: %s", fullStr);
        return;
    }

    for(int row=0; row < numberOfRows; row++){
        for(int collumn=0; collumn < numberOfCollumns; collumn++){

            fprintf(file, "%s%s", table[collumn][row], collumn == numberOfCollumns-1 ? "\n" : ", ");
        }
    }

    
    fclose(file);

    printf("\n\nSuccessfully wrote to %s", fullStr);

    free(fullStr);
}