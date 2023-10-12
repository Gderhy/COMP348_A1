#include "GeneratingData.h"
#include "convertStringToIntArray.h"
#include "WriteDataToFile.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Important function that will handle all the functions required to complete the task
void generateData(char* tableOptionSelection, int numberOfRows, char* outputFileName){

    numberOfRows++; // ++ To account for header


    // first step is to convert string into int[]
    int numberOfCollumns;
    int* intTableSelection = strToIntArray(tableOptionSelection, &numberOfCollumns);
    // Works

    
    // Second step is to create a table matrix containing the data
    char*** table = createTable(numberOfCollumns, numberOfRows);  // Can't forget to free memory use freeTable();
    // Works
 
    // fill table with corresponding data
    fillTable(table, numberOfCollumns, numberOfRows, intTableSelection); 

    // //print to see table
    // printTable(table, numberOfCollumns, numberOfRows);

    // Write to file
    writeDataToFile(table, numberOfCollumns, numberOfRows, outputFileName);
    

    // Free the memory of the table after it is done
    freeTable(table, numberOfCollumns, numberOfRows);
    free(intTableSelection);
}


void fillTable(char*** table, int numberOfCollumns, int numberOfRows, int intTableSelection[]){

    for(int i=0; i < numberOfCollumns; i++){

        if (intTableSelection[i] == 1) fillUserID(table, i, numberOfRows);
        if (intTableSelection[i] == 2) fillFirstName(table, i, numberOfRows);
        if (intTableSelection[i] == 3) fillLastName(table, i, numberOfRows);
        if (intTableSelection[i] == 4) fillCountry(table, i, numberOfRows);
        if (intTableSelection[i] == 5) fillPhoneNumber(table, i, numberOfRows);
        if (intTableSelection[i] == 6) fillEmail(table, i, numberOfRows, intTableSelection, numberOfCollumns);
        if (intTableSelection[i] == 7) fillSIN(table, i, numberOfRows);
        if (intTableSelection[i] == 8) fillPassword(table, i, numberOfRows);
    }
}


// Prints the content of the table
void printTable(char*** table, int columns, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%s ", table[j][i]);
        }
        printf("\n");
    }
}
// Creates an empty 2D string array -- Important, each cell is RESPONSIBLE for allocating the memory it needs
char*** createTable(int numberOfCollumns, int numberOfRows){

    char*** emptyTable = (char***) malloc (numberOfCollumns * sizeof(char**));

    for(int i=0; i < numberOfCollumns; i++){

        emptyTable[i] = (char**) malloc (numberOfRows * sizeof(char*));

        // Allow cell size to be determined by functions
        // for(int j=0; j < numberOfRows; j++){

        //     emptyTable[i][j] = (char*) malloc (20 * sizeof(char));
        // }


    }

    return emptyTable;
}

// Dynamically free the array
void freeTable(char*** table, int numberOfCollumns, int numberOfRows){

    for(int i=0; i < numberOfCollumns; i++){
        for(int j=0; j < numberOfRows; j++){

            free(table[i][j]);
        }
        
        free(table[i]);
    }

    free(table);
}


// Fill userID (1) -- works
void fillUserID(char*** table, int columnNumber, int numberOfRows){

    table[columnNumber][0] = "User IDs";

    const int sizeOfCell = 7; // 1 < x < 1M => 6 char to display xxx xxx +1 for null term

    for(int i=1; i < numberOfRows; i++){

        // memory allocation for cell
        table[columnNumber][i] = (char*) malloc (sizeOfCell * sizeof(char));

        sprintf(table[columnNumber][i], "%d", i);
    }
}

