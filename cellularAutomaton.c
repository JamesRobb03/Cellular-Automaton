#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
// we need this fro unsigned long long int ULLONG_MAX
#include <limits.h>
#include "cellularAutomaton.h"

int main()
{
	int userOptions;
	logo();
	while(1){
		printf("1.Generate preset automaton\n");
		printf("2.Generate your own \n");
		printf("3.Help\n");
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
			printf("\n");
			userGeneration();
			printf("\n");
		}
		else if(userOptions == 3)
		{
			printf("\n");
			displayHelp();
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


void displayHelp()
{
	printf("HELP\n");
	printf("Option 1: \n");
	printf("This option prints out the default 1D cellular automaton\n");
	printf("This uses Rule 30, has width 31, and displays 16 generations\n");
	printf("This option also saves the automaton to a file.\n");
	printf("\n");
	printf("Option 2: \n");
	printf("This option allows the user to generate their own automaton by setting the rule, the width, the amount of generations and allows them to choose a starting generation\n");
	printf("-A rule can be any number between 0 and 255\n");
	printf("-Width can be any number greater than 3, however you will see a warning if your terminal window is too small to display the automaton properly however you can choose to ignore this warning if you wish.\n");
	printf("-The amount of generations can be any number greater than 1\n");
	printf("-You can choose to change the starting generation. However this only works with widths less than 64. This is due to the way the program sets the starting generation\n");	
	printf("The program converts the width into a binary number where all elements in an array of length width is equal to 1.\n");
	printf("for an example if width was set to 3. then the user would be asked for an input between 1 and 7. as 111 in binary is 7.\n");
	printf("this means that when the width is greater than 64 the number stored is too big for memory.\n");
	printf("so if the user wishes to still set the first generation the program automatically sets the width to 63 if the width was previously set to be greater.\n");
	printf("\n");
}

void logo()
{
	printf("□ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □\n");
	printf("□ □ ▣ ▣ □ ▣ ▣ ▣ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ ▣ □ ▣ □ □ □ □ ▣ □ □ ▣ ▣ ▣ □\n");
	printf("□ ▣ □ □ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ ▣ □ ▣ □ □ □ ▣ □ ▣ □ ▣ □ ▣ □\n");
	printf("□ ▣ □ □ □ ▣ ▣ ▣ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ ▣ □ ▣ □ □ □ ▣ ▣ ▣ □ ▣ ▣ □ □\n");
	printf("□ ▣ □ □ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ □ ▣ □ □ ▣ □ ▣ □ □ □ ▣ □ ▣ □ ▣ □ ▣ □\n");
	printf("□ □ ▣ ▣ □ ▣ ▣ ▣ □ ▣ ▣ ▣ □ ▣ ▣ ▣ □ □ ▣ ▣ □ □ ▣ ▣ ▣ □ ▣ □ ▣ □ ▣ □ ▣ □\n");
	printf("□ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □\n");
	printf("□ □ ▣ □ □ ▣ □ ▣ □ ▣ ▣ ▣ □ ▣ □ □ □ ▣ □ ▣ □ □ □ ▣ □ □ ▣ ▣ ▣ □ □ ▣ □ □\n");
	printf("□ ▣ □ ▣ □ ▣ □ ▣ □ □ ▣ □ ▣ □ ▣ □ ▣ □ ▣ □ ▣ □ ▣ □ ▣ □ □ ▣ □ □ ▣ □ ▣ □\n");
	printf("□ ▣ ▣ ▣ □ ▣ □ ▣ □ □ ▣ □ ▣ □ ▣ □ ▣ □ □ □ ▣ □ ▣ ▣ ▣ □ □ ▣ □ □ ▣ ▣ ▣ □\n");
	printf("□ ▣ □ ▣ □ ▣ □ ▣ □ □ ▣ □ ▣ □ ▣ □ ▣ □ □ □ ▣ □ ▣ □ ▣ □ □ ▣ □ □ ▣ □ ▣ □\n");
	printf("□ ▣ □ ▣ □ □ ▣ □ □ □ ▣ □ □ ▣ □ □ ▣ □ □ □ ▣ □ ▣ □ ▣ □ □ ▣ □ □ ▣ □ ▣ □\n");
	printf("□ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □\n");
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
		printf ("Your terminal window can fit a grid with width up to %d without a problem.\n", (w.ws_col/2));
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
	saveAutomation(generationArray, n);

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
		
		saveAutomation(generationArray, n);
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


	int generationArray[width];
	int nextGen[width];

	// init arrays to 0
	for (int i = 0; i < width; i++)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}

	setInitArrayBinary(generationArray, &width);

	setNumberOfGenerations(&numberGenerations);
	printf("\n");

	numberGenerations = numberGenerations -1;
	//Get input for starting generation

	//set rule
	createRule(ruleSet, ruleInteger);

	printGeneration(generationArray, width);
	
	saveAutomation(generationArray, width);

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
		
		saveAutomation(generationArray, width);
	}

}

