#ifndef _USERS_H_
#define _USERS_H_

#include "../../inc/users/user.h"
#include "../../inc/utils/hashmap.h"

typedef Hashmap Users;


Users * createUsers();
void putUser(Users* users, User* user);
void destroyUsers(Users* users);


#endif