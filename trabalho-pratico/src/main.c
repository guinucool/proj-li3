#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/utils.h"
#include "../includes/structs/hashmap.h"
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"

int main(int argc, char * args[])
{	
	if (argc > 2)
	{
		Global glob = createGlobal();
		char * truePath = (char*) malloc(sizeof(char) * (strlen(args[1]) + 13));

		strcpy(truePath, args[1]);
		strcat(truePath, "/users.csv");
		readFile(truePath, 1, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/drivers.csv");
		readFile(truePath, 2, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/rides.csv");
		readFile(truePath, 3, glob);

		debugPrintHashmap(glob_ride(glob), null, null);

		//printGlobal(glob);

		/*readFile(args[2], 0, glob);

		//query1("MRibeiro33", glob);

		//char gender = 'M';

		//query8(&gender, 1, glob);

		destroyGlobal(glob);*/
	}

	return(0);
}