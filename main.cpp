#include <iostream>
#include "FSA.hpp"
#include "FSA_helper.hpp"


int main(){

	//EXAMPLE 1
Fsa a = *new Fsa();
a.add_char_to_alphabet('a');
a.add_char_to_alphabet('b');

State initial = a.create_state(); //0
State middle = a.create_state();  //1
State final_ = a.create_state();  //2

State unaccessible = a.create_state();

a.set_initial_state(initial);
a.set_final_state(final_);

a.add_transition(initial,'a',middle); //0 -a->1
a.add_transition(middle,'a',final_);  //1 -a->2
a.add_transition(middle,'b',initial); //1 -b->0
a.add_transition(unaccessible,'b',middle);

std::string str1 ("aa");
std::string str2 ("aab");
std::string str3 ("ba");
std::string str4 ("abaa");
std::string str5 ("ababaa");

std::map<State, std::map<char,State> >::iterator it_transiction = a.get_transitions().begin();
std::map<char,State>::iterator it_transiction_inner;
for(;it_transiction!=a.get_transitions().end();it_transiction++){
	it_transiction_inner=it_transiction->second.begin();
	for(;it_transiction_inner!=it_transiction->second.end();it_transiction_inner++){
		std::cout <<"transactions["<<it_transiction->first.get_id()<<"]["<<it_transiction_inner->first<<"]="<<it_transiction_inner->second.get_id()<<"\n";
	}
}
std::cout<<"final: "<<final_.get_id()<<"\n";
std::map<State, std::map<char,State> > local_transitions =  a.get_transitions();
it_transiction=local_transitions.find(middle);
if(local_transitions.find(middle) == local_transitions.end())std::cout<<"bastaddu\n";
std::map<char,State>::iterator it_specific_transition = it_transiction->second.begin();
for(;it_specific_transition!=it_transiction->second.end();it_specific_transition++)
	std::cout<<"\nchar: "<<it_specific_transition->first<<" state: "<<it_specific_transition->second.get_id();

if(a.parse_string(str1)){
	std::cout<<"\nstring 1 passed\n";
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


	//EXAMPLE 2

	Fsa b = *new Fsa();

	b.add_char_to_alphabet('a');
	b.add_char_to_alphabet('b');

	 initial = b.create_state(); //0
	 middle = b.create_state();  //1
	 final_ = b.create_state();  //2

	 unaccessible = b.create_state(); // 3

	State loop1 = b.create_state(); // 4
	State loop2 = b.create_state(); // 5

	b.set_initial_state(initial);
	b.set_final_state(final_);

	b.add_transition(initial,'a',middle); //0 -a->1
	b.add_transition(middle,'a',final_);  //1 -a->2
	b.add_transition(middle,'b',initial); //1 -b->0
	b.add_transition(unaccessible,'b',middle); // 3 -b->1

	b.add_transition(initial,'b',loop1);
	b.add_transition(loop1,'a',loop2);
	b.add_transition(loop2,'b',loop1);
	b.add_transition(loop1,'b',final_);


	FSA_helper::FSA_clean(&b);

return 0;
}
