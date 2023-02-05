#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/structs/global.h"
#include "../includes/io/parser.h"
#include "../includes/io/interactive.h"


/// @brief A função main serve de arranque de todo o programa, seja no modo batch, seja no interativo.
/**
 * 	A função começa por criar a glob, estrutura de dados que ira conter todas as estrturas de dados necessárias
 *  à funcionalidade do programa. De seguida, é aferido se o utilizador pretende iniciar ou modo batch
 *  ou o interativo (caso o nº de argumentos inseridos for menor que 2 será o modo interativo).
 * 
 *  Depois é pedido o caminho até à base de dados e é feito o parsing de dados. Caso seja pretendido o modo batch,
 *  no imput do caminho até a base de dados terá que ser também inserido o ficheiro de texto com os comandos
 *  que se espera serem realizados e com essa informação a main inicia a execução dos mesmos. 
 * 
 *  Caso seja o modo interativo o desejado é apresentado ao utilizador um menu interatico com instruções de como 
 *  navegar o programa.
 * 
 * 	No final, a main da free a toda a memória allocada pelo programa.
 *  
 * 
 *  @param argc Número de argumentos
 * 
 *  @param args Argumentos de imput necessários ao funcionamento do programa.
 * 
 *  @return Int de indicação de sucesso de chegada ao final do programa.
*/
int main(int argc, char * args[])
{	
	Global glob = createGlobal();
	char str[200];

	if (argc < 2)
	{
		printf("Caminho até ao dataset: ");
		scanf("%s", str);
	}
	else
		strncpy(str, args[1], 200);

	char * truePath = (char*) malloc(sizeof(char) * (strlen(str) + 13));

	strcpy(truePath, str);
	strcat(truePath, "/users.csv");
	readFile(truePath, 1, glob, NULL);

	strcpy(truePath, str);
	strcat(truePath, "/drivers.csv");
	readFile(truePath, 2, glob, NULL);

	strcpy(truePath, str);
	strcat(truePath, "/rides.csv");
	readFile(truePath, 3, glob, NULL);

	if (argc > 2)
		readFile(args[2], 0, glob, NULL);
	else
		interactiveMode(glob);

	free(truePath);
	destroyGlobal(glob);

	return 1;
}