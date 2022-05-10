#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ERROR -1

typedef struct IntPair
{
	int a;
	int b;
} IntPair;

int CheckTimeInput(const char* inputString)
{
	if (strlen(inputString) != 5)
		return ERROR;

	if (!(inputString[0] >= '0' && inputString[0] <= '2'))
		return ERROR;

	if (inputString[0] == '0' || inputString[0] == '1')
	{
		if (!isdigit(inputString[1]))
			return ERROR;
	}

	if (inputString[0] == '2')
	{
		if (!(inputString[1] >= '0' && inputString[1] <= '3'))
			return ERROR;
	}

	if (inputString[2] != ':')
		return ERROR;

	if (!(inputString[3] >= '0' && inputString[3] <= '5'))
		return ERROR;

	if (!isdigit(inputString[4]))
		return ERROR;

	if (inputString[5] != '\0')
		return ERROR;

	return 0;
}

int TimeInput(int* output, bool checkFormat)
{
	char inputString[6];
	scanf("%s", inputString);

	if (checkFormat && CheckTimeInput(inputString) < 0)
		return ERROR;

	int hours = (inputString[0] - '0') * 10 + (inputString[1] - '0');
	int minutes = (inputString[3] - '0') * 10 + (inputString[4] - '0');
	*output = hours * 60 + minutes;

	return 0;
}

int UserInput(int* n, IntPair** visitorTimes, int* timeToCheck)
{
	scanf("%d", n);

	if (*n <= 0)
		return ERROR;

	*visitorTimes = (IntPair*)calloc(*n, sizeof(IntPair));
	if (*visitorTimes == NULL)
	{
		printf("MEM_GRESKA");
		return ERROR;
	}

	int i;
	for (i = 0; i < *n; i++)
	{
		IntPair* currentPair = *visitorTimes + i;

		if (TimeInput(&(currentPair->a), true) < 0)
			return ERROR;
		if (TimeInput(&(currentPair->b), true) < 0)
			return ERROR;

		if (currentPair->a >= currentPair->b)
			return ERROR;
	}

	TimeInput(timeToCheck, false);

	return 0;
}

int main()
{
	int n, timeToCheck;
	IntPair* visitorTimes = NULL;

	if (UserInput(&n, &visitorTimes, &timeToCheck) < 0)
	{
		free(visitorTimes);
		return 0;
	}
	
	int i, checkCounter = 0;
	for (i = 0; i < n; i++)
	{
		int stayTime = visitorTimes[i].b - visitorTimes[i].a;
		printf("%02d:%02d", stayTime / 60, stayTime % 60);

		if (i < n - 1)
			printf(" ");

		if (timeToCheck >= visitorTimes[i].a && timeToCheck <= visitorTimes[i].b)
			checkCounter++;
	}

	printf("\n%d", checkCounter);
	
	free(visitorTimes);
	return 0;
}