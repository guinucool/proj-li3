#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"

/// @brief  A função transforma a informação necessária para um ficheiro de output.
/**
 * A função a partir do filter vai receber os dados que quer filtrar, o gender e a age das contas. 
 * De seguida vai bsucar o user e o driver de cada ride, pela qual ele vai passar, na lista ordenada 
 * de rides e vai verificar se o user e o driver, se o genero e a idade respeitam as condições, se 
 * respeitarem a ride é imprimida.
 * 
 * @param ride Ride a ser processada.
 * 
 * @param filter 
 * 
 * @param ignore Número de outputs que vai ter de ignorar.
 * 
 * @param fp Ficheiros de output. 
*/
int RidePrinter(void * ride, void * filter[], int * ignore, FILE * fp) {

    char * gender = filter[0];
    int * age = filter[1];
    User user = ride_user(ride);
    Driver driver = ride_driver(ride);
    Date dateuser;
    Date datedriver;
    user_accountCreation(dateuser, user);
    driver_accountCreation(datedriver, driver);
    int res = user_gender(user) == * gender && calculateAge(dateuser) >= * age && calculateAge(datedriver) >= * age;
    if (res) fprintf(fp,"%012d;%s;%012d;%s\n", driver_id(driver), driver_name(driver), user_name(user), user_username(user)); 

}

/// @brief 
/**
 * A função vai começar por usar a função de ordem superior sortList para ordenar 
 * a lista de rides com a função ridecmp que ordena as rides pela conta mais antiga. 
 * Apos ter a lista ordenada, vai listar as viagens que são impressas pela listOut 
 * no ficheiro de output.
 * 
 * @param gender Genero do condutor.
 * 
 * @param X Numero de anos do perfil.
 * 
 * @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 * @param fp Ficheiro de output.
 * 
*/
char ** query8(char gender,int X, Global glob, FILE * fp) {

    void * filter[2];
    filter[0] = &gender;
    filter[1] = &X; 
    List ride = glob_rideList(glob);
    sortList(ride, ridecmp);
    listOut(ride, RidePrinter, 0, list_size(ride), filter, fp);

}


    



    


