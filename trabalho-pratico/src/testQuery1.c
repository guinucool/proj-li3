#include <stdio.h>
#include <stdlib.h>
#include "../inc/utils/parser.h"
#include "../inc/drivers/drivers.h"
#include "../inc/drivers/driver.h"
#include "../inc/queries/queries.h"

int main() {

    Data *store =  createAll("./db");

    Driver *driver = getDriver(store->drivers, 10000);

    query_one(store, "10000");


    return 0;
}