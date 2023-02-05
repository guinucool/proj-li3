#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/list.h"
#include "../../includes/io/page.h"

/// @brief A função page imprime outputs grandes por páginas.
/**
 *  A função page imprime outputs grandes por páginas, usando a listOut
 *  para fazer as impressões.
 * 
 *  Assim sendo, a função page irá apenas decidir a página que deve
 *  imprimir através do input do utilizador, não permitindo o utilizador
 *  escolher páginas inexistentes ou inválidas.
 * 
 *  @param list A lista de resultados a ser impressa.
 * 
 *  @param printer A função que define a forma como deve ser impresso cada elemento da lista.
 * 
 *  @param N O top número de elementos a ser impresso da lista.
 * 
 *  @param second O segundo argumento da função print (caso exista).
 */
void page(List list, void (*printer)(void*,void*,int*,FILE*), int N, void * second)
{
    char cmd[MAX_LINE], * token;
    int j = 1, max;

    if (N % PAGES == 0) max = (N / PAGES);
    else max = (N / PAGES) + 1;

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

        if(j > max) j = max;

        printf("Página %d-%d:\n", j, max);
        listOut(list, printer, j, N, second, NULL);
    }
}