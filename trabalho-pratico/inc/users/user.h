#ifndef _USER_H_ 
#define _USER_H_

#define MAX_USER_STR 50


typedef struct USER
{
    char* username;
    char* name;
    char gender;
    short int* birth_date; // {day,month,year}
    short int* account_creation; // {day,month,year}
    char* pay_method;
    char account_status; // 'a' para active 'i' para inactive
}User;

User* userCreate(char** data_str);
short int* str_to_int(char* str);
void destroyUser(User* user);
void printUser(User* user);

#endif