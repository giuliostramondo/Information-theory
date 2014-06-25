inf_theory: main.o fsa.o fsa_helper.o
	g++ -std=c++11 -o inf_theory main.o fsa.o fsa_helper.o

main.o: main.cpp FSA.hpp FSA_helper.hpp
	g++ -std=c++11  -o main.o -c main.cpp

fsa_helper.o: FSA_helper.cpp FSA_helper.hpp FSA.hpp
	g++ -std=c++11 -o fsa_helper.o -c FSA_helper.cpp
	
fsa.o: FSA.hpp FSA.cpp
	g++ -std=c++11 -o fsa.o -c FSA.cpp 

clean: 
	 rm *.o && rm inf_theory && rm *~
