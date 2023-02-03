#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief Função que recebe a informação do user e a imprime no ficheiro de output.
/// @param user User a ser impresso.
/// @param fp Ficheiro de output.
void printUser(void * user, FILE * fp)
{
    char name[MAX_USER_STR];
    user_name(name, user);

    if (fp) fprintf(fp, "%s;%c;%d;%0.3f;%d;%0.3f\n", name, user_gender(user), user_age(user), user_averageScore(user), user_rides(user), user_moneySpent(user));
    else printf("%s;%c;%d;%0.3f;%d;%0.3f\n", name, user_gender(user), user_age(user), user_averageScore(user), user_rides(user), user_moneySpent(user));
}

/// @brief Função que recebe a informação do driver e a imprime no ficheiro de output.
/// @param driver Driver a ser impresso.
/// @param fp Ficheiro de output.
void printDriver(void * driver, FILE * fp)
{
    char name[NAME_STR_SIZE];
    driver_name(name, driver);

    if (fp) fprintf(fp, "%s;%c;%d;%0.3f;%d;%0.3f\n", name, driver_gender(driver), driver_age(driver), driver_score(driver, NULL), driver_rides(driver), driver_moneyReceived(driver));
    else printf("%s;%c;%d;%0.3f;%d;%0.3f\n", name, driver_gender(driver), driver_age(driver), driver_score(driver, NULL), driver_rides(driver), driver_moneyReceived(driver));
}

/// @brief A função query1 lista o resumo do utilizador desejado seja user ou driver.
/**
 *  A função começa por aferir se o id fornecido é de um user ou de um driver, 
 *  de seguida é adquirida a estrutura corresponde ao utilizador e são retiradas dela
 *  a informação desejada. Por fim, a informação é adicionada ap ficheiro de output. 
 * 
 * @param id Id fornecido.
 * 
 * @param glob Estrutura de dados global a ser atualizada.
 * 
 * @param fp Ficheiro de output.
*/
void query1(char * id, Global glob, FILE * fp)
{
    if (isNumber(id, INT))
    {
        int key = atoi(id);

        Driver driver = get(glob_driver(glob), &key, equal, hashKey_Int);
        if (driver && driver_accountStatus(driver)) printDriver(driver, fp);
    }
    else
    {
        User user = get(glob_user(glob), id, equal_str, hashKey_Str);
        if (user && user_accountStatus(user)) printUser(user, fp);
    }
}
