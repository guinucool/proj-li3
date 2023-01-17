#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/structs/hashmap.h"
#include "../includes/structs/global.h"
#include "../includes/queries.h"
#include "../includes/structs/driver.h"
#include "../includes/structs/user.h"
#include "../includes/structs/ride.h"
#include "../includes/structs/city.h"
#include "../includes/structs/datefilter.h"
#include "../includes/structs/btree.h";
#include "../includes/utils.h"
#include "../includes/structs/btree.h"


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
            total = 3.25 + ride_Short(ride, 'p') * 0.79 + ride_Tip(ride); 
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

/// @brief A função preco_medio calcula o preco_medio de um certo filtro de viagens.
/**
 * A função preco_medio calcula o preco_medio de um certo filtro de viagens, percorrendo
 * todas as suas ocorrências no Hashmap de rides e no Hashmap de drivers, obtendo
 * assim as tarifas e a distancia percorrida de cada viagem.
 * 
 * Acaba por ir somando os vários preços calculados de cada viagem, e no final 
 * divide esta soma pelo número de viagens existentes no certo filtro.
 * 
 * @param list Lista de viagens no filtro.
 * 
 * @param glob A global que contém a informação recolhida na base de dados.
 * 
 * @param mode O tipo de filtro fornecido (d - datas, c - cidades).
 * 
 * @return O preço médio das viagens neste filtro.
 */
double preco_medio(HashmapNode * list, Global * glob, char mode)
{
    HashmapNode * tracker = list;
    int n = 0;
    double precoRide = 0, precoSum = 0;
    while(tracker != NULL)
    {
        void * key;
        if (mode == 'd')
        {
            DateFilter * filter = (DateFilter*) node_Void(tracker, 'd');
            key = date_Key(filter);
        }
        else
        {
            City * city = (City*) node_Void(tracker, 'd');
            int id = city_Key(city);
            key = (void*) &id;
        }
        Ride * ride = (Ride*) get(global_Hashmap(glob, 'r'), key, equal, hashKey_Int, 1);
        int did = ride_Int(ride, 'd');
        Driver * driver = (Driver*) get(global_Hashmap(glob, 'e'), (void*)&did, equal, hashKey_Int, 1);

        switch (driver_Char(driver, 'c'))
        {
            case 0:
                precoRide = 3.25 + 0.62 * ride_Short(ride, 'p');
                break;
        
            case 1:
                precoRide = 4 + 0.79 * ride_Short(ride, 'p');
                break;

            case 2:
                precoRide = 5.2 + 0.94 * ride_Short(ride, 'p');
                break;
        }

        precoSum += precoRide;
        n++;
        tracker = node_Node(tracker);
    }
    
    if (n != 0)
        return (precoSum/n);
    else
        return (0);
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

/// @brief A funcao query4 calcula o preco medio das viagens realizadas numa determinada cidade.
/**
 *  A função vai usar a lista da cidade para calcular a média, após ter a lista ligada, vai passá-la 
 *  à função preco_medio, que vai percorrer a lista elemento por elemento. Após ter os valores, 
 *  a função vai calcular o preço, fazendo a média de todos os preços calculados. 
 *  
 *  @param city Cidade
 *  @param glob Estrutura de dados global a ser atualizada.
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
double query4(char* city, Global* glob)
{
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), city, equal_str, hashKey_Str, 0);
    double result = preco_medio(cityList,glob,'c');
    return result;
}

/// @brief A função query5 calcula o preço médio das viagens realizadas entre duas datas.
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
double query5(short* dateA , short* dateB, Global* glob)
{
    HashmapNode * listRides = betweenDates(dateA, dateB, 'r', glob);
    double result = preco_medio(listRides,glob,'d');
    destroyNode(listRides, 0);
    return result;
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
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), city, equal_str, hashKey_Str, 0);
    BinaryTree7* bTree;
    BinaryTree7* max[N];
    for (int i = 0; i < N; i++)max[i] = NULL;

    while(cityList != NULL){

        City* cidade = node_Void(cityList,0);
        char cityType = city_Type(cidade); 

        if(cityType == 'r'){
            int key = city_Key(cityList);
            Ride* rideAux = (HashmapNode *) get(global_Hashmap(glob, 'r'), (void*)&key, equal, hashKey_Int, 0);
            int driverID = ride_Int(rideAux,0);
            int driverScore = get_driver_score(rideAux);
            BinaryTree7 * auxTree = insertTreeOrd_7(bTree,driverID);
        
            if(auxTree != NULL){
                incrementCount(auxTree);
                addScore(auxTree,driverScore);
            }else{ 
                Driver * driver = (HashmapNode *) get(global_Hashmap(glob, 'd'), (void*)&driverID, equal, hashKey_Int, 0);
                char * name;
                driver_Str(name,driver, 'n');
                auxTree = createTree(driverID,name,driverScore,NULL,NULL);
            }
        }else cityList = node_Node(cityList);
    }

    int tree_mutex = 1;

    maxN(bTree,N,max,&tree_mutex);
    
    char ** resultados;

    for (int i = 0; i < N; i++)
    {
        double avMedia = 0.f;
        bTree = max[i];

        resultados[i][0] = '\0';

        char driverID[20];
        char driverName[NAME_STR_SIZE];
        avMedia = (double)(bTree_total(bTree)/bTree_count(bTree));
        char avaliacaoMedia[20];

        itoa(bTree_id(bTree),driverID,10);
        strcpy(driverName,bTree_name(bTree));
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

void query9(short* dateA,short* dateB, Global * glob){
    
}
