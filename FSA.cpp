#include "FSA.hpp"


Fsa::Fsa(){
	initial_state = create_state();
	states_number = 0;
}

void Fsa::set_alphabet(std::unordered_set<char> alph){
alphabet = alph;
}

void Fsa::add_char_to_alphabet(char a){
alphabet.insert(a);
}

void Fsa::set_final_state(State s){
final_states.insert(s);
}

void Fsa::add_transition(State from, char c, State to){
 this->transitions[from][c]=to;
}

void Fsa::set_initial_state(State s){
	initial_state = s;
}

State Fsa::create_state(){
	State a = *new State(states_number);
	states.insert(std::pair<unsigned int,State>(states_number, a));
	states_number++;
	return a;
}

State Fsa::create_state(std::string name){
	State a = *new State(states_number,name);
	states.insert(std::pair<unsigned int,State>(states_number, a));
	states_number++;
	return a;
}

bool Fsa::is_state_final(State s){
	std::unordered_set<State>::const_iterator res= final_states.find(s);
	if(res == final_states.end()) return false;
	return true;
}
bool Fsa::parse_string(std::string input){

	State current_state = initial_state;

	for ( std::string::iterator it=input.begin(); it!=input.end(); ++it){
		if(states.find(transitions[current_state][*it].get_id()) == states.end()){
			return false;			
		}else{
		current_state = transitions[current_state][*it];
		}
	}

	if(is_state_final(current_state)) return true;
	return false;	
}

State::State(unsigned int id){
	this->id = id;
}
State::State(){
	
}
State::~State(){
	
}

Fsa::~Fsa(){
}

State Fsa::get_initial_state(){
	return initial_state;
}

std::unordered_set<char> Fsa::get_alphabet(){
	return alphabet;
}

std::map<State, std::map<char,State> > Fsa::get_transitions(){
	return transitions;
}

State::State(unsigned int id,std::string name){
	this->id = id;
	label = name;
}

bool State::operator==(State &s){
	if(s.get_id() == get_id())return true;
	return false;
}

bool State::operator<(State &s){
	if(s.get_id() < get_id())return true;
	return false;
}

unsigned int State::get_id() const {
	return id;
}


