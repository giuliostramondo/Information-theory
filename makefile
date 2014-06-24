inf_theory: main.o fsa.o
	g++ -std=c++11 -o inf_theory main.o fsa.o

main.o: main.cpp FSA.hpp
	g++ -std=c++11  -o main.o -c main.cpp

fsa.o: FSA.hpp FSA.cpp
	g++ -std=c++11 -o fsa.o -c FSA.cpp 

clean: 
	 rm *.o && rm inf_theory && rm *~
