#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>


#define XSQUARE "☒"
#define WSQUARE "☐"

void setRule(int *pInt)
{
	do
	{
		printf("Please enter rule between %d and %d: ", 0, 255);
		scanf("%d", pInt);
	} while ((*pInt < 0) || (*pInt > 255));

	printf("You have set the rule to be equal to %d\n", *pInt);
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
		else if ((*pInt >= 3) && (*pInt < (w.ws_col/2)))
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

int main()
{	
	int ruleNum; 

	int rule[8] = {0};

	setRule(&ruleNum);

	printf("\n");

	// print terminak widow width

	int gridWidth;
    
	setWidht(&gridWidth);

	printf("%d and %d\n", ruleNum, gridWidth);

	return 0;
}

