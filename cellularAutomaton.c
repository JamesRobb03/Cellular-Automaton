/**
FUNCTIONS:
1. GET RULE(DECIMAL TO BINARY(INTEGER))
2. COMPARE(RULE, I, ARRAY) returns 1 or 0; 
3. PRINT GENERATION(HEIGHT, WIDTH, RULE)
**/
#include <stdio.h>
#include <string.h>

int compare(int rule[], int i, int array[])
{
	int c1[3] = {0,0,0};
	int c2[3] = {0,0,1};
	int c3[3] = {0,1,0};
	int c4[3] = {0,1,1};
	int c5[3] = {1,0,0};
	int c6[3] = {1,0,1};
	int c7[3] = {1,1,0};
	int c8[3] = {1,1,1};

	int compArray[3] = {array[i-1], array[i], array[i+1]};

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


void printGeneration(int array[], int width)
{
	for (int i = 0; i < width; ++i)
		{
			printf("%d", array[i]);
		}
	printf("\n");
}

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

int main(int argc, char const *argv[])
{
	int n = 30;
	int rule[8] = {0,0,0,1,1,1,1,0};
	int generationArray[n];
	int nextGen[n];
	int numGen = 2;

	//set all items in array to 0
	for (int i = 0; i < n; ++i)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}

	generationArray[n/2] = 1;

	printGeneration(generationArray, n);

	for (int i = 0; i < numGen; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			int result = compare(rule, j, generationArray);
			//printf("RESULT: %d\n", result);
			nextGen[j] = result;
		}
		swap_arrays(generationArray, nextGen, n);
		printGeneration(generationArray, n);
	}
	
	return 0;
}