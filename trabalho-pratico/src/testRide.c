#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utils/parser.h"
#include "../inc/rides/rides.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        return(0);

    Data * base = createAll(argv[1]);

    Ride * ride = getRide(base->rides, 1000000);

    printf("%d %d %s\n", ride->id, ride->driver, ride->user);

    return(0);
}