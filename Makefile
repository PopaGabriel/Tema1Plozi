run: censor.o
	cp input_stress input_aux
	gcc -g -o censor censor.o censor_group.o error.o
	valgrind --track-origins=yes --leak-check=full ./censor bad_words input_aux
	make clean_sources

no_gdb: censor.o
	rm input_aux
	cp input_stress input_aux
	gcc -g -o -O3 censor censor.o censor_group.o error.o
	./censor bad_words input_aux

censor.o: censor.c error.o censor_group.o
	gcc -g censor.c -c -Wall

censor_group.o: censor_groups/censor_group.c censor_groups/censor_group.h
	cp censor_groups/* .
	gcc -g censor_group.c -c

error.o: errors/error.c errors/error.h
	cp errors/* .
	gcc -g -c error.c


clean:
	make clean_sources
	make clean_file

clean_sources:
	rm censor
	rm censor.o
	rm censor_group.*
	rm error.*


clean_file:
	rm input_aux
