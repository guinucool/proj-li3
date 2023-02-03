#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"

/// @brief  A função transforma a informação de 
/**
 *   @param ride Ride a ser processada
 * 
 *  @param filter 
 * 
 *  
*/
int RidePrinter(void * ride, void * filter[], int * ignore, FILE *fp) {

    char * gender = filter[0];
    int * age = filter[1];
    User user = ride_user(ride);
    Driver driver = ride_driver(ride);
    Date dateuser;
    Date datedriver;
    user_accountCreation(dateuser, user);
    driver_accountCreation(datedriver, driver);
    int res = user_gender(user) == * gender && calculateAge(dateuser) >= * age && calculateAge(datedriver) >= * age;
    if (res)  fprintf(fp,"%012d;%s;%012d;%s\n", driver_id(driver), driver_name(driver), user_name(user), user_username(user)); 

}

/// @brief 
/**
 * 
 * 
 * @param gender Genero do condutor
 * 
 * @param X Numero de anos do perfil
 * 
 * @param glob  A global a ser considerada para os cálculos estatísticos.
 * 
 * 
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


    



    


