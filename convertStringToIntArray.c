#include "convertStringToIntArray.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//returns dynamically sized int array
int* strToIntArray(char* str, int* size){

    const int maxElements = 8; // Maximum number of elements in the array (8 options possible)
    int* array = (int*) malloc (maxElements * sizeof(int));
    int count = 0; // Counter for the number of integers found
    char* token; // Pointer to store each token

    // Tokenize the input string based on commas
    token = strtok(str, ",");

    while (token != NULL && count < maxElements) {
        // Convert the token to an integer and store it in the array
        array[count] = atoi(token);
        count++;

        // Get the next token
        token = strtok(NULL, ",");
    }

    if(count <= 0){

        free(array);
        return NULL;
    }


    // Resize dynamic size of array
    array = (int*) realloc(array, count * sizeof(int));

    // Assigns count to size 
    *size = count;

    // returns array with proper size
    return array;
}


// Prints int array
void printIntegerArray(int integerArray[], int size){

    if(size < 1){

        printf("IntegerArray is empty.");
        return;
    }

    for(int i = 0; i < size; i++){

        printf("%d: %d\n",i, integerArray[i]);
    }
}