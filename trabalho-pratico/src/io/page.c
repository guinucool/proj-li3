#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/page.h"


void page(List list, void (*printer)(void*,void*,int*,FILE*), int N, void * second)
{
    char cmd[MAX_LINE], * token;
    int j = 1;

    while(1)
    {
        printf("Insira o nº da pagina pretendida ou as letras 'a' (pagina anterior) e 's' (pagina seguinte):\n");

        fgets(cmd, MAX_LINE, stdin);
        system("clear");

        if (cmd[0] != '\n')
        {
            token = strtok(cmd, "\n");
            strncpy(cmd, token, MAX_LINE);
        }

        if (isNumber(cmd,INT))
            j = atoi(cmd);
        
        if(j < 1)
            break;
        
        if(!isNumber(cmd, INT))
        {
            if(!(strcmp(cmd,"a")) && (j - 1) > 0) j--;
            else if(!strcmp(cmd,"s")) j++;
            else printf("ERRO: Input inválido!\n");
        }

        if(j * PAGES >= N)
        {
            if (N % PAGES == 0) j = (N / PAGES);
            else j = (N / PAGES) + 1;
        }

        printf("Página %d:\n", j);
        listOut(list, printer, j, N, second, NULL);
    }
}