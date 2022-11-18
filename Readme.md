# Gustavo:
    - Inserir info user hashmap; --DONE--
    - Inserir info user estruturas auxiliares; --DONE--
    - Interpretação da leitura; --DONE--
    - Q5; --DONE--
# Alexandra:
    - Inserir info drivers hashmap; - Done 
    - Inserir info drivers estruturas auxiliares; - Done 
    - Q4; - Done 
    - Output das queries;
# Gui:
    - Leitura de ficheiros(por linha -> chama funções); (Done)
    - Inserir info rides hashmap; (Done)
    - Inserir info rides estruturas auxiliares; (Done)
    - Q6; (Done)

# Tarefas por concluir:

# Queries:
    Q1: not done. 
    Q2: not done
    Q3: not done
    Q4: DONE(not tested) 
    Q5: DONE(not tested)
    Q6: DONE(not tested)
    Q7: not done
    Q8: not done
    Q9: not done

all: ./programa-principal

object:
	mkdir ./out

./out/utils.o: ./src/utils.c ./inc/utils.h
	gcc -g -c -o ./out/utils.o ./src/utils.c

./out/city.o: ./src/structs/city.c ./inc/structs/city.h
	gcc -g -c -o ./out/city.o ./src/structs/city.c

./out/date.o: ./src/structs/date.c ./inc/structs/date.h
	gcc -g -c -o ./out/date.o ./src/structs/date.c

./out/driver.o: ./src/structs/driver.c ./inc/structs/driver.h
	gcc -g -c -o ./out/driver.o ./src/structs/driver.c

./out/hashmap.o: ./src/structs/hashmap.c ./inc/structs/hashmap.h
	gcc -g -c -o ./out/hashmap.o ./src/structs/hashmap.c

./out/ride.o: ./src/structs/ride.c ./inc/structs/ride.h
	gcc -g -c -o ./out/ride.o ./src/structs/ride.c

./out/user.o: ./src/structs/user.c ./inc/structs/user.h
	gcc -g -c -o ./out/user.o ./src/structs/user.c

./out/global.o: ./src/structs/global.c ./inc/structs/global.h ./out/hashmap.o
	gcc -g -c -o ./out/global.o ./src/structs/global.c ./out/hashmap.o

./out/queries.o: ./src/queries.c ./inc/queries.h ./out/driver.o ./out/ride.o ./out/city.o ./out/date.o ./out/utils.o
	gcc -g -c -o ./out/queries.o ./src/queries.c ./out/driver.o ./out/ride.o ./out/city.o ./out/date.o ./out/utils.o

./out/read.o: ./src/io/read.c ./inc/io/read.h ./out/global.o ./out/hashmap.o ./out/user.o ./out/driver.o ./out/ride.o ./out/city.o ./out/date.o ./out/queries.o ./out/utils.o
	gcc -g -c -o ./out/in.o ./src/io/in.c ./out/global.o ./out/hashmap.o ./out/user.o ./out/driver.o ./out/ride.o ./out/city.o ./out/date.o ./out/queries.o ./out/utils.o

./out/in.o: ./src/io/in.c ./inc/io/in.h ./out/read.o
	gcc -g -c -o ./out/in.o ./src/io/in.c ./out/read.o

./out/main.o: ./src/main.c ./out/in.o ./out/global.out
	gcc -g -o ./out/main.o ./src/main.c ./out/in.o ./out/global.out