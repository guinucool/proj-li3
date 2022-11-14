#include <stdio.h>
#include <string.h>

#include "../inc/users/users.h"
#include "../inc/users/user.h"

int main() {

    char* test1[] = {
        "MiTeixeira",
        "Miguel Teixeira",
        "M",
        "03/09/1958",
        "05/11/2017",
        "cash",
        "active"
    };

    char* test2[] = {
        "JorBranco31",
        "Jorge Branco",
        "M",
        "05/10/1992",
        "18/07/2020",
        "credit_card",
        "active"
    };

    Users* users = createUsers();
    User* user1 = userCreate(test1);
    User* user2 = userCreate(test2);
        
    printf("Foram criados os users: ");
    printUser(user1);
    printUser(user2);


    put(users,user1->username,user1,hashstr_get);
    put(users,user2->username,user2,hashstr_get);

    User* u = get(users, "JorBranco31", compStr, hashstr_get);

    printUser(u);


    destroyUsers(users);
    destroyUser(user1);
    destroyUser(user2);

    return 0;
}

