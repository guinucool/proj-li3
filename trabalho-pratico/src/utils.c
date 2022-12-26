#include <string.h>
#include <math.h>
#include "../includes/utils.h"


short calculateAge(short birthday[]) {
    short age, now[3];
    
    stringToDate(REF_DATE, now);

    if (now[1] > birthday[1] || (now[1] == birthday[1] && now[0] >= birthday[0])) {
        age = now[2] - birthday[2];
    } else {
        age = now[2] - birthday[2] - 1;
    }

    return age;
}

/// @brief A função string to date insere num array de 3 shorts o número referente ao dia, mês e ano de uma data.
/** 
 *  A função recebe uma String que contem uma data no formato "DD/MM/AAAA" e converte-a em 3 elementos
 *  do array, ou seja, "DD" -> data[0] = DD, "MM" -> data[1] = MM e "AAAA" -> data[2] = "AAAA".
 * 
 *  @param str  String que contem a data.
 *  @param date Array de shorts que receberá a data.
 */ 
void stringToDate(char* str,short int* date)
{    
    date[0] = (short)(10*(str[0]-48)+(str[1]-48));
    date[1] = (short)(10*(str[3]-48)+(str[4]-48));
    date[2] = (short)(1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48));
}

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

/// @brief A função equal compara duas datas.
/** 
 *  A função datecmp compara duas datas, comparando cada elemento da primeira data  
 *  ao respetivo elemento da segunda data pela ordem ano->mês->dia, verificando qual é maior.
 * 
 * @param dateA Data nº 1.
 * @param dateB Data nº 2.
 * 
 * @return Retorna -1 caso a dateA seja menor que a dateB, retorna 1 caso a dateA seja maior que a dateB e retorna 0 caso as datas sejam iguais.
 */ 
int datecmp(short * dateA, short * dateB)
{
    for (int i = 2; i >= 0; i--)
    {
        if (dateA[i] < dateB[i]) return -1;
        if (dateA[i] > dateB[i]) return 1;
    }

    return 0;
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

/// @brief A função modifica uma data para o dia seguinte.
/** 
 *  A função modifica uma data para o dia seguinte, incrementando 1 valor a data, tendo em conta 
 *  as mudanças de mês e ano.
 * 
 * @param date Data a ser mudada.
 */ 
void nextDay(short date[3])
{    
    short day = 31;
    if ((date[1] < 8 && date[1] % 2 == 0) || (date[1] >= 8 && date[1] % 2 == 1)) day = 30;
    if (date[1] == 2)
    {
        if (date[2] % 4 == 0) day = 29;
        else day = 28;
    }
    short month = 12;

    date[0]++;
    
    if (date[0] > day)
    {
        date[0] = 1;
        date[1]++;
    }
    
    if (date[1] > month)
    {
        date[1] = 1;
        date[2]++;
    }
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

