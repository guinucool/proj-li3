#include <stdlib.h>
#include "../../inc/structs/global.h"

Global * createGlobal()
{
    Global * glob = (Global *) malloc(sizeof(Global));

    glob->users = createHashmap();
    glob->drivers = createHashmap();
    glob->rides = createHashmap();

    return(glob);
}

void destroyGlobal(Global * glob)
{
    destroyHashmap(glob->users);
    destroyHashmap(glob->drivers);
    destroyHashmap(glob->rides);

    free(glob);
}
