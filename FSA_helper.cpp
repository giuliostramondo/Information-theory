/*
 * FSA_helper.cpp
 * Created on: June 25, 2014
 * Author: Giulio Stramondo
 */

#include "FSA_helper.hpp"
#include <iostream>

void FSA_helper::FSA_clean(Fsa *a){
	
std::unordered_set<State>  accessible;
std::list<State> to_check;
std::list<State> tmp_to_check;
std::list<State> post_accessible;
std::list<State> useful;
bool accessible_updated = true;

accessible.insert(a->get_initial_state());
to_check.push_front(a->get_initial_state());
	
while(accessible_updated){
	accessible_updated = false;
	
	std::list<State>::iterator it_to_check = to_check.begin();
	std::unordered_set<char>::iterator it_alphabet;	

	for(; it_to_check != to_check.end(); it_to_check++){
			
	for(it_alphabet = a->get_alphabet().begin(); it_alphabet != a->get_alphabet().end(); it_alphabet++){


		State tmp_state = a->get_transitions()[*it_to_check][*it_alphabet];

		if(accessible.find(tmp_state) == accessible.end()){
			accessible.insert(tmp_state);
			tmp_to_check.push_back(tmp_state);
			accessible_updated= true;
		}
	}	
		
	}	
	to_check=tmp_to_check;
	tmp_to_check.clear();
}
	std::cout<<"Accessible states: \n";
	std::unordered_set<State>::iterator it_accessible = accessible.begin();
	for(; it_accessible != accessible.end(); it_accessible++)
		std::cout<<it_accessible->get_id()<<"\n";

}
