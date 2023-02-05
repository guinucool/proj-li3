#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"
//#include "../includes/io/interactive.h"

int main(int argc, char * args[])
{	
	Global glob = createGlobal();
	if(glob == NULL)return 0;
	char str[200];

	if (argc < 2)
	{
		printf("Caminho até ao dataset: ");
		scanf("%s", str);
	}
	else
		strncpy(str, args[1], 200);

	char * truePath = (char*) malloc(sizeof(char) * (strlen(str) + 13));
	if(truePath == NULL)destroyGlobal(glob);

	strcpy(truePath, str);
	strcat(truePath, "/users.csv");
	if(!readFile(truePath, 1, glob))
	{
		free(truePath);
		truePath = NULL;
		destroyGlobal(glob);
		return 0;
	}

	strcpy(truePath, str);
	strcat(truePath, "/drivers.csv");
	if(!readFile(truePath, 2, glob))
	{
		free(truePath);
		truePath = NULL;
		destroyGlobal(glob);
		return 0;
	}

	strcpy(truePath, str);
	strcat(truePath, "/rides.csv");
	if(!readFile(truePath, 3, glob))
	{
		free(truePath);
		truePath = NULL;
		destroyGlobal(glob);
		return 0;
	}

	if (argc > 2)
	{
		if(!readFile(args[2], 0, glob))
		{
			free(truePath);
			truePath = NULL;
			destroyGlobal(glob);
			return 0;
		}
	}
	else
		if(!interactiveMode(glob))
		{
			free(truePath);
			truePath = NULL;
			destroyGlobal(glob);
			return 0;
		}

	free(truePath);
	truePath = NULL;
	destroyGlobal(glob);

	return 0;
}