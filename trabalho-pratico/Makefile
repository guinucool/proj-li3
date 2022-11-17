all: ../bin/testDriver ../bin/testHashmap ../bin/testDrivers ../bin/testUser ../bin/testRide ../bin/testUsers ../bin/testQuery1

../bin/testQuery1 : ./src/testQuery1.c ./out/queries.o ./out/hashmap.o ./out/driver.o ./out/drivers.o ./out/parser.o ./out/ride.o ./out/utilities.o ./out/rides.o
	gcc -g -o ../bin/testQuery1 ./src/testQuery1.c ./out/queries.o ./out/hashmap.o ./out/driver.o ./out/drivers.o ./out/parser.o ./out/ride.o ./out/utilities.o ./out/rides.o

./out/queries.o : ./src/queries/queries.c ./inc/queries/queries.h ./out/parser.o
	gcc -g -c -o ./out/queries.o ./src/queries/queries.c ./out/parser.o

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

../bin/testRide : ./src/testRide.c ./out/rides.o ./out/hashmap.o ./out/parser.o ./out/ride.o ./out/utilities.o ./out/drivers.o ./out/driver.o 
	gcc -g -o ../bin/testRide ./src/testRide.c ./out/rides.o ./out/hashmap.o ./out/parser.o ./out/ride.o ./out/utilities.o ./out/drivers.o ./out/driver.o 

./out/rides.o : ./src/rides/rides.c ./inc/rides/rides.h ./out/utilities.o
	gcc -g -c -o ./out/rides.o ./src/rides/rides.c  ./out/utilities.o

./out/ride.o : ./src/rides/ride.c ./inc/rides/ride.h
	gcc -g -c -o ./out/ride.o ./src/rides/ride.c

./out/utilities.o : ./src/utils/utilities.c ./inc/utils/utilities.h
	gcc -g -c -o ./out/utilities.o ./src/utils/utilities.c

./out/parser.o: ./src/utils/parser.c ./inc/utils/parser.h ./out/rides.o ./out/drivers.o ./out/hashmap.o
	gcc -g -c -o ./out/parser.o ./src/utils/parser.c ./out/rides.o ./out/drivers.o  ./out/hashmap.o

clean:
	rm ../bin/* ./out/*