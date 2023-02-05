#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/utils.h"
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"

/// @brief A função main irá servir para a execução de testes.
/**
 *  A função main irá servir para a execução de testes.
 * 
 *  Irá receber como argumentos o caminho para o dataset no qual se quer executar
 *  os testes e o caminho para uma pasta de testes, que irá conter um ficheiro (input.txt)
 *  com os comandos pretendidos para o teste, e uma pasta (output) onde estarão os
 *  resultados desses comandos.
 * 
 *  Durante a execução, irá registar os tempos de execução de cada comando
 *  e do parsing de dados, avaliando, no final, se os resultados obtidos
 *  correspodem aos pretendidos.
 * 
 *  Por fim, imprimirá as pontuações e avaliações a que chegou.
 * 
 *  @param argc Número de argumentos fornecidos ao programa.
 * 
 *  @param args Os argumentos fornecidos ao programa.
 * 
 *  @return O sucesso na conclusão do programa.
 */
int main(int argc, char * args[])
{	
	if (argc > 2)
	{
        char * truePath = malloc(sizeof(char) * (strlen(args[1]) + 13));
        char * inStr = malloc(sizeof(char) * (strlen(args[2]) + 11));

        strcpy(inStr, args[2]);
        strcat(inStr, "/input.txt");

        FILE * input = fopen(inStr, "r");

        double total_time = 0.0f, parse_time = 0.0f, query_time = 0.0f;
        double times[9][2] = { {0.0f, 0.0f} };
        int score[9][2] = { {0,0} };

        int count = 0;
        char line[200];

        double * time = malloc(sizeof(double));
        int * commands = malloc(sizeof(int));

        while (fgets(line, 200, input) != NULL)
        {
            count++;
            if (count > 1) commands = realloc(commands, sizeof(int) * (count));
            if (count > 1) time = realloc(time, sizeof(double) * (count));

            commands[count - 1] = (int)(line[0] - 48);
            time[count - 1] = 0;

            score[commands[count-1]-1][1]++;
        }

        fclose(input);

        Global glob = createGlobal();
        clock_t start, end;

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
        free(truePath);

        parse_time = (double) (end - start) / CLOCKS_PER_SEC;
        total_time = parse_time;

        readFile(inStr, 0, glob, time);
        free(inStr);

        char * path = malloc(sizeof(char));
        char * outPath = malloc(sizeof(char));

        for (int i = 0; i < count; i++)
        {
            total_time += time[i];
            query_time += time[i];

            if ((commands[i] == 2 || commands[i] == 3 || commands[i] == 7 || commands[i] == 8) && times[commands[i]-1][1] == 0)
                times[commands[i]-1][1] = time[i];
            else
                times[commands[i]-1][0] = time[i];

            char * pTemp = realloc(path,sizeof(char) * (strlen(args[2]) + 23 + intLen(i+1)));
            char * oTemp = realloc(outPath,sizeof(char) * (29 + intLen(i+1)));

            if (!pTemp || !oTemp)
            {
                if (pTemp) free(pTemp);
                if (oTemp) free(oTemp);

                free(time);
                free(commands);
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

            sprintf(path, "%s/output/command%d_output.txt", args[2], i+1);
                                            
            strcpy(outPath, "\0");
            sprintf(outPath, "Resultados/command%d_output.txt", i+1);

            FILE * res = fopen(outPath, "r");
            FILE * out = fopen(path, "r");

            if (!res || !out)
            {
                if (res) fclose(res);
                if (out) fclose(out);

                free(time);
                free(commands);
                destroyGlobal(glob);
                free(path);
                free(outPath);

                return 0;
            }

            score[commands[i]-1][0] += equal_file(res, out);
            fclose(res);
            fclose(out);
        }

        free(commands);
        free(time);

        free(outPath);
        free(path);

        printf("--=== [TEST RESULTS] ===--\n");
        printf("[TOTAL]---------EXECUTION TIME - %f\n", total_time);
        printf("[PARSE]---------EXECUTION TIME - %f\n", parse_time);
        printf("[ALL QUERIES]---EXECUTION TIME - %f\n", query_time);
        for (int i = 0; i < 9; i++)
        {
            printf("[QUERY %d]-------SCORE - %d/%d\n", i+1, score[i][0], score[i][1]);
            if (i == 1 || i == 2 || i == 6 || i == 7) printf("[QUERY %d]-FIRST EXECUTION TIME - %f\n", i+1, times[i][1]);
            printf("[QUERY %d]-------EXECUTION TIME - %f\n", i+1, times[i][0]/score[i][1]);
        }

        destroyGlobal(glob);
    }
	return 0;
}