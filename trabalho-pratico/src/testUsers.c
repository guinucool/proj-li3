#include <stdio.h>
#include <string.h>

#include "../inc/users/users.h"
#include "../inc/users/user.h"

int equal(void* key1, void* key2){
    return !(strcmp(key1, key2));
}

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


    putUser(users, user1);
    putUser(users, user2);

    printf("Tamanho dos users = %d\n", users->size);

    User* u = getUser(users, "JorBranco31", equal);

    printUser(u);


    destroyUsers(users);
    destroyUser(user1);
    destroyUser(user2);

    return 0;
}

