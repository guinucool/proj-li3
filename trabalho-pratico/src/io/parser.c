#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/global.h"
#include "../../includes/io/interpreter.h"
#include "../../includes/io/parser.h"

/// @brief A função readFile lê e importa a informação de um ficheiro.
/**
 * A função readFile, através do path recebido, abre o ficheiro desejado e,
 * linha a linha, irá dando output da sua informação para um array de strings.
 * 
 * Assim sendo, esta terá de saber qual o tipo de informação contida no ficheiro
 * para escolher o melhor separador de informação (; no caso de ficheiros csv,
 * ou espaço no caso de comandos).
 * 
 * Uma vez convertida a informação, esta é enviada para a respetiva função de interpretação.
 * 
 * @param path O caminho para a localização ficheiro a ser lido.
 * @param mode O tipo de informação que irá ser lido no ficheiro escolhido.
 * @param glob A variável global que segura, ou vai segurar, a informação relevante à execução do programa.
 */
void readFile(char * path, char mode, Global glob)
{
    FILE * file = fopen(path, "r");
    char line[MAX_LINE];
    char cut = ' ';
    int size = 4;

    if (mode != 0)
    {
        fgets(line, MAX_LINE, file);

        for (int i = 0; line[i] != '\n'; i++)
            if(line[i] == ';' || line[i+1] == '\n') size++;

        cut = ';';
    }

    char * holder = (char *) malloc(sizeof(char) * MAX_LINE);
    char args[size][MAX_LINE];
    int cmd = 1;

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

        switch (mode)
        {
            case 0:
                interCmd(args, glob, cmd);
                break;

            case 1:
                interUser(args, glob);
                break;

            case 2:
                interDriver(args, glob);
                break;

            case 3:
                interRide(args, glob);
                break;
        }

        cmd++;
    }

    free(holder);
    fclose(file);
}