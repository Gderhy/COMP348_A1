#include "displayingMenu.h"

#include <stdio.h>
#include <string.h>

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

