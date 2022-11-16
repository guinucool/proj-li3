#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../inc/users/user.h"
#include "../../inc/utils/utilities.h"



User* userCreate(char** data){
    char* username = data[0];
    char* name = data[1];
    User* user = (User*) malloc(sizeof(User));
    strncpy(user->username, username, MAX_USER_STR);
    strncpy(user->name, name, MAX_USER_STR);
    user->gender = data[2][0];
    stringToDate(data[3],user->birth_date);
    stringToDate(data[4],user->account_creation);
    user->pay_method = data[5];
    user->account_status = data[6][0];

    return user;
}

int compStr(void* s1,void* s2){
    return !(strcmp(s1,s2));
}

void destroyUser(User* user){
    free(user);
}

void printUser(User* user){
    printf("%s,\n%s,\n%c,\n%d/%d/%d,\n%d/%d/%d,\n%s,\n%c\n",
    user->username,user->name,user->gender,user->birth_date[0],user->birth_date[1],user->birth_date[2],user->account_creation[0],user->account_creation[1],user->account_creation[2],user->pay_method,user->account_status);
}