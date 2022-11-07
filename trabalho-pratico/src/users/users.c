#include <stdlib.h>

#include "../../inc/users/users.h"
#include "../../inc/utils/hashmap.h"


Users * createUsers() {
	return createHashmap();
}

void putUser(Users* users, User* user) {

	if (users != NULL) {

		put((Hashmap*)users, (void*)&user->username, (void*)user);

	} 

}

User* getUser(Users *users, char* key,  int (*equal)(void*, void*)) {
	return (User*) get((Hashmap*)users, (void*) &key, equal);
}

void destroyUsers(Users* users) {
	destroyHashmap(users);
}

