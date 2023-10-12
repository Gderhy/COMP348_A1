#ifndef GENERATINGDATA_H
#define GENERATINGDATA_H

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
void fillEmail(char*** table, int columnNumber, int numberOfRows, int intTableSelection[], int numberOfCollumns); // Done
void fillSIN(char*** table, int columnNumber, int numberOfRows);//Done
void fillPassword(char*** table, int columnNumber, int numberOfRows);// Done

#endif