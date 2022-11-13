all: ../bin/testDriver ../bin/testHashmap ../bin/testDrivers ../bin/testUser ../bin/testUsers

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

../bin/testUser : ./src/testUser.c ./out/user.o
	gcc -g -o ../bin/testUser ./src/testUser.c ./out/user.o

./out/user.o : ./src/users/user.c ./inc/users/user.h
	gcc -g -c -o ./out/user.o ./src/users/user.c

../bin/testUsers : ./src/testUsers.c ./out/users.o
	gcc -g -o ../bin/testUsers ./src/testUsers.c ./out/hashmap.o ./out/user.o ./out/users.o

./out/users.o : ./src/users/users.c ./inc/users/users.h ./out/hashmap.o
	gcc -g -c -o ./out/users.o ./src/users/users.c

clean:
	rm ./bin/* ./out/*