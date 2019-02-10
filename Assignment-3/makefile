debug: my_tests.o node.o string_set.o
	g++ -o debug my_tests.o node.o string_set.o 

a.out: my_tests.o node.o string_set.o
	g++ my_tests.o node.o string_set.o

my_tests.o: node.h string_set.h my_tests.cpp
	g++ -c -g my_tests.cpp

node.o: node.cpp node.h
	g++ -c -g node.cpp

string_set.o: string_set.h node.h string_set.cpp
	g++ -c -g string_set.cpp

clean:
	rm -f my_tests.o node.o string_set.o a.out
