#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void displayMenu();
void displayTableOptions();
void displaySummary(char* str, int numberOfRows, char* outputFileName);

int main(int argc, char **argv){

    system("clear"); // Clears the terminal 

    while(1){

        displayMenu();
        int menuSelection;
        scanf("%d", &menuSelection);
        system("clear");

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
            printf("Enter the output file name: ");
            char outputFileName[100];
            scanf("%s", outputFileName); // ex of input (string)"filename"

            // Printing summary
            printf("\n");
            displaySummary(tableOptionSelection, numberOfRows, outputFileName);
            printf("\n");
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

    printf("\tSummary of properties:\n");
    printf("\t\tColumns: %s\n", selectedTables);
    printf("\t\tNumber of rows: %d\n", numberOfRows);
    printf("\t\tName of output file: %s\n", outputFileName);
    printf("\n");
}










