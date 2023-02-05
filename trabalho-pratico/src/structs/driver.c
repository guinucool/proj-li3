#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"

char car_classes[CLASS_SIZE][8] = {"BASIC", "GREEN", "PREMIUM"};
char driver_account_statuses[STATUS_SIZE][9] = {"INACTIVE", "ACTIVE"};

typedef struct _DRIVER_ {
	int id;                                      //!< INTEGER - Id do driver
	char name[NAME_STR_SIZE];                    //!< STRING - Nome do driver
	short age;                                   //!< SHORT - Idade do driver
	char gender;                                 //!< CHAR {'M' - MALE, 'F' - FEMALE} - Género do driver
	char car_class;                              //!< CHAR {0 - BASIC, 1 - GREEN, 2 - PREMIUM} - Classe do driver
	char license_plate[LICENSE_PLATE_STR_SIZE];  //!< STRING - Matrícula do driver
	char city[CITY_STR_SIZE];                    //!< STRING - Cidade do driver
	Date account_creation;                       //!< DATE {day, month, year} - Data de criação da conta do driver
	char account_status;                         //!< CHAR {0 - INACTIVE, 1 - ACTIVE} - Estado da conta do driver
	int * score;								 //!< DYNAMIC ARRAY - Pontuação do driver (global e cidades)
	int * rides;								 //!< DYNAMIC ARRAY - Número de viagens do driver (global e cidades)
	double money_received;						 //!< DOUBLE - Totalidade do dinheiro recebido pelo driver
	char ** cities;								 //!< DYNAMIC STRING ARRAY - Cidades das viagens do driver
	int counter;								 //!< INTEGER - Número de cidades das viagens do driver
	Date last_ride;								 //!< DATE {day, month, year} - Data da última viagem do driver
}*Driver, NPDriver;

/// @brief A funcao createDriver cria uma variavel do tipo driver.
/**
 * A funcao createDriver cria uma variavel do tipo drive, alocando 
 * o espaco necessário na memoria para a mesma.
 *
 * Assim sendo, irá depois, também, associar os respetivos valores de input
 * da função às repetivas propriedades da variável.
 *
 * @param id O id do driver.
 * @param name O nome do driver
 * @param age A idade do driver.
 * @param gender O genero do driver.
 * @param car_class A classe do veiculo do driver.
 * @param license_plate A matricula do carro do driver.
 * @param city A cidade do driver.
 * @param account_creation A data de criacao da conta do driver.
 * @param account_status O estado da conta do driver.
 *
 * @return O driver criado com as respetivas propriedades.
 */
Driver createDriver(int id, char * name, short age, char gender, char car_class, char * license_plate, char * city, Date account_creation, char account_status)
{	
	Driver driver = (Driver) malloc(sizeof(NPDriver));
	if(driver == NULL) return NULL;

	driver->id = id;
	strncpy(driver->name, name, NAME_STR_SIZE);
	driver->age = age;
	driver->gender = gender;

	driver->car_class = car_class;
	strncpy(driver->license_plate, license_plate, LICENSE_PLATE_STR_SIZE);
	strncpy(driver->city, city, CITY_STR_SIZE);

	driver->account_creation[0] = account_creation[0];
	driver->account_creation[1] = account_creation[1];
	driver->account_creation[2] = account_creation[2];
	driver->account_status = account_status;

	driver->score = malloc(sizeof(int));
	if(driver->score == NULL)
	{
		free(driver);
		return NULL;
	}
	driver->score[0] = 0;
	driver->rides = malloc(sizeof(int));
	if(driver->rides == NULL)
	{
		free(driver->score);
		free(driver);
		return NULL;
	}
	driver->rides[0] = 0;
	driver->money_received = 0.f;
	driver->counter = 0;

	driver->last_ride[0] = account_creation[0];
	driver->last_ride[1] = account_creation[1];
	driver->last_ride[2] = account_creation[2];

	return driver;
}

/// @brief A função updateDriver atualiza a informação de um Driver.
/**
 * A função updateDriver atualiza a informação de um Driver
 * após um viagem, adicionando as estatísticas dessa viagem
 * às já existentes no Driver.
 * 
 * @param driver O Driver a ser atualizado.
 * @param score A pontuação a ser adicionada.
 * @param money_received O dinheiro recebido a ser adicionado.
 * @param city A cidade onde a viagem ocorreu.
 * @param date A data da viagem.
 * 
 * @return A conclusão de que se a cidade é uma nova inserção.
 */
