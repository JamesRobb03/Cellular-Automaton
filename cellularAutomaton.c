/**
FUNCTIONS:
1. GET RULE(DECIMAL TO BINARY(INTEGER))
2. COMPARE(RULE, I, ARRAY) returns 1 or 0; 
3. PRINT GENERATION(HEIGHT, WIDTH, RULE)
**/

//TO-DO: INPUT VERIFICATION - All inputs are integers. function which checks if an input is an int with upper and lower bounds.
// 		 FIRST GENERATION EDITING
//		 SAVE OUTPUT TO FILE


#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "cellularAutomaton.h"

int main()
{
	int userOptions;
	while(1){
		printf("1.Generate preset automaton\n");
		printf("2.Generate your own \n");
		printf("0. Exit\n");
		printf("Please enter a choice: ");
		scanf("%d", &userOptions);
		if (userOptions == 1)
		{
			genPreset();
			printf("\n");
		} 
		else if(userOptions == 2)
		{
			userGeneration();
			printf("\n");
		}
		else if (userOptions == 0)
		{
			break;
		}
		else{
			printf("\nPlease try again and enter a valid option\n\n");
		}
	}
	return 0;
}

//function used to compare 3 items in the generation array to the rule set. Returns an output of 1 or 0 depending on the rule
//basically just lots of if statements. must be a better way to do it.
int compare(int rule[], int i, int array[], int width)
{
	int c1[3] = {0,0,0};
	int c2[3] = {0,0,1};
	int c3[3] = {0,1,0};
	int c4[3] = {0,1,1};
	int c5[3] = {1,0,0};
	int c6[3] = {1,0,1};
	int c7[3] = {1,1,0};
	int c8[3] = {1,1,1};

	int first;
	int third;

	//check if array[i-1] is out of bounds
	if (array[i-1] == 0 || array[i-1] == 1)
	{
		first = array[i-1];
	}else
	{
		first = array[width-1];
	}

	//check if array[i+1] is out of bounds
	if (array[i+1] == 0 || array[i+1] == 1)
	{
		third = array[i+1];
	}else
	{
		third = array[0];
	}

	int compArray[3] = {first, array[i], third};

	//printf("%d %d %d :", compArray[0], compArray[1], compArray[2]);

	if (memcmp(c1, compArray, sizeof(c1))==0)
	{
		return rule[0];
	}
	else if (memcmp(c2, compArray, sizeof(c1))==0)
	{
		return rule[1];
	}
	else if (memcmp(c3, compArray, sizeof(c1))==0)
	{
		return rule[2];
	}
	else if (memcmp(c4, compArray, sizeof(c1))==0)
	{
		return rule[3];
	}
	else if (memcmp(c5, compArray, sizeof(c1))==0)
	{
		return rule[4];
	}
	else if (memcmp(c6, compArray, sizeof(c1))==0)
	{
		return rule[5];
	}
	else if (memcmp(c7, compArray, sizeof(c1))==0)
	{
		return rule[6];
	}
	else if (memcmp(c8, compArray, sizeof(c1))==0)
	{
		return rule[7];
	}
	else
	{
		return 2;
	}
}

//Function used to print out generations
void printGeneration(int array[], int width)
{
	for (int i = 0; i < width; ++i)
		{
			if (array[i]==1)
			{
				printf("%s ",XSQUARE);
			}
			else{
				printf("%s ",WSQUARE);
			}
		}
	printf("\n");
}

//Function used to swap arrays. Used to set the nextGen to the current generation
void swap_arrays(int *y, int *z, int width)
{
    int x,temp;

    for(x=0;x<width;x++)
    {
        temp = y[x];
        y[x] = z[x];
        z[x] = temp;
    }
}

//function which converts integer, into binary number array
//Some parts of the code taken from https://www.geeksforgeeks.org/program-decimal-binary-conversion/
void createRule(int *array, int number)
{

	for (int i = 0; i < 8; ++i)
	{
		int remainder = number >> i;
		if (remainder & 1)
		{
			array[i] = 1;
		}
		else
		{
			array[i] = 0;
		}
	}
}