// Filling First name (2) - works
void fillFirstName(char*** table, int columnNumber, int numberOfRows){

    // if(table[columnNumber][0] != NULL) return; // Allows email to be selected before First or Last name
    
    table[columnNumber][0] = "First Name";    

    FILE* file = fopen("data\\first_names.txt", "r");

    if(file == NULL){

        printf("Can't open countries.txt");
        return;
    }

    const int numberOfEntries = 1000; // 195 entries in this file
    
    const int bufferSize = 64;
    char buffer[bufferSize]; // Will be used to read through the lines
    int row = 1;  // Will allow to fill array, start at 1 since 0 is header


    char** contentRead = (char**) malloc(numberOfEntries * sizeof(char*));
    int count = 0;

    // Read and process each line in the file, buffer == the line read + \n
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        // Remove the newline character, if present
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        contentRead[count] = (char*) malloc (bufferSize+1);
        strcpy(contentRead[count++], buffer); // Fill table with value from file and increment row
    }
    fclose(file);

    for(int i=1; i < numberOfRows; i++){

        table[columnNumber][i] = (char*) malloc (bufferSize+1);
        strcpy(table[columnNumber][i], contentRead[rand() % numberOfEntries]);
    }

    // Free contentRead array
    for(int i=0; i <numberOfEntries; i++){

        free(contentRead[i]);
    }

    free(contentRead);
}


// Filling Last name (3) -- works
void fillLastName(char*** table, int columnNumber, int numberOfRows){

    // if(table[columnNumber][0] != NULL) return; // Allows email to be selected before First or Last name

    table[columnNumber][0] = "Last Name";    

    FILE* file = fopen("data\\last_names.txt", "r");

    if(file == NULL){

        printf("Can't open countries.txt");
        return;
    }

    const int numberOfEntries = 1000; // 195 entries in this file
    
    const int bufferSize = 64;
    char buffer[bufferSize]; // Will be used to read through the lines
    int row = 1;  // Will allow to fill array, start at 1 since 0 is header


    char** contentRead = (char**) malloc(numberOfEntries * sizeof(char*));
    int count = 0;

    // Read and process each line in the file, buffer == the line read + \n
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        // Remove the newline character, if present
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        contentRead[count] = (char*) malloc (bufferSize+1);
        strcpy(contentRead[count++], buffer); // Fill table with value from file and increment row
    }
    fclose(file);

    for(int i=1; i < numberOfRows; i++){

        table[columnNumber][i] = (char*) malloc (bufferSize+1);
        strcpy(table[columnNumber][i], contentRead[rand() % numberOfEntries]);
    }

    // Free contentRead array
    for(int i=0; i <numberOfEntries; i++){

        free(contentRead[i]);
    }

    free(contentRead);
}


// Fill Country (4) -- works
void fillCountry(char*** table, int columnNumber, int numberOfRows){
    
    table[columnNumber][0] = "Country";    

    FILE* file = fopen("data\\countries.txt", "r");

    if(file == NULL){

        printf("Can't open countries.txt");
        return;
    }

    const int numberOfEntries = 195; // 195 entries in this file
    
    const int bufferSize = 64;
    char buffer[bufferSize]; // Will be used to read through the lines
    int row = 1;  // Will allow to fill array, start at 1 since 0 is header


    char** contentRead = (char**) malloc(numberOfEntries * sizeof(char*));
    int count = 0;

    // Read and process each line in the file, buffer == the line read + \n
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        // Remove the newline character, if present
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        contentRead[count] = (char*) malloc (bufferSize+1);
        strcpy(contentRead[count++], buffer); // Fill table with value from file and increment row
    }
    fclose(file);

    for(int i=1; i < numberOfRows; i++){

        table[columnNumber][i] = (char*) malloc (bufferSize+1);
        strcpy(table[columnNumber][i], contentRead[rand() % numberOfEntries]);
    }

    for(int i=0; i <numberOfEntries; i++){

        free(contentRead[i]);
    }

    free(contentRead);
}

// Fill Phone Number (5) -- works
void fillPhoneNumber(char*** table, int columnNumber, int numberOfRows){

    table[columnNumber][0] = "Phone number";
    
    char* validIndexCodes[] = {"398", "270", "925", "867", "209", "429", "908", "997", "444", "219"};

    srand(time(NULL));

    const int sizeOfCell = 9;

    for(int i=1; i < numberOfRows; i++){

        char phoneNumber[sizeOfCell]; // xxx-xxxx\0 (9 chars counting null term)
        sprintf(phoneNumber, "%s-%04d",validIndexCodes[rand() % 10], rand() % 10000); // rand() % 10 = [0, 9] & rand() % 10000 = [0,9999]
        

        // Manually set the size of the cell
        table[columnNumber][i] = (char*) malloc (sizeOfCell * sizeof(char));

        strcpy(table[columnNumber][i], phoneNumber); 
    }
}

