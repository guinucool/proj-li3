#ifndef _USER_H_ 
#define _USER_H_

#define MAX_USER_STR 50

/// \struct Estrutura que define as variáveis do tipo User.
typedef struct USER
{
    char username[MAX_USER_STR];    //!< Username do user
    char name[MAX_USER_STR];        //!< Nome do user
    char gender;                    //!< Genero do user
    short int birth_date[3];        //!< Data de nascimento do user no formato {dia,mês,ano}
    short int account_creation[3];  //!< Data de criação de conta do user no formato {dia,mês,ano}
    char pay_method[MAX_USER_STR];  //!< Metodo de pagamento que o user usa
    char account_status;            //!< Status da conta ('a' para active 'i' para inactive)
}User;

User* userCreate(char data[][200]);
void destroyUser(User * user);
void printUser(User * user);

#endif