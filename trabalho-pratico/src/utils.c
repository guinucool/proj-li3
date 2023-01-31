#include <string.h>
#include <math.h>
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

void null(void * element)
{
    return;
}

void nullMap(void * element, void (*function)(void*,void*), void * second)
{
    function(element, second);
}

int isPrime(int num)
{
    int res = 1;

    if (num <= 1) res = 0;

    if (num % 2 == 0 && num > 2) res = 0;

    for(int i = 3; i < num / 2 && res; i+= 2) if (num % i == 0) res = 0;

    return res;
}

/// @brief A função hashKey_Int cria uma hash de procura, cuja chave é um Int.
/**
 * A função hashKey_Int cria uma hash de procura, cuja chave é um Int, usando
 * o módulo (chave mod tamanho do hashmap) para criar a hash que
 * corresponderá à posição do elemento na hashmap.
 * 
 * @param key O void pointer da chave do elemento pretendido.
 * @param size O tamanho do hashmap para o qual vai ser criada a chave.
 */
int hashKey_Int(void * key, int size)
{
    int *true_Key = ((int*) key);

    return(*true_Key % size);
}

/// @brief A função hashKey_Str cria uma hash de procura, cuja chave é uma String.
/**
 * A função hashKey_Str cria uma hash de procura, cuja chave é uma String, usando 
 * o somatorio do modulo do resultado da multiplicação dos caracteres com as respetivas posições 
 * na string. O resultado deste somatorio será a posição do elemento na hashmap.
 * 
 * @param str O void pointer da chave do elemento pretendido.
 * @param size O tamanho do hashmap para o qual vai ser criada a chave.
 */
int hashKey_Str(void * str, int size)
{
    const char * s = str;
    const int n = strlen(s);
    const int p = 111111;
    int hash = 0;
    long p_pow = 1;

    for (int i = 0; i < n; i++)
    {
        hash = (hash + s[i] * p_pow) % size;
        p_pow = (p_pow * p) % size;
    }

    // return hash < 0 ? hash * -1 : hash;
    return hash;
}

void strtop(char * str)
{
    for (int i = 0; str[i] != '\0'; i++)
        toupper(str[i]);
}