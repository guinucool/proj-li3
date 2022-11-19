#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/io/in.h"

int main(int argc, char * args[])
{	
	if (argc > 2)
	{
		Global * glob = createGlobal();
		char * truePath = (char*) malloc(sizeof(char) * 30);

		strcpy(truePath, args[1]);
		strcat(truePath, "/users.csv");
		readFile(truePath, 1, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/drivers.csv");
		readFile(truePath, 2, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/rides.csv");
		readFile(truePath, 3, glob);

		//printGlobal(glob);

		readFile(args[2], 0, glob);
	}

	return(0);
}