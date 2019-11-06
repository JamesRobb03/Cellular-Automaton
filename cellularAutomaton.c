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
	int c8[3] = {1,0,0};

	int compArray[3] = {array[i-1], array[i], array[i+1]};

	printf("%d %d %d", compArray[0], compArray[1], compArray[2]);

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

int main(int argc, char const *argv[])
{
	int n = 30;
	int rule[8] = {0,0,0,1,1,1,1,0};
	int generationArray[n];
	int nextGen[n];

	for (int i = 0; i < n; ++i)
	{
		generationArray[i] = 0;
		nextGen[i] = 0;
	}

	
	generationArray[n/2] = 1;

	//create next gen.
	for (int i = 1; i < n; ++i)
	{
		int result = compare(rule, i, generationArray);
		printf("RESULT: %d\n", result);
		nextGen[i] = result;
	}

	//print first gen
	for (int i = 0; i < n; ++i)
	{
		printf("%d", generationArray[i]);
	}
	printf("\n");
	//print second gen
	for (int i = 0; i < n; ++i)
	{
		printf("%d", nextGen[i]);
	}
	printf("\n");
	
	return 0;
}