#include <iostream>
#include "FSA.hpp"
#include "FSA_helper.hpp"


int main(){
Fsa a = *new Fsa();
a.add_char_to_alphabet('a');
a.add_char_to_alphabet('b');

State initial = a.create_state();
State middle = a.create_state();
State final_ = a.create_state();

State unaccessible = a.create_state();

a.set_initial_state(initial);
a.set_final_state(final_);

a.add_transition(initial,'a',middle);
a.add_transition(middle,'a',final_);
a.add_transition(middle,'b',initial);
a.add_transition(unaccessible,'b',middle);

std::string str1 ("aa");
std::string str2 ("aab");
std::string str3 ("ba");
std::string str4 ("abaa");
std::string str5 ("ababaa");

if(a.parse_string(str1)){
	std::cout<<"string 1 passed\n";
}

if(a.parse_string(str2)){
	std::cout<<"string 2 passed\n";
}

if(a.parse_string(str3)){
	std::cout<<"string 3 passed\n";
}

if(a.parse_string(str4)){
	std::cout<<"string 4 passed\n";
}

if(a.parse_string(str5)){
	std::cout<<"string 5 passed\n";
}

	FSA_helper::FSA_clean(&a);
return 0;
}
