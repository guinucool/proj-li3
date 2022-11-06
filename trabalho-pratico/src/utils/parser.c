#include <stdio.h>
#include <stdlib.h>
#define _MAX_LINE 1000

int main()
{
    FILE* data = fopen("../../db/users.csv", "r");
    int loop = 1;
    char *line = malloc(sizeof(char**) * _MAX_LINE);

    fgets(line, _MAX_LINE, data);

    while(loop)
    {   
        line[0] = '\0';

        fgets(line, _MAX_LINE, data);
        printf("%s", line);

        if (line[0] == '\0') loop = 0;
    }

    return(0); 
}