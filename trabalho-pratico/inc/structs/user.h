#ifndef _USER_H_ 
#define _USER_H_

#define MAX_USER_STR 50


typedef struct USER
{
    char username[MAX_USER_STR];
    char name[MAX_USER_STR];
    char gender;
    short int birth_date[3]; // {day,month,year}
    short int account_creation[3]; // {day,month,year}
    char pay_method[MAX_USER_STR];
    char account_status; // 'a' para active 'i' para inactive
}User;

User* userCreate(char data[][200]);
void str_to_int(char* str,short int* date);
int compStr(void* s1,void* s2);
void destroyUser(User* user);
void printUser(User* user);

#endif