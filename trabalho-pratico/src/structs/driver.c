#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/structs/driver.h"

char car_class_str[][8] = {"BASIC", "GREEN", "PREMIUM"};
int car_class_size = 3;
char account_status_str[][9] = {"INACTIVE", "ACTIVE"};
int account_status_size = 2;

/// @brief A funcao createDriver cria uma variavel do tipo drive.
/**
 * A funcao createDriver cria uma variavel do tipo drive, alocando 
 * o espaco necesaario na memoria para a mesma.
 *
 * Assim sendo, ira depois, tambem, associar os respetivos valores de input
 * da funcao as repetivas propriedades da variavel.
 *
 * @param id O id do driver.
 * 
 * @param name O nome do driver
 * 
 * @param birth_day A data de nascimento do driver.
 * 
 * @param gender O genero do driver.
 * 
 * @param car_class A classe do veiculo do driver.
 * 
 * @param license_plate A matricula do carro do driver.
 *
 * @param city A cidade do driver.
 *
 * @param account_creation A data de criacao da conta do driver.
 *
 * @param account_status O estado da conta do driver.
 *
 * @return O driver criado com as respetivas propriedades.
 
 */

Driver *createDriver(int id, char *name, short birth_day[], char gender, char car_class, char license_plate[], char city[], short account_creation[], char account_status) {
	
	Driver *driver = (Driver*) malloc(sizeof(Driver));

	driver->id = id;
	strncpy(driver->name, name, NAME_STR_SIZE);

	driver->birth_day[0] = birth_day[0];
	driver->birth_day[1] = birth_day[1];
	driver->birth_day[2] = birth_day[2];
	
	driver->gender = gender;
	driver->car_class = car_class;
	strncpy(driver->license_plate, license_plate, LICENSE_PLATE_STR_SIZE);
	strncpy(driver->city, city, CITY_STR_SIZE);
	driver->account_creation[0] = account_creation[0];
	driver->account_creation[1] = account_creation[1];
	driver->account_creation[2] = account_creation[2];
	driver->account_status = account_status; 

	return driver;
}


/// @brief A funcao destroyDriver destroi uma variavel do tipo Driver.
/**
 * A funcao destroyDriver destroi uma variavel do tipo driver, libertando
 * o espaco ocupado pela variavel e pelas suas propriedades.
 * 
 * @param driver A variavel do tipo driver que vai ser destruida.
 */

void destroyDriver(Driver *driver) {
	free(driver);
}



void printDriver(Driver* driver) {
	printf("Driver {id: %d, name: %s, birth_date: %02d/%02d/%04d, gender: %c, car_class: %s, license_plate: %s, city: %s, account_creation: %02d/%02d/%04d, account_status: %s}", 
		driver->id, 
		driver->name,
		driver->birth_day[0], driver->birth_day[1], driver->birth_day[2],
		driver->gender,
		car_class_str[(int) driver->car_class],
		driver->license_plate,
		driver->city,
		driver->account_creation[0], driver->account_creation[1], driver->account_creation[2],
		account_status_str[(int) driver->account_status]
	);
}


/// @brief A funcao parseDriver
/**
 * Extrai os campos id, name, birth_day, gender, car_class, license_plate, city, account_creation, account_status do array tokens passado
 * como parametro. E devolve um Driver com esses mesmos parametros.
 * Caso aconteca um erro na extracao de um parametro do array tokens, a funcao devolve o valor NULL.
 * 
 *
 * @return Driver | NULL
*/
Driver *parseDriver(char tokens[9][200]) {
		
	//int i = 0, id; 
	int id;
	char name[NAME_STR_SIZE];
	short birth_day[3];
	char gender;
	int car_class;
	char license_plate[LICENSE_PLATE_STR_SIZE];
	char city[CITY_STR_SIZE];
	short account_creation[3];
	char account_status;
	//char limit[] = {';', '\0'};

	// Parse ID.
	if ((id = atoi(tokens[0])) == 0) {
		return NULL;
	}

	// Parse NAME.
	strncpy(name, tokens[1], NAME_STR_SIZE);

	// Parse BIRTTH DAY.
	if (!parseDate(tokens[2], birth_day)) {
		return NULL;
	}

	// Parse GENDER.
	gender = tokens[3][0];

	if (gender != MALE && gender != FEMALE) {
		return NULL;
	}

	// Parse CAR CLASS.
	// Converte o token para maiusculas.
	for(int i = 0; tokens[4][i]; i++) {
		tokens[4][i] = toupper(tokens[4][i]);
	}

	// Verificar se o token existe no array car_class_str (onde estao todos os car classe possiveis).
	car_class = -1;
	for (int i = 0; i < car_class_size; i++) {
		if (strcmp(tokens[4], car_class_str[i]) == 0) {
			car_class = i;
			break;
		}
	}

	// Interrompe a funcao se car class nao e valido (-1).
	if (car_class == -1) {
		return NULL;
	}

	// Parse LICENSE PLATE
	strncpy(license_plate, tokens[5], LICENSE_PLATE_STR_SIZE);

	// Parse CITY.
	strncpy(city, tokens[6], CITY_STR_SIZE);

	// Parse ACCOUNT CREATION.
	if (!parseDate(tokens[7], account_creation)) {
		return NULL;
	}

	// Parse ACCOUNT STATUS.
	// Converte para maiusculas o token.
	for(int i = 0; tokens[8][i]; i++) {
		tokens[8][i] = toupper(tokens[8][i]);
	}

	// Veririca se o estado em token é valido (isto e se existe no array account_status_str).
	account_status = 9;
	for (int i = 0; i < account_status_size; i++) {
		if (strcmp(tokens[8], account_status_str[i]) == 0) {
			account_status = i;
			break;
		}
	}

	// Interrompe a funcao se status nao é valido (9).
	if (account_status == 9) {
		return NULL;
	}

	// Cria e devolve um novo driver com os parametros extraidos do array tokens.
	return createDriver(id, name, birth_day, gender, car_class, license_plate, city, account_creation, account_status);
}


/// @brief A funcao parseDate vai receber uma string e devolve um array com as datas
/**
 *
 * @return Devolve 3 inteiros armazenados
*/

int parseDate(char *str, short date[]) {

	char *token;
	char limit[] = {'/', '\0'};
	int n, i = 0;

	// Extrair a string antes do primeiro '/' (dia)
	token = strtok(str, limit);

	do {

		// Converte a string (token) num inteiro.
		if ((n = atoi(token)) == 0) {
			return 0;
		}

		// Armazena o inteiro na posicao correta (0 - dia/1 - mes/2 - ano)
		date[i++] = n;

		// Continua a extrair as strings para o mes e o ano.
	} while((token = strtok(NULL, limit)));

	// Verifica se foram armazenados 3 inteiros (dia/mes/ano).
	return i==3;
}