#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/interpreter.h"
#include "../../includes/io/interactive.h"

void interactiveMode(Global glob)
{   
    char str[MAX_LINE], tok[4][MAX_LINE];
    printf("Insira o comando no sequinte formato: <query-id> [arg1...argN]\n");
    printf("Exemplo: 6 Lisboa 01/01/2020 31/12/2020\n");
    while(1)
    {     
        fgets(str, MAX_LINE, stdin);

        if(str[0] == '0') break;

        if(str[0] > '0' && str[0] <= '9')
        {
            tokens(str, " \n", tok);
            interCmd(tok, glob, 0);
        }
    }
}