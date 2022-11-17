#include <stdio.h>
#include <stdlib.h>
#include "../../inc/queries/queries.h"
#include "../../inc/drivers/drivers.h"
#include "../../inc/users/users.h"
//#include "../../inc/utils/hashmap"


void query_one(Data *store, char *id) {
    // TODO: criar query one.

    printf("QUERY one:");

    // TODO: Testar id (string - utilizador ou integer - driver)

    int number = atoi(id);


    if (number != 0) {

        Driver *driver = getDriver(store->drivers, number);

        if (driver == NULL) {
            printf("No Driver to print.\n");
        } else {
            printDriver(driver);
        }
    } else {
        /*
        (User *) get(glob->users, (void *) key, equalStr, hashKey_Str, 1);


        if (user == NULL) {
            printf("No Driver to print. \n");
        } else {
            printUser(user);
        }
*/
        // TODO: como extrair um utilizador (void *get)

        // TODO: Como extrair um utilizador?

        // User *user = getU
    }

}
