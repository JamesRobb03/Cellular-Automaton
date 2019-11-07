#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define WSQUARE "\u2610"
#define XSQUARE "\u2612"

//function used to compare 3 items in the generation array to the rule set. Returns an output of 1 or 0 depending on the rule
//basically just lots of if statements. must be a better way to do it.
int compare(int rule[], int i, int array[], int width);

//Function used to print out generations
void printGeneration(int array[], int width);

//Function used to swap arrays. Used to set the nextGen to the current generation
void swap_arrays(int *y, int *z, int width);

//function which converts integer, into binary number array
//Some parts of the code taken from https://www.geeksforgeeks.org/program-decimal-binary-conversion/
void createRule(int *array, int number);

//Function for printing an array. Used when debugging the program.
void print(int array[]);

void setRule(int *pInt);

void setNumberOfGenerations(int *pInt);

void setWidht(int *pInt);

//Preset generation
void genPreset();

//user Generation
void userGeneration();

// //function which saves automation to a text file.
// int saveAutomation(int array[], int width[]);

int power(int base, int exp);

int getDecimalFromNLongBinary(int width);

void getInitDecimal(int *pInt, int width);

void setInitArrayBinary(int *initStateArr, int width);



