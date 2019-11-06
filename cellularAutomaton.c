/**
FUNCTIONS:
1. GET RULE(DECIMAL TO BINARY(INTEGER))
2. COMPARE(RULE, I, ARRAY) returns 1 or 0; 
3. PRINT GENERATION(HEIGHT, WIDTH, RULE)
**/

#include <stdio.h>
#include <string.h>

#define WSQUARE "\u2610"
#define XSQUARE "\u2612"


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

//function which converts integer, into binary number and changes binary number into list of integers.
int createRule(int *array, int number)
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

void print(int array[])
{
	for (int i = 7; i >= 0; --i)
	{
		printf("%d\n", array[i]);
	}
}

//Preset generation
void genPreset()
{
	printf("\n");
	printf("Using rule 30\n");
	printf("Using width 43\n");
	printf("displaying 22 generations\n");
	printf("\n");

	int n = 43;
	int rule[8] = {0,1,1,1,1,0,0,0};
	int generationArray[n];
	int nextGen[n];
	int numGen = 21;

	//set all items in array to 0
	for (int i = 0; i < n; ++i)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}
	//sets centre of array to 1
	generationArray[n/2] = 1;

	print(rule);

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
	int width;
	int numberGenerations;
	int ruleInteger;
	int ruleSet[8] = {0,0,0,0,0,0,0,0};
	int generationArray[width];
	int nextGen[width];

	//User Input
	printf("Please enter the rule you wish to use: ");
	scanf("%d", &ruleInteger);
	printf("Please enter a width: ");
	scanf("%d", &width);
	printf("Please enter the amount of generations to display: ");
	scanf("%d", &numberGenerations);

	numberGenerations = numberGenerations -1;
	//Get input for starting generation

	//populate arrays
	//set all items in array to 0
	for (int i = 0; i < width; ++i)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}

	//set rule
	createRule(ruleSet, ruleInteger);
	print(ruleSet);

	generationArray[width/2] = 1;
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

int main(int argc, char const *argv[])
{
	int userOptions;
	while(1){
		printf("Please enter a choice\n");
		printf("1.Generate preset automaton\n");
		printf("2.Generate your own \n");
		printf("0. Exit\n");
		scanf("%d", &userOptions);
		if (userOptions == 1)
		{
			genPreset();
		}
		else if(userOptions == 2)
		{
			userGeneration();
		}
		else if (userOptions == 0)
		{
			break;
		}
		else{
			printf("Please try again and enter a valid option\n");
		}
	}
	return 0;
}

