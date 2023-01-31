#include <ctype.h>
#include <math.h>
#include <string.h>
#include "../includes/utils.h"

/// @brief A função equal compara duas chaves de tipo Int.
/** 
 * A função equal compara duas chaves de tipo Int, retornando
 * 1 caso sejam igual ou 0 caso sejam diferentes.
 * 
 * @param key1 A chave 1.
 * @param key2 A chave 2.
 * 
 * @return O resultado da comparação das duas chaves.
 */ 
int equal(void* key1, void* key2)
{
    return *((int*) key1) == *((int*) key2);
}

/// @brief A função equal_str compara duas chaves de tipo String.
/** 
 * A função equal compara duas chaves de tipo String, retornando
 * 1 caso sejam igual ou 0 caso sejam diferentes.
 * 
 * @param s1 A chave 1.
 * @param s2 A chave 2.
 * 
 * @return O resultado da comparação das duas chaves.
 */
int equal_str(void* s1,void* s2)
{
    return !(strcmp(s1,s2));
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

/// @brief A função null funciona como um NULL para funções.
/**
 * A função null será usada como um NULL para
 * parâmetros em que é necessário fornecer uma
 * função, porém não sendo pretendido que essa
 * função faça alterações.
 * 
 * @param element O suposto elemento que iria ser alterado.
 */
void null(void * element)
{
    return;
}

/// @brief A função nullMap funciona como um NULL para funções de map.
/**
 * A função nullMap será usada como um NULL para
 * parâmetros em que é necessário fornecer uma
 * função map, porém o elemento que deveria ser
 * mapeado não é mapeável.
 * 
 * @param element O suposto elemento que iria ser mapeado.
 * @param function A função que ia ser usada no mapeamento.
 * @param second O segundo argumento da função que ia ser usada.
 * 
 * @return O suposto número de operações executadas.
 */ 
int nullMap(void * element, void (*function)(void*,void*), void * second)
{
    function(element, second);
    return 1;
}

/// @brief A função isId verifica se uma string contém apenas números.
/**
 * A função isId verifica se uma string contém apenas números, sendo
 * assim possível assumir que esta se trata de um Id de Driver.
 * 
 * Retornará, então, 1 ou 0 dependo da conclusão a que chegar.
 * 
 * @param s A string a ser verificada.
 * 
 * @return A conclusão a que chegou.
 */
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

/// @brief A função isPrime verifica se um número é um primo.
/**
 * A função isPrime verifica se um número é um primo,
 * retornando 1 ou 0 dependendo da conclusão
 * a que chegou.
 * 
 * @param num O número a ser verificado.
 * 
 * @return A conclusão a que chegou.
 */
int isPrime(int num)
{
    int res = 1;

    if (num <= 1) res = 0;

    if (num % 2 == 0 && num > 2) res = 0;

    for(int i = 3; i < num / 2 && res; i+= 2) if (num % i == 0) res = 0;

    return res;
}

int charIsPosInt(char caracter)
{
    return caracter > 48 && caracter <= 57;
}

/// @brief A função strtop transforma uma string em letras maiscúlas.
/**
 * A função strtop converte todos caracteres de uma string
 * em maiscúlos.
 * 
 * @param str A string a ser transformada.
 */
void strtop(char * str)
{
    for (int i = 0; str[i] != '\0'; i++)
        toupper(str[i]);
}

/// @brief A função intLen calcula o numero de digitos que um int tem.
/**
 * A função intLen faz divisões inteiras por 10 do int a ser processado até que este
 * seja igual a 0, o número de divisoes realisadas é o número de digitos do int.
 * 
 * @param value O int a ser processado.
 * 
 * @return O número de dígitos do int.
 */
int intLen(int value)
{
    int count = 0;
    while(value != 0)
    {
        value /= 10;
        count++;
    }
    return count;
}