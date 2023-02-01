#include <stdio.h>
#include "../../includes/io/interpreter.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/interactive.h"


void interactiveMode(Global glob)
{   
    char str[MAX_LINE];
    int cmd = 0;
    printf("Insira o comando no sequinte formato: < query id > [arg1...argN ]\n");
    printf("Exemplo: 6 Lisboa 01/01/2020 31/12/2020");
    while(1)
    {     
        scanf("%s\n",str);
        if(str[0] != '0')break;
        cmd++;
        interCmd(str,glob,cmd);
    }
}