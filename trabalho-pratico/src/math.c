#include <stdio.h>
#include <math.h>

#include "../inc/structs/driverId.h"
#include "../inc/structs/ride.h"
#include "../inc/drivers/driver.h"
#include "../inc/utils.h"
#include "../inc/structs/hashmap.h"

int media(int preço[], int n)
{
    int med, sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += preço[i];
    }
    med = sum / n;

    return med;
}