int updateDriver(Driver driver, int score, double money_received, char * city, Date date)
{
	int res = 0;
	int target = -1;
	void * memAux;

	for (int i = 0; i < driver->counter; i++)
		if(strcmp(driver->cities[i], city) == 0) target = i;

	if (target == -1)
	{
		res = 1;

		target = driver->counter;
		driver->counter++;

		if (driver->counter == 1)
		{ 
			driver->cities = malloc(sizeof(char*));
			if(driver->cities == NULL) return -1;
		}
		else 
		{
			memAux = realloc(driver->cities, sizeof(char*) * driver->counter);
			if(memAux == NULL)return -1;
			else driver->cities = memAux;
		}

		driver->cities[target] = malloc(sizeof(char) * strlen(city));
		if(driver->cities[target] == NULL)return -1;

		strcpy(driver->cities[target], city);

		memAux = realloc(driver->score, sizeof(int) * (driver->counter + 1));
		if(memAux == NULL)return -1;
		else driver->score = memAux;

		driver->score[driver->counter] = 0;

		memAux = realloc(driver->rides, sizeof(int) * (driver->counter + 1));
		if(memAux == NULL)return -1;
		else driver->rides = memAux;

		driver->rides[driver->counter] = 0;
	}

	target++;

	driver->score[0] += score;
	driver->score[target] += score;

	driver->rides[0]++;
	driver->rides[target]++;

	driver->money_received += money_received;

	if (datecmp(date, driver->last_ride) > 0)
    {
        driver->last_ride[0] = date[0];
        driver->last_ride[1] = date[1];
        driver->last_ride[2] = date[2];
    }

	return res;
}

/// @brief A função destroyDriver destroi uma variavel do tipo Driver.
/**
 * A função destroyDriver destroi uma variavel do tipo Driver, libertando
 * o espaco ocupado pela variável e pelas suas propriedades.
 * 
 * @param driver A variável do tipo Driver que vai ser destruida.
 */
void destroyDriver(Driver driver)
{
	if (driver)
	{
		if (driver->score) free(driver->score);
		if (driver->rides) free(driver->rides);

		if (driver->cities)
		{
			for (int i = 0; i < driver->counter; i++)
				free(driver->cities[i]);
			
			free(driver->cities);
		}
		
		free(driver);
	}
}

/// @brief A função debugPrintDriver imprime um Driver.
/**
 * A função debugPrintDriver imprime um Driver e as suas informações
 * afim de dar informações úteis para debugging.
 * 
 * @param driver O Driver a ser imprenso.
 */
void debugPrintDriver(Driver driver)
{
	printf("[%p](Driver) {\n    id: %d\n    name: %s\n    age: %d\n    gender: %c\n    car_class: %d\n    license_plate: %s\n    city: %s\n    account_creation: %d/%d/%d\n    account_status: %d\n    ",
		driver,
		driver->id, 
		driver->name,
		driver->age,
		driver->gender,
		driver->car_class,
		driver->license_plate,
		driver->city,
		driver->account_creation[0], driver->account_creation[1], driver->account_creation[2],
		driver->account_status
	);
	printf("[Global]\n    score: %d\n    rides: %d\n    money_received: %.3f\n    last_ride: %d/%d/%d\n",
        driver->score[0],
        driver->rides[0],
        driver->money_received,
        driver->last_ride[0],driver->last_ride[1],driver->last_ride[2]
    );
	for (int i = 0; i < driver->counter; i++)
	{
		printf("    [%s]\n    score: %d\n    rides: %d\n",
			driver->cities[i],
        	driver->score[i+1],
        	driver->rides[i+1]
    	);
	}
	printf("}\n");
}

/// @brief A função parseDriver converte várias strings em propriedades adequadas ao tipo Driver.
/**
 * A função parseDriver extrai os campos id, name, birth_day, gender, car_class, license_plate,
 * city, account_creation, account_status do array tokens passado
 * como parametro.
 * 
 * Depois de os tratar, devolve um Driver com esses mesmos parametros.
 * Caso aconteca um erro na extracao de um parametro do array tokens,
 * a funcao devolve o valor NULL.
 * 
 * @param tokens A informação em strings.
 *
 * @return O Driver criado.
*/
Driver parseDriver(char tokens[9][200])
{
	// Parse BIRTH_DAY
	Date birth_day;
	if(!parseDate(tokens[2], birth_day)) return NULL;

	// Parse ACCOUNT_CREATION
	Date account_creation;
	if(!parseDate(tokens[7], account_creation)) return NULL;

	int id;
	short age;
	char name[NAME_STR_SIZE], license_plate[LICENSE_PLATE_STR_SIZE], city[CITY_STR_SIZE];
	char gender, car_class = -1, account_status = -1;
	//char limit[] = {';', '\0'};

	// Parse ID
	if ((id = atoi(tokens[0])) == 0) return NULL;

	// Parse NAME
	strncpy(name, tokens[1], NAME_STR_SIZE);
	if(strlen(name) == 0) return NULL;

	// Parse AGE
	age = calculateAge(birth_day);

	// Parse GENDER
	gender = tokens[3][0];
	if (gender != MALE && gender != FEMALE) return NULL;

	// Parse CAR_CLASS
	// Converte o token para maiusculas.
	strtop(tokens[4]);

	// Verificar se o token existe no array car_class_str (onde estao todos os car classe possiveis).
	for (int i = 0; i < CLASS_SIZE; i++)
		if (strcmp(tokens[4], car_classes[i]) == 0) car_class = i;

	// Interrompe a funcao se car class nao e valido (-1).
	if (car_class == -1) return NULL;

	// Parse LICENSE_PLATE
	strncpy(license_plate, tokens[5], LICENSE_PLATE_STR_SIZE);
	if(strlen(tokens[5]) == 0) return NULL;

	// Parse CITY
	strncpy(city, tokens[6], CITY_STR_SIZE);
	if(strlen(tokens[6]) == 0) return NULL;

	// Parse ACCOUNT_STATUS
	// Converte para maiusculas o token.
	strtop(tokens[8]);

	// Veririca se o estado em token é valido (isto e se existe no array account_status_str).
	for (int i = 0; i < STATUS_SIZE; i++)
		if (strcmp(tokens[8], driver_account_statuses[i]) == 0) account_status = i;

	// Interrompe a funcao se status nao é valido (-1).
	if (account_status == -1) return NULL;

	// Cria e devolve um novo driver com os parametros extraidos do array tokens.
	return createDriver(id, name, age, gender, car_class, license_plate, city, account_creation, account_status);
}