unsigned long long int power(int base, int exp)
{
    unsigned long long int result = 1;
    while(exp) { result *= base; exp--; }
    return result;
}

unsigned long long int getULLINTFromNLongBinary(int width)
{
	unsigned long long int output = 0;

	for (int i = 0; i < width; i++)
	{
		output = output + power(2, i);
	}

	return output;
}

void getInitULLINT(unsigned long long int *pULLINT, int width)
{
	unsigned long long int maxULLINT = getULLINTFromNLongBinary(width);

	do
	{
		printf("Please enter initial condition as a UNSIGNED LONG LONG INTEGER between %d and %lld: ", 0, maxULLINT);
		scanf("%llu", pULLINT);
	} while ((*pULLINT > maxULLINT));

	printf("You have set the initial condition to be equal to %lld\n", *pULLINT);
}

void setInitArrayBinary(int *generationArray, int *width)
{
	char givePermission = '\0';
	
	if ((*width) > 63)
	{
		printf("[WARNING] You have entered width greater that 63. \nNote that, if you decide NOT to use the default initial condition, the width will be set to 63 automatically. \nThat is because width greater that 63 cannot be set initial condition due to the limit of UNASIGNED LONG LONG INT.\n");
	}

	printf("Do you want to go with the default initial condition and initialise only the middle elemet(s)?\n");

	do
	{
		printf("Continue default? [Y/n]: ");
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

	if (givePermission == 'Y')
	{
		// if width is even
		if ((*width) % 2 == 0)
		{
			generationArray[(*width)/2] = 1;
			generationArray[((*width)/2)-1] = 1;
		}
		// if width is odd
		else
		{
			generationArray[(*width)/2] = 1;
		}
	}

	else
	{
		if ((*width) > 63)
		{
			(*width) = 63;
			printf("[NOTE] Width set automatically to 64.\n");
		}

		unsigned long long int initULLINT;

		getInitULLINT(&initULLINT, *width);

		int i;

		for( i = 0; initULLINT > 0; i++)    
		{    
			generationArray[i] = initULLINT%2;    
			initULLINT = initULLINT/2;    
		}

		printf("In BINARY of the given ULLINT is equal to ");   

		for(i= i-1; i >= 0; i--)    
		{    
			printf("%d", generationArray[i]);    
		}   

		printf("\n");

		printf("Thus, first generation will look like this: \n");

		printGeneration(generationArray, *width);
	}


}


//function which saves automation to a text file.
int saveAutomation(int array[], int width)	
{
    FILE *file;
    file = fopen("savedAutomation.txt", "a");
    char newLine = '\n';

	if (array == NULL)	{
		printf("ERROR");
	}
	if (file != NULL)	{
		for (int i = 0; i < width; ++i)
		{
			if (array[i]==1)
			{
				fputs(XSQUARE, file);
			}
			else{
				fputs(WSQUARE, file);
			}
		}
	fputc(newLine, file);
	}	
	
    fclose(file);

    return 0;
}