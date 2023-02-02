#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"

void ListRes(void * driver,LinkedList res)
{
    res = addOrdList(driver,res,ridecmp2);

}

int RidePrinter(void * ride, void * filter){

    char gender = filter[0];
    int age = atoi(filter + 1);
    Date date;
    user_accountCreation;
    int res = user_gender(ride_user(ride)) == gender && calculateAge;
    

}

char ** query8(char gender,int X, Global * glob) {

    sortList(glob_rideList(glob), ridecmp2);

    Hashmap rides = global_Hashmap(glob);
    Hashmap drivers = global_Hashmap(glob);
    Hashmap users = global_Hashmap(glob);
    List res;
    int size;


    while (rides) {

        nrecords += datFilter(gender,ListRes,res);

        // Inserir as informações da viagem, condutor e utilizador na lista de resultados.
        if (driver_Char(driver) == gender && user_Char(user) == gender && 
            dateDiffYears(driverProfileDate) >= X && dateDiffYears(userProfileDate) >= X) {
            records[nrecords][0] = (void*) ride;
            records[nrecords][1] = (void*) driver;
            records[nrecords++][2] = (void*) user;

    }

    char ** resultados = malloc(sizeof(char*) * nrecords);

    char * string, name;

    int rideKey;
    int driverKey;
    char userKey[MAX_USER_STR];
    ride_Str(userKey, r);

    for (int i = 0; i < nrecords; i++) {
        resultados[i] = (char*) malloc(sizeof(char) * 1024);
    }

    // Ordenar o array por (1) antiguidade to condutor, (2) antiguidade do utilizador e (3) id viagem por ordem crescente.
    /* for (int i = 0; i < size-1; i++) {
        for (int j = i; j < size; j++ ) { */

        // Extrair e calcular a diferença entre as datas dos contudores 'i' e 'j'.
        int diffDriverDate = dateDiffYears(driverProfileDate) - dateDiffYears(driverProfileDate);

        // Extrair e calcular a diferença entre as datas dos utilizadores
        int diffUserDate = dateDiffYears(userProfileDate) - dateDiffYears(userProfileDate);
         
        // Extrair os ids das viagens 'i' e 'j'.
        int rideID_i, rideID_j;
        rideID = ride_Int(records[i][0])

        }
    }

    for (int i = 0; i < nrecords; i++) {
            
        ride = list_element(res);
        
        driver_id(id, driver);
        nameSize = strlen(id);

        driver_name(name, driver);
        nameSize = strlen(name);

        user_id(id, user);
        nameSize = strlen(id);

        user_name(name, user);
        nameSize = strlen(name);

        string = malloc(strSize);

        sprintf(string,"%012d;%s;%012d;%s", driver_id(driver), driver_name(driver), user_name(user), user_username(user))

        resultados[i] = string;

        list_next(res);
    }

    return resultados;
}





    


