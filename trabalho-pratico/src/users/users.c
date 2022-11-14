#include <stdlib.h>

#include "../../inc/users/users.h"
#include "../../inc/utils/hashmap.h"


Users * createUsers() {
	return createHashmap();
}

void destroyUsers(Users* users) {
	destroyHashmap(users);
}

