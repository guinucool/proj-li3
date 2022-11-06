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



#endif