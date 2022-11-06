#include <stdio.h>
#include <string.h>

#include "../../inc/users/user.h"



User* userCreate(char* data_str){

    User* user = (User*) malloc(sizeof(User));
    char* tables[7] = string_division(data_str);
    strncpy(user->username, tables[0], MAX_USER_STR);
    strncpy(user->name, tables[1], MAX_USER_STR);
    user->gender = tables[2][0];
    user->birth_date = str_to_int(tables[3]);
    user->account_creation = str_to_int(tables[4]);
    user->pay_method = tables[5];
    user->account_status = tables[6][0];

    return user;
}

short int* str_to_int(char* str){
    
    short int date[3];

    date[0] = 10*(str[0]-48)+(str[1]-48);
    date[1] = 10*(str[3]-48)+(str[4]-48);
    date[2] = 1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48);

    return date;
}

char* string_division(char* data_str){

    char* tables[7];
    short int i;

    for ( i = 0; i < 7; i++)
    {
        tables[1] = strtok(data_str,';');
    }

    return tables;
    
}