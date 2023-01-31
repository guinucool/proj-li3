#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/utils.h"
#include "../includes/structs/global.h"
#include "../includes/structs/hashmap.h"
#include "../includes/structs/driver.h"
#include "../includes/structs/user.h"
#include "../includes/structs/ride.h"
#include "../includes/structs/city.h"
#include "../includes/structs/date.h"
#include "../includes/structs/datemap.h"
#include "../includes/structs/linkedlist.h"
#include "../includes/queries.h"


int isUser(char *id) {
    return id[0] != '\0' && ((id[0] >= 'a' && id[0] <= 'z') || (id[0] >= 'A' && id[0] <= 'Z'));
}

int isDriver(char *id) {
    return id[0] != '\0' && id[0] >= '0' && id[0] <= '9';
}

double calculate_ride_cost(Ride *ride, Global *glob) {

    int driver_key = ride_Int(ride, 'd');
    double total = 0;

    Driver *driver = (Driver*) get(global_Hashmap(glob, 'e'), (void*) &driver_key, equal, hashKey_Int, 1);

    switch(driver_Char(driver, 'c')) {
        case 0: // BASIC
            total = 3.25 + ride_Short(ride, 'p') * 0.62 + ride_Tip(ride); 
            break;
        case 1: // GREEN
            total = 4.00 + ride_Short(ride, 'p') * 0.79 + ride_Tip(ride); 
            break;
        case 2: // PREMIUM
            total = 5.20 + ride_Short(ride, 'p') * 0.94 + ride_Tip(ride); 
            break;
        default:
            total = 0;
            break; 
    }

    return total;
}


void insertDOrd(Driver maxN[], int N, Driver driver,char* city){
    int i;

    if(drivercmp(maxN,driver,city))return;

    for (i = 0; i < N; i++)
    {
        if(drivercmp(driver,maxN,city))break;
    }

    for(int j = N-1; j > i; j--)
    {
        maxN[j] = maxN[j-1];
    }

    maxN[i] = driver;
    
}

void rideCostFilterNoTip(void * ride, double res)
{
    res = rideCost(ride,0);
}

void linkedListRes(void * ride,LinkedList res)
{
    res = addOrdList(ride,res,ridecmp2);
}

void idOutput(int id, char * dest)
{   
    int size, i;
    char * idAux;
    sprintf(idAux,"%d",id);
    size = strlen(idAux);
    for (i = 0; i < 12-size; i++)
    {
        dest[i] = '0';
    }
    for (i; i < 12; i++)
    {
        dest[i] = idAux[i-12+size];
    }
}

void dateOutput(Date date, char * dest)
{
    char *day,*month,*year;
    sprintf(day,"%d",date[0]);
    sprintf(month,"%d",date[1]);
    sprintf(year,"%d",date[2]);

    strcat(dest,day);
    strcat(dest,"/");
    strcat(dest,month);
    strcat(dest,"/");
    strcat(dest,year);
}

char ** output(int )
{

}

void query1(char *id, Global *glob) {
    printf("QUERY one:\n");

    Hashmap *rides = NULL;
    Driver *driver = NULL;
    User *user = NULL;

    char name[MAX_USER_STR], gender;
    short birthdate[3], age;
    float average;
    int total = 0, count = 0;

    if (isUser(id)) {
        // Get the user from the correpondent hashmap (if it exists).
        user = (User*) get(global_Hashmap(glob, 'u'), (void*)id, equal_str, hashKey_Str, 1);

        rides = global_Hashmap(glob, 'r');

        total = 0; count = 0;
        double expenses = 0.0;

        for (int i = 0; i < HASHMAP_MAX; i++) {
            HashmapNode* node = get_entry(rides, i);

            for (HashmapNode *aux = node; aux != NULL; aux = node_Node(aux)) {
                    count++;  
                    Ride *ride = (Ride*) node_Void(aux, 'd');
                    total += get_user_score(ride);
                    expenses += calculate_ride_cost(ride, glob);
            }
        }

        average = 0.0;
        if (count > 0) {
            average = (float)total / count;
        }

        user_Str(name, user, 'n');
        gender = user_Char(user, 'g');
        user_Date(birthdate, user, 'b');
        age = calculateAge(birthdate);

        printf("%s;%c;%d;%0.3f;%d;%0.3f", name, gender, age, average, count, expenses);
    } else {
        if (isDriver(id)) {

            int number = atoi(id);

            // Get the driver from the correpondent hashmap (if it exists).
            driver = (Driver*) get(global_Hashmap(glob, 'e'), (void*)&number, equal, hashKey_Int, 1);

            rides = global_Hashmap(glob, 'r');

            total = 0; count = 0;
            double gains = 0.0;

            for (int i = 0; i < HASHMAP_MAX; i++) {
                HashmapNode* node = get_entry(rides, i);

                for (HashmapNode *aux = node; aux != NULL; aux = node_Node(aux)) {
                        count++;  
                        Ride *ride = (Ride*) node_Void(aux, 'd');
                        total += get_driver_score(ride);
                        gains += calculate_ride_cost(ride, glob);
                }
            }

            average = 0.0;
            if (count > 0) {
                average = (float)total / count;
            }
            
            driver_Str(name, driver, 'n');
            gender = driver_Char(driver, 'g');
            driver_Date(birthdate, driver, 'b');
            age = calculateAge(birthdate);
   
            printf("%s;%c;%d;%0.3f;%d;%0.3f", name, gender, age, average, count, gains);
        } else {
            printf("No user or driver found.\n");
        }
    }
}

