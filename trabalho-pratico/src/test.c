#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/io/in.h"
#include "../includes/structs/global.h"
#include "../includes/queries.h"
#include "../includes/utils.h"

/// @brief A função test_query4 executa testes à query 4.
/** 
 * @param glob A global que contém a informação da base de dados
 * 
 * @return O número de queries bem executadas
 */
int test_query4(Global * glob)
{
    char res1[8];
    int res = 0;

    sprintf(res1, "%.3f", query4("Braga", glob));
    res += equal_str(res1, "10.062");

    sprintf(res1, "%.3f", query4("Porto", glob));
    res += equal_str(res1, "10.053");

    sprintf(res1, "%.3f", query4("Lisboa", glob));
    res += equal_str(res1, "10.066");

    sprintf(res1, "%.3f", query4("Faro", glob));
    res += equal_str(res1, "10.057");

    return(res);
}

/// @brief A função test_query5 executa testes à query 5.
/** 
 * @param glob A global que contém a informação da base de dados
 * 
 * @return O número de queries bem executadas
 */
int test_query5(Global * glob)
{
    char res1[8];
    int res = 0;
    short dateA[3], dateB[3];

    stringToDate("20/01/2020", dateA);
    stringToDate("20/01/2021", dateB);
    sprintf(res1, "%.3f", query5(dateA, dateB, glob));
    res += equal_str(res1, "10.062");

    stringToDate("08/08/2016", dateA);
    stringToDate("03/05/2017", dateB);
    sprintf(res1, "%.3f", query5(dateA, dateB, glob));
    res += equal_str(res1, "10.065");

    stringToDate("08/08/2016", dateA);
    stringToDate("08/08/2019", dateB);
    sprintf(res1, "%.3f", query5(dateA, dateB, glob));
    res += equal_str(res1, "10.082");

    return(res);
}

/// @brief A função test_query6 executa testes à query 6.
/** 
 * @param glob A global que contém a informação da base de dados
 * 
 * @return O número de queries bem executadas
 */
int test_query6(Global * glob)
{
    char res1[8];
    int res = 0;
    short dateA[3], dateB[3];

    stringToDate("20/01/2020", dateA);
    stringToDate("20/01/2021", dateB);
    sprintf(res1, "%.3f", query6("Faro", dateA, dateB, glob));
    res += equal_str(res1, "7.500");

    stringToDate("01/02/2021", dateA);
    stringToDate("01/03/2021", dateB);
    sprintf(res1, "%.3f", query6("Setúbal", dateA, dateB, glob));
    res += equal_str(res1, "7.590");

    stringToDate("01/01/2020", dateA);
    stringToDate("01/01/2021", dateB);
    sprintf(res1, "%.3f", query6("Braga", dateA, dateB, glob));
    res += equal_str(res1, "7.490");

    return(res);
}

/// @brief A função main irá servir para a execução de testes
/**
 * Assumindo a base de dados fornecida na primeira fase do projeto, a
 * função main irá testar as várias queries implementadas.
 * 
 * Começando por medir o tempo que demora a fazer a leitura da base de
 * dados, a main irá depois, também, avaliar o número de queries executadas,
 * o tempo total de execução das mesmas e o tempo médio individual.
 * 
 * Por fim, irá imprimir as estatísticas dos resultas obtidos nas medições
 * anteriores.
 * 
 * @param argc Número de argumentos fornecidos ao programa
 * 
 * @param args Argumentos fornecidos ao programa
 * 
 * @return Devolve 0 em caso de sucesso
 */ 
int main(int argc, char * args[])
{	
	if (argc > 1)
	{
        clock_t start, parse, end;
        double time_parse, time_query, time_total;
        start = clock();

		Global * glob = createGlobal();
		char * truePath = (char*) malloc(sizeof(char) * 30);

		strcpy(truePath, args[1]);
		strcat(truePath, "/users.csv");
		readFile(truePath, 1, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/drivers.csv");
		readFile(truePath, 2, glob);

		strcpy(truePath, args[1]);
		strcat(truePath, "/rides.csv");
		readFile(truePath, 3, glob);

        parse = clock();

        int q = 0;

        q += test_query4(glob);
        q += test_query5(glob);
        q += test_query6(glob);

        end = clock();

        time_parse = ((double) (parse - start)) / CLOCKS_PER_SEC;
        time_query = ((double) (end - parse)) / CLOCKS_PER_SEC;
        time_total = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("[TOTAL] CPU TIME - %f\n", time_total);
        printf("[PARSE] CPU TIME - %f\n", time_parse);
        printf("[ALL QUERY] CPU TIME - %f\n", time_query);
        printf("[ALL QUERY] SCORE - %d/10\n", q);
        printf("[SINGLE QUERY] CPU TIME - %f\n", time_query/10);
	}

	return(0);
}