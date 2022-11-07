#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ""
#define MAX_LINE 200

void readAll(char * path)
{
    read(path, 0);
    read(path, 1);
    read(path, 2);
}

void read(char * path, char ctl)
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
    char * line = malloc(sizeof(char) * MAX_LINE);
    int size = 0;

    fgets(line, MAX_LINE, catalogue);

    for (int i = 0; line[i] != '\n'; i++)
        if(line[i] == ';' || line[i+1] == '\n') size++;

    char * holder = malloc(sizeof(char));
    char out[size][MAX_LINE];

    while (fgets(line, MAX_LINE, catalogue) != NULL)
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