void query2(int N, Global* glob){

}

void query3(int N, Global* glob){
    
}

/// @brief [OUTDATED DOCUMENTACION]A funcao query4 calcula o preco medio das viagens realizadas numa determinada cidade.
/**
 *  A função vai usar a lista da cidade para calcular a média, após ter a lista ligada, vai passá-la 
 *  à função preco_medio, que vai percorrer a lista elemento por elemento. Após ter os valores, 
 *  a função vai calcular o preço, fazendo a média de todos os preços calculados. 
 *  
 *  @param city Cidade
 *  @param glob Estrutura de dados global a ser atualizada.
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
double query4(char* city, Global glob)
{
    // Aquisição do Hashmap de cities
    Hashmap cities = glob_city(glob);

    // Aquisição da struct da city a ser analisada
    City city = get(cities, city, equal_str, hashKey_Str);

    // Aquisição do preço médio da cidade a partir da struct city
    double preco_medio = city_averageMoney(city);

    return preco_medio;
}

/// @brief [DOCUMENTAÇÃO OUTDATED]A função query5 calcula o preço médio das viagens realizadas entre duas datas.
/**
 *  A função chama a função betweenDates() para asquirir a lista ligada de HashmapNode 
 *  de Date do intervalo de tempo entre as duas datas pretendidas e depois usa a função
 *  preco_medio() para calcular o preço médio entre essas duas datas.
 * 
 *  @param dateA Data em que começa o intervalo de tempo.
 *  @param dateB Data em que termina o intervalo de tempo.
 *  @param glob  Estrutura de dados global a ser atualizada.
 * 
 *  @return Retorna o preço médio das viagens realizadas entre essas duas datas.
 */ 
double query5(Date dateA , Date dateB, Global glob)
{
    Hashmap calendario = glob_ride(glob); 
    Ride ride;
    double sum = 0;
    int count = 0;

    while (dateA[2] != dateB[2]+1)
    {
        DateMap anoA = get(calendario,&dateA[2],equal,hashKey_Int);

        dateFilter(anoA,dateA,dateB,rideCostFilterNoTip);
    }

    return (double)sum/count;
}

/// @brief A função query6 calcula a média da distância percorrida
///        numa cidade dentro de um dado intervalo de tempo.
/**
 * A função query6 calcula a média da distância percorrida
 * numa cidade dentro de um dado intervalo de tempo. 
 * 
 * Para isso, irá encontrar a lista (filtro) referente à cidade
 * desejada, e irá percorrer as ocorrências desta uma a uma.
 * 
 * A cada ocorrência, irá verificar se a viagem referente à mesma
 * tem uma data compatível com o intervalo desejado, e usar o valor
 * da sua distância para o cálculo da média caso seja compatível.
 * 
 * @param cty A cidade a ser filtrada.
 * 
 * @param dateInf O limite inferior do intervalo.
 * 
 * @param dateUp O limite superior do intervalo.
 * 
 * @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 * @return A média da distância total percorrida desejada.
 */
double query6(char * cty, short * dateInf, short * dateUp, Global * glob)
{
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), cty, equal_str, hashKey_Str, 0);

    double med = 0.f;
    double sum = 0.f;
    int i = 0;

    while (cityList != NULL)
    {
        City * city = (City *) node_Void(cityList, 'd');
        int key = city_Key(city);
        Ride * ride = (Ride *) get(global_Hashmap(glob, 'r'), (void *)&key, equal, hashKey_Int, 1);
        short date[3];
        ride_Date(date, ride);
        if (datecmp(dateInf, date) <= 0 && datecmp(date, dateUp) <= 0)
        {
            i++;
            sum += (double)ride_Short(ride, 'p');
        }
        cityList = node_Node(cityList);
    }
    
    if (i != 0)
        med = sum/i;

    return(med);
}

