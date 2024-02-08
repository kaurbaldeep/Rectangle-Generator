make: AlgorithmsAndComplexity.o
	g++ AlgorithmsAndComplexity.o -o make
AlgorithmsAndComplexity.o: AlgorithmsAndComplexity.cpp
	g++ -c AlgorithmsAndComplexity.cpp
clean: 
	rm *.o
	rm make
	rm *.csv
debug: make
	gdb ./make

run: make
	./make