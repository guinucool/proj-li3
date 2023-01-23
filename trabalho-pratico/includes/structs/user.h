#ifndef _USER_H_ 
#define _USER_H_

#define MAX_USER_STR 50

#define MALE 'M'
#define FEMALE 'F'

#define INACTIVE 0
#define ACTIVE 1

#define CASH 0
#define CREDIT_CARD 1
#define DEBIT_CARD 2

#define METHODS_SIZE 3
extern char payment_methods[METHODS_SIZE][MAX_USER_STR];

#define STATUS_SIZE 2
extern char account_statuses[STATUS_SIZE][MAX_USER_STR];

// Estrutura
typedef struct _USER_ *User;

// Tratamentos
User userCreate(char * username, char * name, char gender, short age, Date account_creation, char pay_method, char account_status);
void userUpdate(User user, int score, double money_spent, int distance, Date date);
void destroyUser(User user);
void debugPrintUser(User user);
User parseUser(char data[7][200]);
int usercmp(User user1, User user2);

// Devoluções
void user_username(char * dest, User user);
void user_name(char * dest, User user);
char user_gender(User user);
short user_age(User user);
void user_accountCreation(Date dest, User user);
char user_accountStatus(User user);
double user_averageScore(User user);
int user_rides(User user);
double user_moneySpent(User user);
int user_distance(User user);

#endif