#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/page.h"
#include "../../includes/queries.h"

/// @brief Função que recebe a informação do driver e a imprime no ficheiro de output.
/// @param user User a ser impresso.
/// @param null Placeholder para que listOut resulte.
/// @param ignore Número de outputs que vai ter que ignorar.
/// @param fp Ficheiro de output.
void printerUsers(void * user, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char username[MAX_USER_STR];
        user_username(username, user);

        char name[MAX_USER_STR];
        user_name(name, user);

        if(fp) fprintf(fp,"%s;%s;%d\n", username, name, user_distance(user));
        else printf("%s;%s;%d\n", username, name, user_distance(user));
    }
    else *ignore -= 1;
}

/// @brief Esta função lista os N condutores com maior distância viajada.
/**
 *  A função começa por usar a função de ordem superior sortList que irá ordenar 
 *  a lista de condutores pela avaliação media através da função usercmp.
 *  
 *  Tendo a lista ordenada é chamada a função de ordem superior listOut que irá 
 *  imprimir os N primeiros elementos da lista.
 * 
 *  @param N Número de condutores a ser impressos.
 * 
 *  @param glob Estrutura de dados global a ser atualizada.
 * 
 *  @param fp Ficheiro de output.
*/
void query3(int N, Global glob, FILE * fp)
{
    sortList(glob_userList(glob), usercmp, NULL);
    
    if (fp) listOut(glob_userList(glob), printerUsers, 0, N, NULL, fp);
    else page(glob_userList(glob), printerUsers, N, NULL);
}