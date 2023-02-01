#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"

char payment_methods[METHODS_SIZE][MAX_USER_STR] = {"CASH", "CREDIT_CARD", "DEBIT_CARD"};
char user_account_statuses[STATUS_SIZE][MAX_USER_STR] = {"INACTIVE", "ACTIVE"};

/// \struct Estrutura que define as variáveis do tipo User.
typedef struct _USER_ {
    char username[MAX_USER_STR];    //!< Username do user
    char name[MAX_USER_STR];        //!< Nome do user
    char gender;                    //!< Genero do user
    short age;                      //!< Data de nascimento do user no formato {dia,mês,ano}
    Date account_creation;          //!< Data de criação de conta do user no formato {dia,mês,ano}
    char pay_method;                //!< Metodo de pagamento que o user usa
    char account_status;            //!< Status da conta ('a' para active 'i' para inactive)
    int score;                      //!< Avaliação total do utilizador
    int rides;                      //!< Número de viagens do utilizador
    double money_spent;             //!< Total gasto em viagens pelo utilizador
    int distance;                   //!< Distancia total percorrida pelo utilizador
    Date last_ride;                 //!< Data da última viagem
}*User, NPUser;

/// @brief A função userCreate cria uma variável do tipo User.
/**
 * A função userCreate cria uma variável do tipo User, alocando
 * o espaço necessário na memória para a mesma.
 * 
 * Assim sendo, irá depois, também, associar os respetivos valores de input
 * da função às repetivas propriedades da variável.
 * 
 * @param username O username do user.
 * @param name O nome do user.
 * @param gender O género do user.
 * @param age A idade do user.
 * @param account_creation A data de criação de conta do user.
 * @param pay_method A forma de pagamento do user.
 * @param account_status O estado da conta do user.
 * 
 * @return O User criada com as respetivas propriedades.
 */
User userCreate(char * username, char * name, char gender, short age, Date account_creation, char pay_method, char account_status)
{
    User user = (User) malloc(sizeof(NPUser));

    strncpy(user->username, username, MAX_USER_STR);
    strncpy(user->name, name, MAX_USER_STR);
    user->gender = gender;

    user->age = age;
    user->account_creation[0] = account_creation[0];
    user->account_creation[1] = account_creation[1];
    user->account_creation[2] = account_creation[2];

    user->pay_method = pay_method;
    user->account_status = account_status;

    user->score = 0;
    user->rides = 0;
    user->money_spent = 0.f;
    user->distance = 0;

    user->last_ride[0] = account_creation[0];
    user->last_ride[1] = account_creation[1];
    user->last_ride[2] = account_creation[2];

    return user;
}

/// @brief A função userUpdate atualiza os valores de um user após uma ride.
/**
 * A função userUpdate atualiza uma variável do tipo User
 * após uma viagem.
 * 
 * @param user A variável user a ser atualizada.
 * @param score A pontuação a ser adicionada ao user.
 * @param money_spent O dinheiro a ser adicionado ao user.
 * @param distance A distância a ser adicionado ao user.
 * @param date A data da viagem que provocou a atualização.
 */
void userUpdate(User user, int score, double money_spent, int distance, Date date)
{
    user->score += score;
    user->rides++;
    user->money_spent += money_spent;
    user->distance += distance;

    if (datecmp(date, user->last_ride) > 0)
    {
        user->last_ride[0] = date[0];
        user->last_ride[1] = date[1];
        user->last_ride[2] = date[2];
    }
}

/// @brief A função destroyUser destroí uma variável do tipo User.
/**
 * A função destroyUser destroí uma variável do tipo user, libertando
 * o espaço ocupado pela variável e pelas suas propriedades.
 * 
 * @param user A variável do tipo User que vai ser destruída.
 */
void destroyUser(User user)
{
    if (user) free(user);
}

/// @brief A função debugPrintUser imprime um User.
/**
 * A função debugPrintUser imprime toda a informação registada
 * numa variável do tipo User para propósitos de debugging.
 * 
 * @param user A variável User a ser imprensa.
 */
void debugPrintUser(User user)
{
    printf("[%p](User) {\n    username: %s\n    name: %s\n    gender: %c\n    age: %d\n    account_creation: %d/%d/%d\n    pay_method: %d\n    account_status:%d\n    ",
        user,
        user->username,
        user->name,
        user->gender,
        user->age,
        user->account_creation[0],user->account_creation[1],user->account_creation[2],
        user->pay_method,
        user->account_status
    );
    printf("score: %d\n    rides: %d\n    money_spent: %.3f\n    distance: %d\n    last_ride: %d/%d/%d\n}\n",
        user->score,
        user->rides,
        user->money_spent,
        user->distance,
        user->last_ride[0],user->last_ride[1],user->last_ride[2]
    );
}

