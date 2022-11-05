all: ./bin/testDriver ./bin/testHashmap ./bin/testDrivers

./bin/testDrivers : ./src/testDrivers.c ./object/drivers.o
	gcc -g -o ./bin/testDrivers ./src/testDrivers.c ./object/hashmap.o ./object/driver.o ./object/drivers.o

./object/drivers.o : ./src/drivers.c ./include/drivers.h ./object/hashmap.o
	gcc -g -c -o ./object/drivers.o ./src/drivers.c

./bin/testHashmap : ./src/testHashmap.c ./object/hashmap.o
	gcc -g -o ./bin/testHashmap ./src/testHashmap.c ./object/hashmap.o

./object/hashmap.o : ./src/hashmap.c ./include/hashmap.h
	gcc -g -c -o ./object/hashmap.o ./src/hashmap.c

./bin/testDriver : ./src/testDriver.c ./object/driver.o
	gcc -g -o ./bin/testDriver ./src/testDriver.c ./object/driver.o

./object/driver.o : ./src/driver.c ./include/driver.h
		gcc -g -c -o ./object/driver.o ./src/driver.c

clean:
	rm ./bin/* ./object/*