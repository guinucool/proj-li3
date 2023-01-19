#ifndef _USER_H_ 
#define _USER_H_

#define MAX_USER_STR 50

typedef struct _USER_ User;
typedef short Date[3];

User* userCreate(char data[][200]);
void destroyUser(User * user);
void printUser(User * user);
void user_Str(char * dest, User * user, char mode);
char user_Char(User * user, char mode);
void user_Date(Date dest, User * user, char mode);

#endif