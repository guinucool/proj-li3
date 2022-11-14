#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/io/in.h"

void readFile(char * path, char mode, Global * glob)
{
    FILE * file = fopen(path, "r");
    char line[MAX_LINE];
    char cut = ' ';
    int size = 3;

    if (mode != 0)
    {
        fgets(line, MAX_LINE, file);

        for (int i = 0; line[i] != '\n'; i++)
            if(line[i] == ';' || line[i+1] == '\n') size++;

        cut = ';';
    }

    char * holder = (char *) malloc(sizeof(char));
    char args[size][MAX_LINE];

    while (fgets(line, MAX_LINE, file) != NULL)
    {
        int f = 0, j = 0;

        for (int i = 0; line[i] != '\n'; i++)
        {
            holder[i-j] = line[i];

            if (line[i+1] == cut || line[i+1] == '\n')
            {
                holder[i-j+1] = '\0';
                strcpy(args[f], holder);
                f++;
                if (line[i+1] != '\n') i++;
                j = i+1;
            }
        }

        printf("%s", line);
    }
}