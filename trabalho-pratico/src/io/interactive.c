#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/interpreter.h"
#include "../../includes/io/interactive.h"

/// @brief A função interactiveMode fornece ao programa uma interface de utilizador interativa.
/**
 *  A função apresenta as possibilidades de comandos a serem executados e começa um ciclo infinito.
 *  De seguida, é pedido um imput de um comando ao utilizador e após a seleção do comando pretendido,
 *  o comando é executado. Caso seja inserido em primeiro lugar o caractere '0' o cilco quebra 
 *  e a função termina.
 * 
 * @param glob A global a ser considerada para os cálculos estatísticos.
*/
void interactiveMode(Global glob)
{   
    char str[MAX_LINE], tok[4][MAX_LINE];
    while(1)
    {
        fgets(str, MAX_LINE, stdin);

        if(str[0] == '0') break;

        if(str[0] > '0' && str[0] <= '9')
        {
            tokens(str, " \n", tok);
            interCmd(tok, glob, 0);
        }
        printf("Insira o comando no sequinte formato: <query-id> [arg1...argN]\n");
        printf("Query 1 : 1 <ID>\n");
        printf("Query 2 : 2 <N>\n");
        printf("Query 3 : 3 <N>\n");
        printf("Query 4 : 4 <city>\n");
        printf("Query 5 : 5 <data A> <data B>\n");
        printf("Query 6 : 6 <city> <data A> <data B>\n");
        printf("Query 7 : 7 <N> <city>\n");
        printf("Query 8 : 8 <gender> <X>\n");
        printf("Query 9 : 9 <data A> <data B>\n");
        printf("Insira '0' para terminar o modo interativo\n");
    }
}