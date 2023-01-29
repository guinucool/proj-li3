#ifndef _GLOBAL_H_
#define _GLOBAL_H_

// Estrutura
typedef struct _GLOBAL_ *Global;

// Tratamentos
Global createGlobal();
void destroyGlobal(Global glob);

// Devoluções
void * glob_user(Global glob);
void * glob_driver(Global glob);
void * glob_ride(Global glob);
void * glob_city(Global glob);
void * glob_userList(Global glob);
void * glob_driverList(Global glob);
void * glob_rideList(Global glob);

#endif