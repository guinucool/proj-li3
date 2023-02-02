#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/io/interpreter.h"
#include "../../includes/structs/global.h"
#include "../../includes/utils.h"
#include "../../includes/io/interactive.h"


void page(char * str[200], int N)
{
    int i, j = 0, num;
    char cmd[200];
    while(1)
    {
        printf("Pagina %d:\n",j+1);
        for (i = j*10; i < j*10 + 10 && i < N; i++)
        {
            printf("%s\n",str[i]);
        }
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

    }
    
}

void interactiveMode(Global glob)
{   
    char str[200];
    int cmd = 0; 
    printf("Insira o comando no sequinte formato: < query id > [arg1...argN ]\n");
    printf("Exemplo: 6 Lisboa 01/01/2020 31/12/2020\n");
    while(1)
    {     
        scanf("%s%*c",str);
        if(str[0] == '0')break;
        if(str[0] == '9')page(str,strlen(str));
        cmd++;

        interCmd(str,glob,cmd);
    }
}