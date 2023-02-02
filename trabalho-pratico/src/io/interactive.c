#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/io/interpreter.h"
#include "../../includes/structs/global.h"
#include "../../includes/utils.h"
#include "../../includes/io/interactive.h"


void interactiveMode(Global glob)
{   
    char str[200];
    int cmd = 0; 
    printf("Insira o comando no sequinte formato: < query id > [arg1...argN ] <page>\n");
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