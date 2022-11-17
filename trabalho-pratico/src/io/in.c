#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/io/in.h"
#include "../../inc/io/read.h"
#include "../../inc/structs/user.h"
#include "../../inc/structs/ride.h"
#include "../../inc/structs/city.h"
#include "../../inc/structs/date.h"
#include "../../inc/utils.h"
#include "../../inc/queries.h"

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
 * 
 * @param mode O tipo de informação que irá ser lido no ficheiro escolhido.
 * 
 * @param glob A variável global que segura, ou vai segurar,
 *             a informação relevante à execução do programa.
 */
void readFile(char * path, char mode, Global * glob)
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

        switch (mode)
        {
            case 0:
                interCmd(args, glob);
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
    }
}

int main()
{
    Global * glob = createGlobal();

    readFile("../../db/users.csv", 1, glob);
    readFile("../../db/rides.csv", 3, glob);

    short date[]= {30, 4, 2016};
    short date1[]= {1, 5, 2016};

    //char * str = "MiTeixeira";

    Date * data = (Date*) get(glob->dates, (void *) date, equal_date, hashKey_date, 1);
    //HashmapNode * dates = betweenDates(date, date1, 'r', glob);
    //HashmapNode * temp = dates;

    printf("%d/%d/%d %p %c\n", (int)data->date[0], (int)data->date[1], (int)data->date[2], data->keyRef, data->type);

    //nextDay(date);

    printf("%d/%d/%d\n", (int)date[0], (int)date[1], (int)date[2]);
    /*while (temp != NULL)
    {
        Date * tmpCity = (Date *) temp->data;
        printf("%d/%d/%d %p\n", tmpCity->date[0], tmpCity->date[1], tmpCity->date[2], tmpCity->keyRef);
        temp = temp->next;
    }*/

    printf("%.3f", (float)query6("Braga", date, date1, glob));
}