char ** query7(int N,char* city, Global * glob){

    double avMedia;
    Driver maxN[N];
    Driver driver;
    
    for (int i = 0; i < N; i++){maxN[i] = NULL;}
    
    // Obter a lista de todas as ocorrências na cidade pretendida
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), city, equal_str, hashKey_Str, 0);

    // Percorrer a lista das ocorrências na cidade pretendida
    while(cityList != NULL){

        // Adquirir a estrutura de city
        City* cityNode = node_Void(cityList,0);

        // Adquirir o tipo de ocorrência desta estrutura city
        char cityType = city_Type(cityNode); 

        // Verificar se o estrutura da lista é do tipo ride
        if(cityType == 'r'){

            // Aquisição da chave referente à hashmap de Rides
            int key = city_Key(cityNode);

            // Aquisição da estrutura Ride pretendida e dos elementos necessarios
            Ride* rideAux = (Ride *) get(global_Hashmap(glob, 'r'), (void*)&key, equal, hashKey_Int, 0);
            int driverID = ride_Int(rideAux,0);

            // Aquisição da estrutura Driver a partir do driverID 
            driver = (Driver *) get(global_Hashmap(glob, 'd'), (void*)&driverID, equal, hashKey_Int, 0);
            char status = driver_Char(driver,'s');
            
            if(!status)break;

            for (int i = 0; i < N; i++)
            {
                if(driver == maxN[i]){
                    status = 0;
                    break;
                }
            }

            if(!status)break;
            else insertDOrd(maxN,N,driver,city);
            
        }
    
    cityList = node_Node(cityList);
    }

    // Inicialização da lista de Strings contendo os resultados
    char ** resultados;

    // Inserção dos resultados da lista de Strings
    for (int i = 0; i < N; i++)
    {   
        driver = maxN[i];

        // Iniciar a string do resultado como vazia.
        resultados[i][0] = '\0';

        // Extração dos resultados de cada String
        char driverID[20];
        char driverName[NAME_STR_SIZE];
        char avaliacaoMedia[20];

        sprintf(driverID,"%d",driver_id(driver));
        driver_name(driverName,driver);
        avMedia = driver_score(driver,city);
        double_to_string(avMedia,avaliacaoMedia,3);

        strcat(resultados[i], driverID);
        strcat(resultados[i], ";");
        strcat(resultados[i], driverName);
        strcat(resultados[i], ";");
        strcat(resultados[i], avaliacaoMedia);
    }

    // Devolver o resultado da pesquisa.
    return resultados;
}


