#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "displayingMenu.h"
#include "GeneratingData.h"


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