//Function for printing an array. Used when debugging the program.
void print(int array[])
{
	for (int i = 7; i >= 0; --i)
	{
		printf("%d\n", array[i]);
	}
}

void setRule(int *pInt)
{
	do
	{
		printf("Please enter rule between %d and %d: ", 0, 255);
		scanf("%d", pInt);
	} while ((*pInt < 0) || (*pInt > 255));

	printf("You have set the rule to be equal to %d\n", *pInt);
}

void setNumberOfGenerations(int *pInt)
{
	do
	{
		printf("Please enter desired number of generations equal or greater than %d: ", 1);
		scanf("%d", pInt);
	} while ((*pInt < 1));

	printf("You have set the number of generations to be equal to %d\n", *pInt);
}

void setWidht(int *pInt)
{
	struct winsize w;

	char givePermission = '\0';
    
	do
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		printf ("Your terminal window can fit a grid without problem with width up to %d.\n", (w.ws_col/2));
		printf("Please enter width of a grid greater or equal to %d: ", 3);
		scanf("%d", pInt);

		if (*pInt > (w.ws_col/2))
		{
			printf("[WARNING] Desired width of %d is greater than window's size!\n", *pInt);	
			do
			{
				printf("Grid may not display properly. Continue? [Y/n]: ");
				scanf(" %c", &givePermission);

				if (givePermission == 'Y')
				{
					break;
				}
				else if (givePermission == 'N')
				{
					break;
				}
				else if (givePermission == 'n')
				{
					break;
				}
				else
				{
					givePermission = '\0';
				}
			} while (givePermission == '\0');
		}
		else if ((*pInt >= 3) && (*pInt <= (w.ws_col/2)))
		{
			givePermission = 'Y';
		}
		else
		{
			givePermission = '\0';
		}


	} while (givePermission != 'Y');

	printf("You have set the width of the grid to be equal to %d\n", *pInt);
}

//Preset generation
void genPreset()
{
	printf("\n");
	printf("Using rule 30\n");
	printf("Using width 31\n");
	printf("displaying 16 generations\n");
	printf("\n");

	int n = 31;
	int rule[8] = {0,1,1,1,1,0,0,0};
	int generationArray[n];
	int nextGen[n];
	int numGen = 16;

	numGen = numGen - 1;


	//set all items in array to 0
	for (int i = 0; i < n; ++i)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}
	//sets centre of array to 1
	generationArray[n/2] = 1;

	//prints the starting generation
	printGeneration(generationArray, n);

	for (int i = 0; i < numGen; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int result = compare(rule, j, generationArray, n);
			//printf("RESULT: %d\n", result);
			nextGen[j] = result;
		}
		swap_arrays(generationArray, nextGen, n);
		printGeneration(generationArray, n);
	}
}



//user Generation
void userGeneration()
{
	//Starter variables.
	int width = 0;
	int numberGenerations = 0;
	int ruleInteger = 0;
	int ruleSet[8] = {0};

	//User Input
	setRule(&ruleInteger);
	setWidht(&width);	
	setNumberOfGenerations(&numberGenerations);
	printf("\n");


	int generationArray[width];
	int nextGen[width];

	for (int i = 0; i < width; i++)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}

	numberGenerations = numberGenerations -1;
	//Get input for starting generation

	//set rule
	createRule(ruleSet, ruleInteger);

	// if width is even
	if (width % 2 == 0)
	{
		generationArray[width/2] = 1;
		generationArray[(width/2)-1] = 1;
	}
	// if width is odd
	else
	{
		generationArray[width/2] = 1;
	}

	printGeneration(generationArray, width);

	for (int i = 0; i < numberGenerations; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int result = compare(ruleSet, j, generationArray, width);
			//printf("RESULT: %d\n", result);
			nextGen[j] = result;
		}
		swap_arrays(generationArray, nextGen, width);
		printGeneration(generationArray, width);
	}

}