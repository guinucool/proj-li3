#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/structs/user.h"
#include "../../includes/structs/date.h"

/// \struct Estrutura que define as variáveis do tipo User.
typedef struct _USER_
{
    char username[MAX_USER_STR];    //!< Username do user
    char name[MAX_USER_STR];        //!< Nome do user
    char gender;                    //!< Genero do user
    Date birth_date;                //!< Data de nascimento do user no formato {dia,mês,ano}
    Date account_creation;          //!< Data de criação de conta do user no formato {dia,mês,ano}
    char pay_method[MAX_USER_STR];  //!< Metodo de pagamento que o user usa
    char account_status;            //!< Status da conta ('a' para active 'i' para inactive)
    int score;                      //!< Avaliação total do utilizador
    int rides;                      //!< Número de viagens do utilizador
    double money_spent;             //!< Total gasto em viagens pelo utilizador
    int distance;                   //!< Distancia total percorrida pelo utilizador
}User;

/// @brief A função userCreate cria uma variável do tipo User.
/**
 * A função userCreate cria uma variável do tipo User, alocando
 * o espaço necessário na memória para a mesma.
 * 
 * Assim sendo, irá depois, também, associar os respetivos valores de input
 * da função às repetivas propriedades da variável.
 * 
 * @param data A lista de strings que contem os parametros para a criação do user.
 * 
 * @return A User criada com as respetivas propriedades.
 */
User* userCreate(char data[][200])
{
    User * user = (User*) malloc(sizeof(User));

    strncpy(user->username, data[0], MAX_USER_STR);
    strncpy(user->name, data[1], MAX_USER_STR);
    user->gender = data[2][0];
    createDate(data[3],user->birth_date);
    createDate(data[4],user->account_creation);
    strncpy(user->pay_method, data[5], MAX_USER_STR);
    user->account_status = data[6][0];
    user->score = 0;
    user->rides = 0;
    user->money_spent = 0.f;
    user->distance = 0;

    return user;
}

/// @brief A função userUpdate atualiza os valores de um user após uma ride.
/**
 * A função userUpdate atualiza uma variável do tipo User
 * após uma viagem.
 * 
 * @param user A variável user a ser atualizada.
 * 
 * @param score A pontuação a ser adicionada ao user.
 * 
 * @param money_spent O dinheiro a ser adicionado ao user.
 * 
 * @param distance A distância a ser adicionado ao user.
 * 
 */
void userUpdate(User * user, int score, double money_spent, int distance)
{
    user->score += score;
    user->rides++;
    user->money_spent += money_spent;
    user->distance += distance;
}

/// @brief A função destroyUser destroí uma variável do tipo User.
/**
 * A função destroyUser destroí uma variável do tipo user, libertando
 * o espaço ocupado pela variável e pelas suas propriedades.
 * 
 * @param user A variável do tipo User que vai ser destruída.
 */
void destroyUser(User * user)
{
    free(user);
}

void printUser(User* user){
    printf("[User] -> {username: %s, name: %s, gender: %c, birth_date: %d/%d/%d, account_creation: %d/%d/%d, pay_method: %s, account_status:%c}",
    user->username,
    user->name,
    user->gender,
    user->birth_date[0],user->birth_date[1],user->birth_date[2],
    user->account_creation[0],user->account_creation[1],user->account_creation[2],
    user->pay_method,
    user->account_status
    );
}

void user_Str(char * dest, User * user, char mode)
{
    switch (mode)
    {
        case 'u':
            strcpy(dest, user->username);
            break;

        case 'n':
            strcpy(dest, user->name);
            break;

        case 'p':
            strcpy(dest, user->pay_method);
            break;
    }
}

char user_Char(User * user, char mode)
{
    switch (mode)
    {
        case 'g':
            return(user->gender);
            break;

        case 's':
            return(user->account_status);
            break;
    }
    return(' ');
}

void user_Date(Date dest, User * user, char mode)
{
    switch (mode)
    {
        case 'b':
            dest[0] = user->birth_date[0];
            dest[1] = user->birth_date[1];
            dest[2] = user->birth_date[2];
            break;

        case 'a':
            dest[0] = user->account_creation[0];
            dest[1] = user->account_creation[1];
            dest[2] = user->account_creation[2];
            break;
    }
}