#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/date.h"
#include "../../includes/utils.h"

/// @brief A função createDate cria uma variável do tipo Date.
/**
 * A função createDate cria uma variável do tipo Date, associando
 * cada propriedade a cada posição respetiva do array do tipo
 * Date de 3 elementos.
 * 
 * O primeiro elemento será o dia, o segundo o mês e o terceiro o ano.
 * 
 * @param day O dia da data a ser criada.
 * @param month O mês da data a ser criada.
 * @param year O ano da data a ser criada.
 * @param res O local onde a data criada vai ser armazenada.
 */ 
void createDate(short day, short month, short year, Date res)
{   
    res[0] = day;
    res[1] = month;
    res[2] = year;
}

/// @brief A função nextDay modifica uma data para o dia seguinte.
/** 
 * A função nextDay modifica uma data para o dia seguinte,
 * incrementando 1 valor à data, tendo em conta 
 * as mudanças de mês e ano.
 * 
 * @param date A data a ser mudada.
 */ 
void nextDay(Date date)
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

/// @brief A função debugPrintDate imprime uma Date.
/**
 * A função debugPrintDate imprime uma variável
 * do tipo Date para fins de debugging.
 * 
 * @param date A data a imprimir.
 */ 
void debugPrintDate(Date date)
{
    printf("[VAR](Date) {\n    day: %d\n    month: %d\n    year: %d\n}\n",
        date[0],
        date[1],
        date[2]
    );
}

/// @brief A função parseDate transforma uma string numa Date.
/**
 * A função parseDate transforma uma string devidamente
 * formatada numa variável do tipo Date.
 * 
 * @param str A string a ser transformada.
 * @param date Local onde a data criada será armazenada.
 */ 
void parseDate(char * str, Date date)
{
    short day, month, year;

    day = (short)(10*(str[0]-48)+(str[1]-48));
    month = (short)(10*(str[3]-48)+(str[4]-48));
    year = (short)(1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48));

    createDate(day,month,year,date);

    /*if(str[2] == '/' && 
       str[5] == '/' &&
       strlen(str) == 10 &&
       charIsPosInt(str[0]) &&
       charIsPosInt(str[1]) &&
       charIsPosInt(str[3]) &&
       charIsPosInt(str[4]) &&
       charIsPosInt(str[6]) &&
       charIsPosInt(str[7]) &&
       charIsPosInt(str[8]) &&
       charIsPosInt(str[9])
      ){
        day = (short)(10*(str[0]-48)+(str[1]-48));
        month = (short)(10*(str[3]-48)+(str[4]-48));
        year = (short)(1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48));
        if(day <= 31 && month <= 12){
            createDate(day,month,year,date);
        }
            
    }*/
}

/// @brief A função datecmp compara duas datas.
/** 
 * A função datecmp compara duas datas, comparando cada elemento da primeira data  
 * ao respetivo elemento da segunda data pela ordem ano->mês->dia, verificando qual é mais
 * recente.
 * 
 * Retorna -1 caso a dateA seja mais antiga que a dateB,
 * retorna 1 caso a dateA seja mais recente que a dateB
 * e retorna 0 caso as datas sejam iguais.
 * 
 * @param dateA A data 1.
 * @param dateB A data 2.
 * 
 * @return O resultado da comparação das datas.
 */ 
int datecmp(Date dateA, Date dateB)
{
    for (int i = 2; i >= 0; i--)
    {
        if (dateA[i] < dateB[i]) return -1;
        if (dateA[i] > dateB[i]) return 1;
    }

    return 0;
}

/// @brief A função calculateAge calcula a idade de uma Date.
/**
 * A função calculateAge calcula a idade (em anos) de
 * uma Date, considerando para tal a Data de referência.
 * 
 * @param date A data da qual se quer saber a idade.
 * 
 * @return A idade em anos.
 */ 
short calculateAge(Date date)
{
    Date ref = REF_DATE;
    short res;

    if (date[1] < ref[1] || (date[1] == ref[1] && date[0] <= ref[0]))
        res = ref[2] - date[2];
    else
        res = ref[2] - date[2] - 1;

    return res;
}