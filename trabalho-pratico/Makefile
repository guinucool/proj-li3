all: ../bin/testDriver ../bin/testHashmap ../bin/testDrivers ../bin/testUser

../bin/testDrivers : ./src/testDrivers.c ./out/drivers.o
	gcc -g -o ../bin/testDrivers ./src/testDrivers.c ./out/hashmap.o ./out/driver.o ./out/drivers.o

./out/drivers.o : ./src/drivers/drivers.c ./inc/drivers/drivers.h ./out/hashmap.o
	gcc -g -c -o ./out/drivers.o ./src/drivers/drivers.c

../bin/testHashmap : ./src/testHashmap.c ./out/hashmap.o
	gcc -g -o ../bin/testHashmap ./src/testHashmap.c ./out/hashmap.o

./out/hashmap.o : ./src/utils/hashmap.c ./inc/utils/hashmap.h
	gcc -g -c -o ./out/hashmap.o ./src/utils/hashmap.c

../bin/testDriver : ./src/testDriver.c ./out/driver.o
	gcc -g -o ../bin/testDriver ./src/testDriver.c ./out/driver.o

./out/driver.o : ./src/drivers/driver.c ./inc/drivers/driver.h
	gcc -g -c -o ./out/driver.o ./src/drivers/driver.c

../bin/testUser : ./src/testUser.c ./out/user.o  ./out/utils.o
	gcc -g -o ../bin/testUser ./src/testUser.c ./out/user.o ./out/utils.o

./out/utils.o : ./src/utils.c ./inc/utils.h
	gcc -g -c -o ./out/utils.o ./src/utils.c

./out/user.o : ./src/users/user.c ./inc/users/user.h
	gcc -g -c -o ./out/user.o ./src/users/user.c

clean:
	rm ../bin/* ./out/*