// Fill email (6) -- this one is more complicated since it requires first and last name to be filled first. 
// Waiting for email
void fillEmail(char*** table, int columnNumber, int numberOfRows, int intTableSelection[], int numberOfCollumns){

    table[columnNumber][0] = "Email";

    int first = -1, last = -1;
    
    // Finding the collumNumber of first name and last name
    for(int i=0; i < numberOfCollumns; i++){

        if(intTableSelection[i] == 2) first = i;
        if(intTableSelection[i] == 3) last = i;
    }

    // Checking if user picked first and last name when choosing collumns
    if(first == -1 || last == -1){

        printf("\nIn order to select email, first and last name must also be selected\n\n");
        
        // Filling table with empty cells
        for(int i=1; i < numberOfRows; i++){

            table[columnNumber][i] = "Cannot produce email.";
        }

        return;
    }


    // Fills up the collums for first and last name in case they are selected afterwards 
    if(columnNumber < first){

        fillFirstName(table, first, numberOfRows);
    }

    if(columnNumber < last){

        fillLastName(table, last, numberOfRows);
    }

    // Filling up email collumn

    FILE* file = fopen("data\\email_suffixes.txt", "r");

    if(file == NULL){

        printf("Can't open email_suffixes.txt");
        return;
    }

    const int numberOfEntries = 100; // 100 entries in this file
    
    const int bufferSize = 64;
    char buffer[bufferSize]; // Will be used to read through the lines
    int row = 1;  // Will allow to fill array, start at 1 since 0 is header


    char** contentRead = (char**) malloc(numberOfEntries * sizeof(char*));
    int count = 0;

    // Read and process each line in the file, buffer == the line read + \n
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        // Remove the newline character, if present
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        contentRead[count] = (char*) malloc (bufferSize+1);
        strcpy(contentRead[count++], buffer); // Fill contentRead with value from file and increment row
    }
    fclose(file);

    for(int i=1; i < numberOfRows; i++){

        table[columnNumber][i] = (char*) malloc (150 * sizeof(char));
        sprintf(table[columnNumber][i], "%c%s@%s",table[first][i][0], table[last][i], contentRead[rand() % numberOfEntries]);
    }

    for(int i=0; i <numberOfEntries; i++){

        free(contentRead[i]);
    }

    free(contentRead);
}

// Fill SIN (7) -- works 
// The reason I did it with a char array is because using rand() wouldnt create large enough numbers
void fillSIN(char*** table, int columnNumber, int numberOfRows){

    table[columnNumber][0] = "SIN";
    
    const int sizeOfCell = 10; //"xxx_xxx_xxx" 9+1 for null term

    char numbers[] = "0123456789";

    for(int i=1; i < numberOfRows; i++){

        char* buffer = (char*) malloc (sizeOfCell * sizeof(char));

        for(int j=0; j < 10; j++){

            buffer[j] = numbers[rand() % sizeOfCell];
        }

        buffer[sizeOfCell - 1] = '\0';
        table[columnNumber][i] = (char*) malloc (sizeOfCell * sizeof(char));

        strcpy(table[columnNumber][i], buffer);

        free(buffer);
    }
}


// Fill Password (8) -- works
void fillPassword(char*** table, int columnNumber, int numberOfRows) {
    
    table[columnNumber][0] = "Passwords";

    const char characters[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789<>.?/\"';:{[]}\\|~`!@#$%%^&*()-_+=";
    const int charLength = strlen(characters);

    for (int i = 1; i < numberOfRows; i++) {
        int lengthOfPassword = rand() % (16 - 6 + 1) + 6;
        char* password = (char*)malloc((lengthOfPassword + 1) * sizeof(char));

        for (int j = 0; j < lengthOfPassword; j++) {
            password[j] = characters[rand() % charLength];
        }
        password[lengthOfPassword] = '\0'; // Null-terminate the password

        // Make sure to free any previous content in the cell
        free(table[columnNumber][i]);

        table[columnNumber][i] = password;
    }
}
