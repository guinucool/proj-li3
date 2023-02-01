#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

char * printerUsers(void * user)
{
    char username[MAX_USER_STR];
    user_username(username, user);

    char name[MAX_USER_STR];
    user_name(name, user);

    char * res = malloc(sizeof(char) * (2 + strlen(username) + strlen(name) + intLen(user_distance(user))));
    sprintf(res,"%s;%s;%d", username, name, user_distance(user));

    return res;
}

/*void createUserList(void * element, void * list)
{
    if (user_accountStatus(element)) addOrdList(element, list, usercmp);
}*/

char ** query3(int N, Global glob)
{
    /*List ordUser = glob_userList(glob);

    if (listEmpty(ordUser)) map(glob_user(glob), nullMap, createUserList, ordUser);
    
    return listOut(ordUser, printerUsers, N);*/
}