#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/utils.h"
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"

/// @brief A função test_query4 executa testes à query 4.
/** 
 * @param glob A global que contém a informação da base de dados.
 * 
 * @return O número de queries bem executadas.
 */
/*int test_query4(Global * glob)
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
 * @param glob A global que contém a informação da base de dados.
 * 
 * @return O número de queries bem executadas.
 */
/*int test_query5(Global * glob)
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
 * @param glob A global que contém a informação da base de dados.
 * 
 * @return O número de queries bem executadas.
 */
/*int test_query6(Global * glob)
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
 * @param argc Número de argumentos fornecidos ao programa.
 * 
 * @param args Argumentos fornecidos ao programa.
 * 
 * @return Devolve 0 em caso de sucesso.
 */ 
int main(int argc, char * args[])
{	
	if (argc > 2)
	{
        char * truePath = malloc(sizeof(char) * (strlen(args[1]) + 13));
        if (truePath)
        {
            char * inStr = malloc(sizeof(char) * (strlen(args[2]) + 11));
            if (inStr)
            {
                strcpy(inStr, args[2]);
                strcat(inStr, "/input.txt");

                FILE * input = fopen(inStr, "r");
                if (input)
                {
                    double * time = malloc(sizeof(double));
                    if (time)
                    {
                        int * cmd = malloc(sizeof(int));
                        if (cmd)
                        {
                            double total_time = 0.0f, parse_time = 0.0f, query_time = 0.0f;
                            double times[9][2] = { {0.0f, 0.0f} };
                            int score[9][2] = { {0,0} };

                            int count = 0;
                            char line[200];

                            while (fgets(line, 200, input) != NULL)
                            {
                                count++;
                                int * cTmp = realloc(cmd, sizeof(int) * count);
                                double * tTmp = realloc(time, sizeof(double) * count);

                                if (!cTmp || !tTmp)
                                {
                                    if (cTmp) free(cTmp);
                                    if (tTmp) free(tTmp);

                                    free(truePath);
                                    free(inStr);
                                    fclose(input);
                                    free(time);
                                    free(cmd);

                                    return 0;
                                }
                                else
                                {
                                    time = tTmp;
                                    cmd = cTmp;
                                }

                                time = tTmp;
                                cmd = cTmp;

                                cmd[count - 1] = line[0] - 48;

                                score[cmd[count-1]][1]++;
                            }
                            fclose(input);

                            Global glob = createGlobal();
                            if (glob)
                            {
                                /*clock_t start, end;

                                start = clock();

                                strcpy(truePath, args[1]);
                                strcat(truePath, "/users.csv");
                                readFile(truePath, 1, glob, NULL);

                                strcpy(truePath, args[1]);
                                strcat(truePath, "/drivers.csv");
                                readFile(truePath, 2, glob, NULL);

                                strcpy(truePath, args[1]);
                                strcat(truePath, "/rides.csv");
                                readFile(truePath, 3, glob, NULL);

                                end = clock();
                                //free(truePath);

                                /*parse_time = (double) (end - start) / CLOCKS_PER_SEC;
                                total_time = parse_time;

                                readFile(inStr, 0, glob, time);
                                //free(inStr);

                                char * path = malloc(sizeof(char));
                                if (path)
                                {
                                    char * outPath = malloc(sizeof(char));
                                    if (outPath)
                                    {
                                        for (int i = 0; i < count; i++)
                                        {
                                            total_time += time[i];
                                            query_time += time[i];

                                            if ((cmd[i] == 2 || cmd[i] == 3 || cmd[i] == 7 || cmd[i] == 8) && times[cmd[i]-1][1] == 0)
                                                times[cmd[i]-1][1] = time[i];
                                            else
                                                times[cmd[i]-1][0] = time[i];

                                            char * pTemp = realloc(path,sizeof(char) * (strlen(args[2]) + 19 + intLen(i)));
                                            char * oTemp = realloc(outPath,sizeof(char) * (29 + intLen(i)));

                                            if (!pTemp || !oTemp)
                                            {
                                                if (pTemp) free(pTemp);
                                                if (oTemp) free(oTemp);

                                                free(time);
                                                free(cmd);
                                                destroyGlobal(glob);
                                                free(path);
                                                free(outPath);

                                                return 0;
                                            }
                                            else
                                            {
                                                path = pTemp;
                                                outPath = oTemp;
                                            }

                                            path = pTemp;
                                            outPath = oTemp;

                                            strcpy(path, args[2]);
                                            sprintf(path, "/output/command%d_output.txt", i);
                                            
                                            strcpy(outPath, "\0");
                                            sprintf(outPath, "Resultados/command%d_output.txt", i);

                                            FILE * res = fopen(outPath, "r");
                                            FILE * out = fopen(path, "r");

                                            if (!res || !out)
                                            {
                                                printf("HELLO!");

                                                /*if (res) fclose(res);
                                                if (out) fclose(out);

                                                free(time);
                                                free(cmd);
                                                destroyGlobal(glob);
                                                free(path);
                                                free(outPath);

                                                return 0;
                                            }

                                            //score[cmd[i]-1][0] += equal_file(res, out);
                                        }
                                        free(outPath);
                                    }
                                    free(path);
                                }*/
                                destroyGlobal(glob);

                                printf("[TOTAL]---------EXECUTION TIME - %f\n", total_time);
                                printf("[PARSE]---------EXECUTION TIME - %f\n", parse_time);
                                printf("[ALL QUERIES]---EXECUTION TIME - %f\n", query_time);
                                for (int i = 0; i < 9; i++)
                                {
                                    printf("[QUERY %d]-------SCORE - %d/%d\n", i+1, score[i][0], score[i][1]);
                                    if (i == 1 || i == 2 || i == 6 || i ==7) printf("[QUERY %d]-FIRST EXECUTION TIME - %f\n", i+1, times[i][1]);
                                    printf("[QUERY %d]-------EXECUTION TIME - %f\n", i+1, times[i][0]/score[i][1]);
                                }
                            }
                            free(cmd);
                        }
                        free(time);
                    }
                }
            }
        }
        
        /*clock_t start, parse, end;
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
        time_total = ((double) (end - start)) / CLOCKS_PER_SEC;*/
        /*printf("[TOTAL] CPU TIME - %f\n", time_total);
        printf("[PARSE] CPU TIME - %f\n", time_parse);
        printf("[ALL QUERY] CPU TIME - %f\n", time_query);
        printf("[ALL QUERY] SCORE - %d/10\n", q);
        printf("[SINGLE QUERY] CPU TIME - %f\n", time_query/10);*/
	}

	return 0;
}