/// @brief A função drivercmp compara dois Drivers.
/**
 * A função drivercmp tem como objetivo proceder à comparação
 * de dois drivers, dando um output que obedece às regras
 * da comparação (1 para maior, etc...).
 * 
 * A primeira prioridade na comparação será a avaliação média
 * dos Drivers, por ordem crescente.
 * 
 * A segunda prioridade, no caso de empate e da comparação
 * ser global, será a data da viagem mais recente.
 * 
 * E a terceira prioridade será o id do driver, por ordem
 * crescente no caso global, e decrescente no caso de
 * cidade.
 * 
 * @param driver1 O Driver 1.
 * @param driver2 O Driver 2.
 * @param city A cidade de comparação (NULL no caso de Global).
 * 
 * @return O valor correspondente ao resultado da comparação.
 */
int drivercmp(Driver driver1, Driver driver2, char * city)
{
	int res = 0;
	double av1 = (double) driver1->score[0] / driver1->rides[0];
	double av2 = (double) driver2->score[0] / driver2->rides[0];

	if(driver1 == NULL) res = -1;
	if(driver2 == NULL) res = 1;

	if (city)
	{
		for (int i = 0; i < driver1->counter; i++)
			if(strcmp(driver1->cities[i], city) == 0) av1 = (double)driver1->score[i+1] / driver1->rides[i+1];

		for (int i = 0; i < driver2->counter; i++)
			if(strcmp(driver2->cities[i], city) == 0) av2 = (double)driver2->score[i+1] / driver2->rides[i+1];
	}

	if (av1 != av1) av1 = 0.f;
	if (av2 != av2) av2 = 0.f;

	if (av1 > av2) res = 1;
	if (av1 < av2) res = -1;

	if(!city && res == 0) res = datecmp(driver1->last_ride, driver2->last_ride);

	if(res == 0)
	{
		if(driver1->id < driver2->id) res = 1;
		else res = -1;
		
		if(city) res = -res;
	}

	return res;
}

/// @brief A função driver_id devolve o id de um Driver. 
int driver_id(Driver driver)
{
	return driver->id;
}

/// @brief A função driver_name devolve o nome de um Driver. 
void driver_name(char * dest, Driver driver)
{
	strncpy(dest, driver->name, NAME_STR_SIZE);
}

/// @brief A função driver_age devolve a idade de um Driver. 
short driver_age(Driver driver)
{
	return driver->age;
}

/// @brief A função driver_gender devolve o género de um Driver. 
char driver_gender(Driver driver)
{
	return driver->gender;
}

/// @brief A função driver_carClass devolve a classe de um Driver.
char driver_carClass(Driver driver)
{
	return driver->car_class;
}

/// @brief A função driver_accountCreation devolve a data de criação de conta de um Driver.
void driver_accountCreation(Date dest, Driver driver)
{
	dest[0] = driver->account_creation[0];
	dest[1] = driver->account_creation[1];
	dest[2] = driver->account_creation[2];
}

/// @brief A função driver_accountStatus devolve o estado da conta de um Driver.
char driver_accountStatus(Driver driver)
{
	return driver->account_status;
}

/// @brief A função driver_score devolve a pontuação média de um Driver.
double driver_score(Driver driver, char * city)
{
	double res = (double)driver->score[0] / driver->rides[0];

	if(city) for (int i = 0; i < driver->counter; i++)
				if(strcmp(driver->cities[i], city) == 0) res = (double)driver->score[i+1] / driver->rides[i+1];
	
	return res;
}

/// @brief A função driver_rides devolve o número de viagens de um Driver.
int driver_rides(Driver driver)
{
	return driver->rides[0];
}

/// @brief A função driver_moneyReceived devolve o dinheiro ganho por um Driver.
double driver_moneyReceived(Driver driver)
{
	return driver->money_received;
}