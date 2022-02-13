run: censor.o censor_group.o error.o
	cp input input_aux
	gcc -g -o censor censor.o censor_group.o error.o
	valgrind --track-origins=yes --leak-check=full ./censor bad_words input_aux

no_gdb: censor.o censor_group.o error.o
	rm input_aux
	cp input_stress input_aux
	gcc -g -o -O3 censor censor.o censor_group.o error.o
	./censor bad_words input_aux

censor.o: censor.c
	gcc -g censor.c -c -Wall

censor_group.o: censor_group.c censor_group.h
	gcc -g -c censor_group.c

error.o: error.c error.h
	gcc -g -c error.c


clean:
	make clean_sources
	make clean_file

clean_sources:
	rm censor
	rm censor.o
	rm censor_group.o

clean_file:
	rm input_aux
