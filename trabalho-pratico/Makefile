CC=gcc
CFLAGS=-Wall -Iincludes

all: directory programa-principal #programa-testes

directory:
	mkdir out

#programa-testes: out/test.o out/parser.o out/interpreter.o out/global.o out/hashmap.o out/user.o out/driver.o out/ride.o out/date.o out/datemap.o out/linkedlist.o out/city.o out/utils.o out/query2.o out/query3.o
#	$(CC) $(CFLAGS) $^ -o $@

programa-principal: out/main.o out/utils.o out/date.o out/list.o out/user.o out/driver.o out/ride.o out/hashmap.o out/datemap.o out/city.o out/global.o out/query1.o out/query2.o out/query3.o out/query4.o out/query5.o out/query7.o out/query9.o out/parser.o out/interpreter.o
	$(CC) $(CFLAGS) $^ -o $@

out/test.o: src/test.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/parser.o: src/io/parser.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/interpreter.o: src/io/interpreter.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query1.o: src/queries/query1.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query2.o: src/queries/query2.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query3.o: src/queries/query3.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query4.o: src/queries/query4.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query5.o: src/queries/query5.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query7.o: src/queries/query7.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/query9.o: src/queries/query9.c
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

out/list.o: src/structs/list.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/datemap.o: src/structs/datemap.c
	$(CC) $(CFLAGS) -c $^ -o $@

out/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean: files dirs

files:
	rm programa-principal out/*
	#programa-testes

dirs:
	rmdir out