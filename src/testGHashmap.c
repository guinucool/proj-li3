#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

/*typedef struct user {
    int id;
    char * name;
}*USER;


int main()
{
    USER user = g_malloc(sizeof(USER));
    user->id = 1;
    user->name = "João Cordeiro";

    void *userkey = (int*)user->id;

    GHashTable * userTable = g_hash_table_new(g_int_hash, g_int_equal);

    g_hash_table_insert(userTable, userkey, user);

    printf("Hello world! The user id is %d and name is %s!\n", (int)userkey, user->name);
    return(0);
}*/

typedef struct mystruct {
    int a,c;
    char * b,* d;
}mystruct;

int main()
{
    GHashTable *table;
    struct mystruct *my;

    table = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, g_free);
    my = g_malloc(sizeof *my);
    my->a = 1;
    my->b = "hello";
    my->c = 5;
    my->d = "test";

    gpointer value = my;

    g_hash_table_insert(table, GINT_TO_POINTER(my->a), value);
}
