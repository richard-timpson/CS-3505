# My makefile - uses partial compilation
# put a tab character after the rule name, and before the command!

tester:	big_integer.o tester.o
	g++ -o tester big_integer.o tester.o 

big_integer.o:	big_integer.cpp big_integer.h
	g++ -c big_integer.cpp

tester.o:	tester.cpp big_integer.h
	g++ -c tester.cpp

clean:
	rm -f tester *.o
