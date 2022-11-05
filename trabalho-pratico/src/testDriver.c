#include "../inc/drivers/driver.h"

int main() {

    char name[] = "Fernando Fonseca";
	Driver *dA = createDriver(1001, name);
    printDriver(dA);
    destroyDriver(dA);

    return 0;
}