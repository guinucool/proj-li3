#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/io/interpreter.h"
#include "../../includes/structs/global.h"
#include "../../includes/utils.h"
#include "../../includes/structs/list.h"
#include "../../includes/io/page.h"


void page(List list, void (*printer)(void*,void*,int*,FILE*), int pos, int N, void * second)
{
    
    int j = pos, num;
    char cmd[200];

    while(1)
    {
        printf("Insira o nº da pagina pretendida ou as letras 'a' (pagina anterior) e 's' (pagina seguinte)\n");
        scanf("%s",cmd);
        if(isNumber(cmd,'i'))
        {   
            num = atoi(cmd);
            if(num > (N/10))j = (N/10)-1;
            else if(num < 0)printf("Imput inválido\n");
            else if(num == 0)break;
            else j = (num-1);
        }
        else if(strlen(cmd) == 1)
        {
            if(!(strcmp(cmd,"a")) && j - 1 >= 0 )j -= 1;
            else if(!(strcmp(cmd,"s")) && j + 2 <= N ) j += 1;
            else printf("Imput inválido\n");
        }
        else printf("Imput inválido\n");

        listOut(list,printer,j,N,second,NULL);

    }
    
}