/// @brief A função parseUser converte o input numa variável User.
/**
 * A função parseUser tem como objetivo analisar, intrepetar
 * e converter o input do parser em propriedades adequadas
 * para a variável User.
 * 
 * Irá também fazer as devidas verificações de forma a não
 * converter informação inválida.
 * 
 * @param data O input do parser.
 * 
 * @return O User criado.
 */
User parseUser(char data[7][200])
{
    Date birth_date;
    if(!parseDate(data[3], birth_date)) return NULL;

    Date account_creation;
    if(!parseDate(data[4], account_creation)) return NULL;

    char username[MAX_USER_STR], name[MAX_USER_STR];
    char gender, pay_method = -1, account_status = -1;
    short age;

    strncpy(username, data[0], MAX_USER_STR);
    if(strlen(username) == 0) return NULL;

    strncpy(name, data[1], MAX_USER_STR);
    if(strlen(name) == 0) return NULL;

    gender = data[2][0];
    if (gender != MALE && gender != FEMALE) return NULL;

    age = calculateAge(birth_date);

    strtop(data[5]);
    strtop(data[6]);

    for (int i = 0; i < METHODS_SIZE; i++)
        if(strcmp(data[5], payment_methods[i]) == 0) pay_method = i;

    if (pay_method == -1) return NULL;

    for (int i = 0; i < STATUS_SIZE; i++)
        if(strcmp(data[6], user_account_statuses[i]) == 0) account_status = i;

    if (account_status == -1) return NULL;

    return userCreate(username, name, gender, age, account_creation, pay_method, account_status);
}

/// @brief A função usercmp compara dois users.
/**
 * A função usercmp compara dois users usando as propriedades
 * da distância total percorrida, do score de cada user,
 * da data da ultima viagem em caso de empate,
 * e do username em caso de outro empate.
 * 
 * Objetiva a ordenar os users por ordem decrescente, exceto
 * na propriedade de username, onde é usada a ordem crescente.
 * 
 * @param user1 O user número 1.
 * @param user2 O user número 2.
 * 
 * @return Os valores do costume de acordo com as comparações.
 */ 
int usercmp(User user1, User user2)
{
    int res = 0;

    if (user1->distance > user2->distance) res = 1;
    if (user1->distance < user2->distance) res = -1;

    if (res == 0 && (double)user1->score/user1->rides > (double)user2->score/user2->rides) res = 1;
    if (res == 0 && (double)user1->score/user1->rides < (double)user2->score/user2->rides) res = -1;
    
    if (res == 0) res = datecmp(user1->last_ride, user2->last_ride);

    if (res == 0) res = strcmp(user2->username, user1->username);

    return res;
}

/// @brief A função user_username devolve o username de um User.
void user_username(char * dest, User user)
{
    strncpy(dest, user->username, MAX_USER_STR);
}

/// @brief A função user_name devolve o nome de um User.
void user_name(char * dest, User user)
{
    strncpy(dest, user->name, MAX_USER_STR);
}

/// @brief A função user_gender devolve o género de um User.
char user_gender(User user)
{
    return user->gender;
}

/// @brief A função user_age devolve a idade de um User.
short user_age(User user)
{
    return user->age;
}

/// @brief A função user_accountCreation devolve a data de criação da conta de um User.
void user_accountCreation(Date dest, User user)
{
    dest[0] = user->account_creation[0];
    dest[1] = user->account_creation[1];
    dest[2] = user->account_creation[2];
}

/// @brief A função user_accountStatus devolve o estado de uma conta de um User.
char user_accountStatus(User user)
{
    return user->account_status;
}

/// @brief A função user_averageScore devolve a pontuação média de um User.
double user_averageScore(User user)
{
    return ((double)user->score / user->rides);
}

/// @brief A função user_rides devolve o número de viagens de um User.
int user_rides(User user)
{
    return user->rides;
}

/// @brief A função user_moneySpent devolve o dinheiro gasto por um User.
double user_moneySpent(User user)
{
    return user->money_spent;
}

/// @brief A função user_distance devolve a distância de um User.
int user_distance(User user)
{
    return user->distance;
}