#ifndef _CITY_H_
#define _CITY_H_

#include <stdio.h>
#include <math.h>

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

#endif