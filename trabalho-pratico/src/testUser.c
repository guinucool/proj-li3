#include "../inc/users/user.h"

int main(){

    char* test[7] = {
        "MiTeixeira",
        "Miguel Teixeira",
        "M",
        "03/09/1958","05/11/2017",
        "cash",
        "active"
    };

    User* uTest = userCreate(test);
    printUser(uTest);
    destroyUser(uTest);

    return 0;
}