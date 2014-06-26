/*
 * FSA_helper.cpp
 * Created on: June 25, 2014
 * Author: Giulio Stramondo
 */

#include "FSA_helper.hpp"
#include <iostream>

int FSA_helper::FSA_clean_post_accessible_recursion(Fsa *a, std::unordered_set<State> *post_accessible,State s,std::unordered_set<State> *called_states){

	//std::cout << "Called FSA_clean_post_accessible\n"<<"state: "<<s.get_id()<<"\n";
		if(called_states->find(s)!=called_states->end()){
	//		std::cout << "Cyle detected\n";
			return 0;
	}
	called_states->insert(s);
	std::map<State, std::map<char,State> > local_transitions =  a->get_transitions();

	if(post_accessible->find(s)!=post_accessible->end()){
	//		std::cout << "state "<<s.get_id()<<" is already in the post_accessible list\n";
		return 1;
	}

	if(a->get_final_states().find(s)!=a->get_final_states().end()){
		post_accessible->insert(s);
	//	std::cout << "state "<<s.get_id()<<" is a final state, is added to the post_accessible list\n";

		std::map<State, std::map<char,State> >::iterator it_transiction = local_transitions.find(s);
		if(it_transiction != local_transitions.end() ){
		std::map<char,State>links =it_transiction->second;
		std::map<char,State>::iterator it_links =links.begin();

		for(; it_links != links.end(); it_links++){

	//		std::cout << "state "<<it_links->second.get_id()<<" char "<<it_links->first<<"\n";
			
			FSA_clean_post_accessible_recursion(a,post_accessible,it_links->second,called_states);
		}

	}
		return 1;
	}

	bool is_post_accessible=false;
	std::map<State, std::map<char,State> >::iterator it_transiction = local_transitions.find(s);
			//if(it_transiction == a->get_transitions().end() )continue;
	std::map<char,State>::iterator it_links =it_transiction->second.begin();

	for(; it_links != it_transiction->second.end(); it_links++){
	//	std::cout << "state "<<it_links->second.get_id()<<" char "<<it_links->first<<"\n";
		if (it_links->second == s)continue;
		if(FSA_clean_post_accessible_recursion(a,post_accessible,it_links->second,called_states)) is_post_accessible=true;
	}

	if(is_post_accessible){
	//	std::cout << "state "<<s.get_id()<<" reaches a final state, is added to the post_accessible list\n";
		post_accessible->insert(s);
		return 1;
	}


	return 0;

}

std::unordered_set<State> FSA_helper::FSA_clean_post_accessible(Fsa *a){
	std::unordered_set<State> post_accessible;
	std::map<unsigned int, State> local_states=a->get_states();
	std::map<unsigned int, State>::iterator it_states = local_states.begin();
	std::unordered_set<State> calls;
	for(;it_states != local_states.end(); it_states++){
	//	std::cout<<"Calling FSA_clean_post_accessible state: "<<it_states->first<<"\n";
		calls.clear();
		FSA_clean_post_accessible_recursion(a,&post_accessible,it_states->second,&calls);
	}
	return post_accessible;
}

std::unordered_set<State> FSA_helper::reachable_states(Fsa *a, State starting_state){
std::unordered_set<State>  accessible;
std::list<State> to_check;
std::list<State> tmp_to_check;
bool accessible_updated = true;

accessible.insert(starting_state);
to_check.push_front(starting_state);

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
		return accessible;
}

void FSA_helper::FSA_clean(Fsa *a){
	
std::unordered_set<State>  accessible;
std::unordered_set<State> post_accessible;
std::unordered_set<State> useful;


	accessible= reachable_states(a, a->get_initial_state());

	std::cout<<"\nAccessible states: \n";
	std::unordered_set<State>::iterator it_post_accessible = accessible.begin();
	for(; it_post_accessible != post_accessible.end(); it_post_accessible++)
		std::cout<<it_post_accessible->get_id()<<"\n";


	post_accessible = FSA_clean_post_accessible(a);


	std::cout<<"\nPost-Accessible states: \n";
	std::unordered_set<State>::iterator it_accessible = post_accessible.begin();
	for(; it_accessible != post_accessible.end(); it_accessible++)
		std::cout<<it_accessible->get_id()<<"\n";

	it_post_accessible = accessible.begin();
	for(; it_post_accessible != post_accessible.end(); it_post_accessible++){
		if(accessible.find(*it_post_accessible)!=accessible.end()){
			useful.insert(*it_post_accessible);
		}
	}

	std::cout<<"\nUseful states: \n";
	std::unordered_set<State>::iterator it_useful = useful.begin();
	for(; it_useful != useful.end(); it_useful++)
		std::cout<<it_useful->get_id()<<"\n";



}
