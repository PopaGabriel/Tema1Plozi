build:
	gcc -g censor.c -o censor -Wall
run: censor.o censor_group.o
	gcc -g -o censor censor.o censor_group.o
	valgrind --track-origins=yes --leak-check=full ./censor bad_words

censor.o: censor.c
	gcc -g censor.c -c -Wall

censor_group.o: censor_group.c censor_group.h
	gcc -g -c censor_group.c

run_no_memory:
	./censor input
clean:
	rm censor
	rm censor.o
	rm censor_group.o

