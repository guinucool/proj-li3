#ifndef _DRIVERID_H_
#define _DRIVERID_H_


typedef struct _DRIVERID_
{
    int id;
    int key;
}DriverId;

DriverId * createCity(int driverid, int key);
void destroyDriverId(DriverId * driverId);

#endif