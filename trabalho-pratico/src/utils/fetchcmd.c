#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/utils/cmd.h"

Command createCmd(int id, char arg[ARG_MAX][PRM_MAX])
{
    Command cmd;

    cmd.id = id;
    for (int i = 0; i < ARG_MAX; i++)
        strcpy(cmd.args[i], arg[i]);
    
    return(cmd);
}

void fetchCmd(char * path)
{
    FILE * input = fopen(path, "r");
    char * line = malloc(sizeof(char) * PRM_MAX);
    char * holder = malloc(sizeof(char));
    char args[ARG_MAX][PRM_MAX];

    while (fgets(line, PRM_MAX, input) != NULL)
    {
        int f = 0, j = 2, id = 0;

        id = line[0] - 48;

        for (int i = 2; line[i] != '\n'; i++)
        {
            holder[i-j] = line[i];

            if (line[i+1] == ' ' || line[i+1] == '\n')
            {
                holder[i-j+1] = '\0';
                strcpy(args[f], holder);
                f++;
                if (line[i+1] != '\n') i++;
                j = i+1;
            }
        }

        Command cmd = createCmd(id, args);
    }
}