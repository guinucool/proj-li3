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
    char ** tokensImp;
    printf("Insira o comando no sequinte formato: < query id > [arg1...argN ] <page>\n");
    printf("Exemplo: 6 Lisboa 01/01/2020 31/12/2020\n");
    while(1)
    {     
        scanf("%s%*c",str);
        if(str[0] == '0')break;
        else if(str[0] > '0' && str[0] <= '9')
        {
        tokensImp = tokens(str," ");
        interCmd(tokensImp,glob,0);
        free(tokensImp);
        }
    }
}