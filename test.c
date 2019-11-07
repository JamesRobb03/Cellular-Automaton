#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define XSQUARE "☒"
#define WSQUARE "☐"

int power(int base, int exp)
{
    int result = 1;
    while(exp) { result *= base; exp--; }
    return result;
}

int getDecimalFromNLongBinary(int width)
{
	int output = 0;

	for (int i = 0; i < width; i++)
	{
		output = output + power(2, i);
	}

	return output;
}

void setInitState(int *pInt, int width)
{
	int maxInt = getDecimalFromNLongBinary(width);

	do
	{
		printf("Please enter initial state as an integer between %d and %d: ", 0, maxInt);
		scanf("%d", pInt);
	} while ((*pInt < 0) || (*pInt > maxInt));

	printf("You have set the initial state to be equal to %d\n", *pInt);
}

void populateWithBinary(int *initStateArr, int width)
{
	int initStateInt;

	setInitState(&initStateInt, width);

	int i;

	for( i = 0; initStateInt > 0; i++)    
	{    
		initStateArr[i] = initStateInt%2;    
		initStateInt = initStateInt/2;    
	}

	printf("\nBinary of Given Number is=");   

	for(i= i-1; i >= 0; i--)    
	{    
		printf("%d", initStateArr[i]);    
	}   

	printf("\n");

}

int main()
{	
	int width = 20;

	int initStateArr[width];

	for (int i = 0; i < width; i++)
	{
		initStateArr[i] = 0;
	}

	populateWithBinary(initStateArr, width);

	printf("array = {");
	for (int i = 0; i < width; ++i)
	{
		printf("%d, ", initStateArr[i]);
	}
	printf("}\n");

	return 0;
}

