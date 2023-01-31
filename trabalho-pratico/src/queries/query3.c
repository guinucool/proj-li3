#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h";
#include "../../includes/structs/user.h";
#include "../../includes/structs/linkedlist.h";
#include "../../includes/structs/hashmap.h";
#include "../../includes/structs/global.h";

void createUserList(void * element, void * list)
{
    list = addOrdList(element, list, usercmp);
}

char ** query3(int N, Global glob)
{
    LinkedList ordUser = glob_userList(glob);

    if (!ordUser) map(glob_user(glob), nullMap, createUserList, ordUser);

    char ** res = malloc(sizeof(char*) * N);

    for (int i = 0; i < N && ordUser; i++)
    {
        User user = list_element(ordUser);

        char username[MAX_USER_STR];
        user_username(username, user);

        char name[MAX_USER_STR];
        user_name(name, user);

        res[i] = malloc(sizeof(char) * (2 + strlen(username) + strlen(name) + intLen(user_distance(user))));
        sprintf(res[i],"%s;%s;%d", username, name, user_distance(user));
    }
    
    return res;
}