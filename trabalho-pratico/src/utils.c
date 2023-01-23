#include <string.h>
#include <math.h>
#include "../includes/structs/global.h"
#include "../includes/structs/hashmap.h"
#include "../includes/structs/driver.h"
#include "../includes/structs/ride.h"
#include "../includes/structs/date.h"
#include "../includes/structs/datefilter.h"
#include "../includes/utils.h"

/// @brief A função equal compara duas chaves de tipo Int.
/** 
 *  A função equal compara duas chaves de tipo Int, igualando-as.
 * 
 * @param key1 Chave nº 1.
 * @param key2 chave nº 2.
 * 
 * @return Retorna o resultado da comparação das duas chaves.
 */ 
int equal(void* key1, void* key2)
{
    return *((int*) key1) == *((int*) key2);
}

/// @brief A função equal_date é a negação da função datecmp.
int equal_date(void* key1, void* key2)
{
    return !datecmp((short*) key1, (short*) key2);
}

/// @brief A função equal_date é a negação da função strcmp.
int equal_str(void* s1,void* s2)
{
    return !(strcmp(s1,s2));
}

/// @brief A função verifica se a string contem apenas um número, ou seja, que representa um Id.
/// @param s String pode ou não representar um Id.
/// @return A função retorna 1 caso a String represente um Id ou 0 caso contrário.
int isId(char s[200]){
    int res = 1;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if(s[i]<48 || s[i]>57){
            res = 0;
        }
    }
    return res;
}

void double_to_string(double num, char* str, int precision)
{
    int whole = (int)num;
    double decimal = num - whole;
    int i = 0;
    int j = 0;
    char temp[50];

    // convert whole part to string
    while (whole != 0) {
        int lastDigit = whole % 10;
        temp[i++] = lastDigit + '0';
        whole /= 10;
    }

    // reverse the whole part
    while (i > 0)
        str[j++] = temp[--i];

    // add decimal point
    str[j++] = '.';

    // convert decimal part to string
    while (precision-- > 0) {
        decimal *= 10;
        int lastDigit = (int)decimal;
        str[j++] = lastDigit + '0';
        decimal -= lastDigit;
    }

    // add null character
    str[j] = '\0';
}

double calculate_ride_cost(Ride *ride, Global *glob)
{
    int driver_key = ride_Int(ride, 'd');
    double total = 0;

    Driver * driver = (Driver *) get(global_Hashmap(glob, 'e'), (void*)&driver_key, equal, hashKey_Int, 1);

    switch(driver_Char(driver, 'c'))
    {
        case BASIC:   // BASIC
            total = 3.25 + ride_Short(ride, 'p') * 0.62 + ride_Tip(ride); 
            break;

        case GREEN:   // GREEN
            total = 4.00 + ride_Short(ride, 'p') * 0.79 + ride_Tip(ride); 
            break;

        case PREMIUM: // PREMIUM
            total = 5.20 + ride_Short(ride, 'p') * 0.94 + ride_Tip(ride); 
            break;

        default:
            total = 0;
            break; 
    }

    return total;
}

/// @brief A função betweenDates fornece uma lista ligada de HashmapNode de 
///        Dates de um certo tipo dentro de um intervalo de tempo.
/** 
 *  A função betweenDates fornece uma lista ligada de HashmapNode de Dates de um certo tipo
 *  dentro de um intervalo de tempo, percorrendo todas as Dates do hashmap de Dates
 *  dentro desse intervalo de tempo.
 * 
 *  Quando a função encontrar alguma Date do tipo pretendido adiciona-a à lista ligada
 *  de HashmapNode de resultado.
 * 
 *  @param inf  Data em que começa o intervalo de tempo.
 *  @param up   Data em que termina o intervalo de tempo.
 *  @param type Tipo de data pretendido.
 *  @param glob Estrutura de dados global a ser atualizada.
 *  
 *  @return Retorna a lista ligada de HashmapNode de Dates no intervalo de tempo pretendido.
 */
HashmapNode * betweenDates(Date inf, Date up, char type, Global * glob)
{
    HashmapNode * result = NULL;

    while(datecmp(inf, up) <= 0)
    {
        HashmapNode * list = get(global_Hashmap(glob, 'd'), inf, equal_date, hashKey_date, 0);
        while (list != NULL)
        {
            DateFilter * filter = (DateFilter*) node_Void(list, 'd');;
            if (filter_Type(filter) == type) result = createNode(node_Void(list, 'k'), node_Void(list, 'd'), result);
            list = node_Node(list); 
        }
        nextDay(inf);
    }

    return result;
}
