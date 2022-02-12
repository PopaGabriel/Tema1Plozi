run: censor.o censor_group.o error.o
	gcc -g -o censor censor.o censor_group.o error.o
	valgrind --track-origins=yes --leak-check=full ./censor bad_words

censor.o: censor.c
	gcc -g censor.c -c -Wall

censor_group.o: censor_group.c censor_group.h
	gcc -g -c censor_group.c

error.o: error.c error.h
	gcc -g -c error.c


clean:
	rm censor
	rm censor.o
	rm censor_group.o

