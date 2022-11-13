#include "../inc/drivers/driver.h"

int main() {

    char name[] = "Fernando Fonseca";
	short birth_day[] = {21, 3, 1997};
	char gender = MALE;
	char car_class = PREMIUM;
	char license_plate[] = "11-12-TX";
	char city[] = "Porto";
	short account_creation[] = {1, 1, 2022};
	char account_status = ACTIVE; 

	Driver *dA = createDriver(1001, name, birth_day, gender, car_class, license_plate, city, account_creation, account_status);
    printDriver(dA);
    destroyDriver(dA);

    return 0;
}