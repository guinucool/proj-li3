#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _MAX_LINE_ 150

void readCatalogue(char * path, char ctl)
{
    char * true_path = malloc(sizeof(char) * 22);

    strcpy(true_path, path);

    switch (ctl)
    {
        case 0:
            strcat(true_path, "/users.csv");
            break;

        case 1:
            strcat(true_path, "/drivers.csv");
            break;

        case 2:
            strcat(true_path, "/rides.csv");
            break;
    }

    FILE * catalogue = fopen(true_path, "r");
    char * line = malloc(sizeof(char) * _MAX_LINE_);
    int size = 0;

    fgets(line, _MAX_LINE_, catalogue);

    for (int i = 0; line[i] != '\n'; i++)
        if(line[i] == ';' || line[i+1] == '\n') size++;

    char * holder = malloc(sizeof(char));
    char out[size][_MAX_LINE_];

    while (fgets(line, _MAX_LINE_, catalogue) != NULL)
    {
        int f = 0, j = 0;

        for (int i = 0; line[i] != '\n'; i++)
        {
            holder[i-j] = line[i];

            if (line[i+1] == ';' || line[i+1] == '\n')
            {
                holder[i-j+1] = '\0';
                strcpy(out[f], holder);
                f++;
                if (line[i+1] != '\n') i++;
                j = i+1;
            }
        }
    }
}

int main()
{
    readCatalogue("../../db", 0);

    /*FILE* data = fopen("../../db/users.csv", "r");
    int loop = 1;
    char *line = malloc(sizeof(char**) * _MAX_LINE_);

    fgets(line, _MAX_LINE_, data);

    while(loop)
    {   
        line[0] = '\0';

        fgets(line, _MAX_LINE_, data);
        printf("%s", line);

        if (line[0] == '\0') loop = 0;
    }

    return(0); */
}