// Passo 1 : Extrair a informação das viagens, condutores e utilizadores da hashmap e colocar numa lista ligada.
// Passo 2: Ordenar a lista ligada conforme o enunciado (antiguidade do perfil de condutor, antiguidade do perfil de utilizador, ordem crescrent do id de viagem)
// Passo 3: Contruir o array (de strings) com os campos pretendidos.
char ** query8(char gender,int X, Global * glob) {

    // Actual date.
    short now[3];
    stringToDate(REF_DATE, now);

    // Obter todas as viagens.
    Hashmap *rides = global_Hashmap(glob, 'r');

    // Obter todos os condutores.
    Hashmap *drivers = global_Hashmap(glob, 'e');

    // Obter todos os utilizadores.
    Hashmap *users = global_Hashmap(glob, 'u');

    // Definição da estrutura para armazenar os resultados da query (0 - Ride, 1 - Driver, 2 - User).
    void* records[size(rides)][3];
    int nrecords = 0;

    // Percorrer todas as viagens e extrair aquelas que respeitam o critário de filtragem.
    while (rides) {

        // Extrair a informação da viagem.
        Ride *ride = (Ride*) node_Void(rides, 'd');
        int rideKey = ride_Int(ride, 'i');
        int driverKey = ride_Int(ride, 'e');
        char userKey[MAX_USER_STR];
        ride_Str(userKey, ride, 'u');

        // Extrair a informação do condutor.
        Driver *driver = (Driver*) get(drivers, (void *)& driverKey, equal, hashKey_Int, 1);
        short driverProfileDate[3];
        driver_Date(driverProfileDate, driver, 'b');

        // Extrair a informação do utilizador.
        User *user = (User*) get(users, (void*) &userKey, equal, hashKey_Str, 1);
        short userProfileDate[3];
        user_Date(userProfileDate, user, 'b');

        // Inserir as informações da viagem, condutor e utilizador na lista de resultados.
        if (driver_Char(driver, 'g') == gender && user_Char(user, 'g') == gender && 
            dateDiffYears(&driverProfileDate, &now) >= X && dateDiffYears(&userProfileDate, &now) >= X) {
            records[nrecords][0] = (void*) ride;
            records[nrecords][1] = (void*) driver;
            records[nrecords++][2] = (void*) user;
        }

        // Avançar para a próxima viagem.
        rides = node_Node(rides);
    }

    // Criar o array de strings a devolver.
    char ** resultados = (char**) malloc(sizeof(char*) * nrecords);

    for (int i = 0; i < nrecords; i++) {
        resultados[i] = (char*) malloc(sizeof(char) * 1024);
    }

    // Ordenar o array por (1) antiguidade to condutor, (2) antiguidade do utilizador e (3) id viagem por ordem crescente.
    for (int i = 0; i < nrecords-1; i++) {
        for (int j = i; j < nrecords; j++ ) {

            // Extrair e calcular a diferença entre as datas dos contudores 'i' e 'j'.
            short driverProfileDate_i[3], driverProfileDate_j[3];
            user_Date(driverProfileDate_i, records[i][1], 'b');
            user_Date(driverProfileDate_j, records[j][1], 'b');
            int diffDriverDate = dateDiffYears(&driverProfileDate_i, &now) - dateDiffYears(&driverProfileDate_j, &now);

            // Extrair e calcular a diferença entre as datas dos utilizadores 'i' e 'j'.
            short userProfileDate_i[3], userProfileDate_j[3];
            user_Date(userProfileDate_i, records[i][2], 'b');
            user_Date(userProfileDate_j, records[j][2], 'b');
            int diffUserDate = dateDiffYears(&userProfileDate_i, &now) - dateDiffYears(&userProfileDate_j, &now);

            // Extrair os ids das viagens 'i' e 'j'.
            int rideID_i, rideID_j;
            rideID_i = ride_Int(records[i][0], 'i');
            rideID_j = ride_Int(records[j][0], 'i');

            // Aplicação dos critérios para a troca dos apontadores 'i' e 'j'.
            if ( diffDriverDate < 0  || (diffDriverDate == 0 && diffUserDate < 0) || (diffDriverDate == 0 && diffUserDate == 0 && rideID_j > rideID_i)) {
                void * aux[3];

                // Swap de valores.
                for (int k = 0; k < 3; k++) {
                    aux[k] = records[i][k];
                    records[i][k] = records[j][k];
                    records[j][k] = aux[k];
                }
            }
        }
    }

    // Criar o array de strings com os campos pretendidos.
    for (int i = 0; i < nrecords; i++) {

        // Extrair os dados para construir o resultado.
        char driverID[20];
        char driverName[NAME_STR_SIZE];
        char userID[MAX_USER_STR];
        char userName[MAX_USER_STR];

        itoa(driver_Id(records[i][1]), driverID, 10);
        driver_Str(driverName, records[i][1], 'n');
        user_Str(userID, records[i][2], 'i');
        user_Str(userName, records[i][2], 'n');

        // Iniciar a string do resultado como vazia.
        resultados[i][0] = '\0';

        strcat(resultados[i], driver_Id);
        strcat(resultados[i], ";");
        strcat(resultados[i], driverName);
        strcat(resultados[i], ";");
        strcat(resultados[i], userID);
        strcat(resultados[i], ";");
        strcat(resultados[i], userName);
        strcat(resultados[i], ";");
    }

    // Devolver o resultado da pesquisa.
    return resultados;
}

char ** query9(Date dateA, Date dateB, Global glob){
    
    Hashmap calendario = glob_ride(glob); 
    Ride ride;
    LinkedList res;
    int size;

    while (dateA[2] != dateB[2]+1)
    {
        DateMap anoA = get(calendario,&dateA[2],equal,hashKey_Int);
        
        size = dateFilter(anoA,dateA,dateB,linkedListRes,res);
    }
    
    char ** resultados = malloc(sizeof(char*) * size);

    char * string;
    char * city;

    int strSize;
    int distSize,dist;
    int citySize;
    int tipSize;

    Date date;

    for (int i = 0; i < size; i++)
    {
        ride = list_element(res);

        dist = ride_distance(ride);
        distSize = intLen(dist);
        ride_city(city,ride);
        citySize = strlen(city);
        tipSize = intLen(ride_tip(ride))+3;

        strSize = 26 + distSize + citySize + tipSize;

        string = malloc(strSize);

        ride_date(date,ride);

        sprintf(string,"%012d;%02d/%02d/%04d;%d;%s;%.3f",
                ride_id(ride),
                date[0],
                date[1],
                date[2],
                dist,
                city,
                ride_tip(ride)
                );

        resultados[i] = string;

        list_next(res);
    }

    return resultados;
}
