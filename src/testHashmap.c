#include <stdio.h>

#include "../include/hashmap.h"

int equal(void* key1, void* key2) {
    return *((int*) key1) == *((int*) key2);
}

int main() {

    int key = 13;
    char data[] = "treze";
    char *result;

    Hashmap* hashmap = createHashmap();

    put(hashmap, (void*) &key, (void*) data);

    result = (char*) get(hashmap, (void*) &key, equal);

    printf("Valor devolvido 'e %s\n", result);

    destroyHashmap(hashmap);

    return 0;
}