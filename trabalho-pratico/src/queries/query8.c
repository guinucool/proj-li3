#include <stdio.h>
#include <stdlib.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief  A função transforma a informação de 
/**
 *   @param ride Ride a ser processada
 * 
 *  @param filter 
 * 
 *  
*/
int RidePrinter(void * ride, void * filter[], int * ignore, FILE *fp)
{
    char * gender = filter[0];
    int * age = filter[1];

    User user = ride_user(ride);
    Driver driver = ride_driver(ride);

    Date dateuser, datedriver;
    user_accountCreation(dateuser, user);
    driver_accountCreation(datedriver, driver);

    if (user_gender(user) == * gender && calculateAge(dateuser) >= * age && calculateAge(datedriver) >= * age)
    {
        if (*ignore <= 0)
        {
            char nameuser[MAX_USER_STR], namedriver[NAME_STR_SIZE], username[MAX_USER_STR];
            driver_name(namedriver, driver);
            user_username(username, user);
            user_name(nameuser, user);

            fprintf(fp,"%012d;%s;%012d;%s\n", driver_id(driver), namedriver, nameuser, username);
        }
        else
            *ignore -= 1;
    }

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
void query8(char gender, int X, Global glob, FILE * fp)
{
    List ride = glob_rideList(glob);
    void * filter[2];
    filter[0] = &gender;
    filter[1] = &X; 

    sortList(ride, ridecmp, NULL);
    listOut(ride, RidePrinter, 0, list_size(ride), filter, fp);
}


    



    


