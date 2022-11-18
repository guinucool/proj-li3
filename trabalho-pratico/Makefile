CC=gcc
CFLAGS=-Wall -Iinc

all: directory programa-principal

directory:
	mkdir out

programa-principal: out/main.o out/in.o out/read.o out/global.o out/hashmap.o out/user.o out/driver.o out/ride.o out/date.o out/city.o out/utils.o out/queries.o
	$(CC) $(CFLAGS) $^ -o $@

out/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/in.o: src/io/in.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/read.o: src/io/read.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/queries.o: src/queries.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/city.o: src/structs/city.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/date.o: src/structs/date.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/driver.o: src/structs/driver.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/global.o: src/structs/global.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/hashmap.o: src/structs/hashmap.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/ride.o: src/structs/ride.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/user.o: src/structs/user.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean: files dirs

files:
	rm programa-principal out/*

dirs:
	rmdir out