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

char * printerUsers(void * user, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char username[MAX_USER_STR];
        user_username(username, user);

        char name[MAX_USER_STR];
        user_name(name, user);

        fprintf(fp,"%s;%s;%d\n", username, name, user_distance(user));
    }
    else *ignore -= 1;
}

void query3(int N, Global glob, void * fp)
{
    sortList(glob_userList(glob), usercmp);
    listOut(glob_userList(glob), printerUsers, 0, N, NULL, fp);
}