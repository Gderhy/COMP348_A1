#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



//Menu displaying
void displayMenu();
void displayTableOptions();
void displaySummary(char* str, int numberOfRows, char* outputFileName);

// Converting string to int array
int* strToIntArray(char* str, int* length);
void printIntegerArray(int integerArray[], int size);

// important function
void generateData(char* tableOptionSelection, int numberOfRows, char* outputFileName);


// Creating table matrix
void printTable(char*** table, int columns, int rows);
char*** createTable(int numberOfcolumns, int numberOfRows);

// Filling table
void fillTable(char*** table, int numberOfCollumns, int numberOfRows, int intTableSelection[]); //Done
void freeTable(char*** table, int numberOfCollumns, int numberOfRows); //Done
void fillUserID(char*** table, int columnNumber, int numberOfRows); //Done
void fillFirstName(char*** table, int columnNumber, int numberOfRows);//Done
void fillLastName(char*** table, int columnNumber, int numberOfRows);//Done
void fillCountry(char*** table, int columnNumber, int numberOfRows);//Done
void fillPhoneNumber(char*** table, int columnNumber, int numberOfRows);// Done
void fillEmail(char*** table, int columnNumber, int numberOfRows, int intTableSelection[], int numberOfCollumns); // not done
void fillSIN(char*** table, int columnNumber, int numberOfRows);//Done
void fillPassword(char*** table, int columnNumber, int numberOfRows);// Done

// Writing data to files
void writeDataToFiles(char*** table, int numberOfCollumns, int numberOfRows, char* fileName);


int main(int argc, char **argv){

    char* commandForClearing = "cls"; // "cls" for windows and "clear" for linux
    
    srand(time(NULL));

    while(1){

        system(commandForClearing);
        displayMenu();
        int menuSelection;
        scanf("%d", &menuSelection);
        system(commandForClearing);

        if(menuSelection == 1){

            // Selecting table options
            displayTableOptions();
            char tableOptionSelection[20];
            scanf("%s", tableOptionSelection); // ex of input (string): "1,2,3,4"

            // defining number of rows
            printf("Enter row count (1 < n < 1M): ");
            int numberOfRows;
            scanf("%d", &numberOfRows); // ex of input (int) 45

            // defining the outputfilename
            printf("Enter the output file name (without .txt): ");
            char outputFileName[100];
            scanf("%s", outputFileName); // ex of input (string)"filename"

            // Printing summary
            printf("\n");
            displaySummary(tableOptionSelection, numberOfRows, outputFileName);
            printf("\n"); 


            // Next steps, read files to create necessary tables and write to output files
            generateData(tableOptionSelection, numberOfRows, outputFileName);
                
            char proceed;
            printf("\nPress 'c' or 'C' to continue ");
            do{
            scanf("%c", &proceed);
            } while ( (proceed != 'c') && (proceed != 'C'));
                
        } else { //Terminating program

            printf("Goodbye and thanks for using TableGen.\n");
            break;
        }
    }
    
    return 0;
}


// Display displayMenu options
void displayMenu(){
    
    printf("TableGen Menu\n");
    printf("-------------\n");
    printf("1. Generate new table\n");
    printf("2. Exit\n\n");

    printf("Selection: ");
}

// Display the table options you can choose from
void displayTableOptions(){

    printf("Column Options\n");
    printf("--------------\n");
    printf("1. User ID\n");
    printf("2. First name\n");
    printf("3. Last name\n");
    printf("4. Country\n");
    printf("5. Phone number\n");
    printf("6. Email address\n");
    printf("7. SIN\n");
    printf("8. Password\n\n");

    printf("Enter column list (comma-seperated, no space): ");
}


// Summarizes the collumns and their proprerties
void displaySummary(char* selectedTables, int numberOfRows,  char* outputFileName){

    printf("Summary of properties:\n");
    printf("\tColumns: %s\n", selectedTables);
    printf("\tNumber of rows: %d\n", numberOfRows);
    printf("\tName of output file: %s\n", outputFileName);
    printf("\n");
}


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

// Important function that will handle all the functions required to complete the task
void generateData(char* tableOptionSelection, int numberOfRows, char* outputFileName){

    // first step is to convert string into int[]
    int numberOfCollumns;
    int* intTableSelection = strToIntArray(tableOptionSelection, &numberOfCollumns);
    // Works

    
    // Second step is to create a table matrix containing the data
    char*** table = createTable(numberOfCollumns, numberOfRows);  // Can't forget to free memory use freeTable();
    // Works
 
    // fill tableWWS
    fillTable(table, numberOfCollumns, numberOfRows, intTableSelection); // ++ To account for header

    // //print to see table
    // printTable(table, numberOfCollumns, numberOfRows);

    // Write to file
    writeDataToFiles(table, numberOfCollumns, numberOfRows, outputFileName);
    

    // Free the memory of the table after it is done
    freeTable(table, numberOfCollumns, numberOfRows);
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

        char* buffer = (char*) malloc (10 * sizeof(char));

        for(int j=0; j < 10; j++){

            buffer[j] = numbers[rand() % 10];
        }


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



// Writes the table to the file - works
void writeDataToFiles(char*** table, int numberOfCollumns, int numberOfRows, char* fileName){

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










