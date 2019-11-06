/**
FUNCTIONS:
1. GET RULE(DECIMAL TO BINARY(INTEGER))
2. COMPARE(RULE, I, ARRAY) returns 1 or 0; 
3. PRINT GENERATION(HEIGHT, WIDTH, RULE)
**/

#include <stdio.h>
#include <string.h>

//function used to compare 3 items in the generation array to the rule set. Returns an output of 1 or 0 depending on the rule
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
		return rule[7];
	}
	else if (memcmp(c2, compArray, sizeof(c1))==0)
	{
		return rule[6];
	}
	else if (memcmp(c3, compArray, sizeof(c1))==0)
	{
		return rule[5];
	}
	else if (memcmp(c4, compArray, sizeof(c1))==0)
	{
		return rule[4];
	}
	else if (memcmp(c5, compArray, sizeof(c1))==0)
	{
		return rule[3];
	}
	else if (memcmp(c6, compArray, sizeof(c1))==0)
	{
		return rule[2];
	}
	else if (memcmp(c7, compArray, sizeof(c1))==0)
	{
		return rule[1];
	}
	else if (memcmp(c8, compArray, sizeof(c1))==0)
	{
		return rule[0];
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
			printf("%d", array[i]);
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
int createRule(int ruleNum)
{
	//convert integer into string.
	//sets rule to string index
	//returns rule


}

int main(int argc, char const *argv[])
{
	int n = 11;
	int rule[8] = {0,0,0,1,1,1,1,0};
	int generationArray[n];
	int nextGen[n];
	int numGen = 9;

	//printf("Please enter a choice\n");
	//printf("1.Print preset automaton\n");
	//printf("2. \n");

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
		for (int j = 1; j < n; ++j)
		{
			int result = compare(rule, j, generationArray, n);
			//printf("RESULT: %d\n", result);
			nextGen[j] = result;
		}
		swap_arrays(generationArray, nextGen, n);
		printGeneration(generationArray, n);
	}
	
	return 0;
}

//array[decimal] = 1
