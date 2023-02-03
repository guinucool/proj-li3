#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"
//#include "../includes/io/interactive.h"

int main(int argc, char * args[])
{	
	Global glob = createGlobal();
	char str[200];

	if (argc < 2)
	{
		printf("Caminho até ao dataset: ");
		scanf("%s", str);
	}
	else
		strncpy(str, args[1], 200);

	char * truePath = (char*) malloc(sizeof(char) * (strlen(str) + 13));

	strcpy(truePath, str);
	strcat(truePath, "/users.csv");
	readFile(truePath, 1, glob);

	strcpy(truePath, str);
	strcat(truePath, "/drivers.csv");
	readFile(truePath, 2, glob);

	strcpy(truePath, str);
	strcat(truePath, "/rides.csv");
	readFile(truePath, 3, glob);

	if (argc > 2)
		readFile(args[2], 0, glob);
	else
		interactiveMode(glob);

	free(truePath);
	destroyGlobal(glob);

	return 0;
}