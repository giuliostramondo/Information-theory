/*
 * FSA.hpp
 * Created on: June 24, 2014
 * Author: Giulio Stramondo
 */

#ifndef FSA_HPP
#define FSA_HPP
#include <map>
#include <unordered_set>
#include <boost/functional/hash.hpp>

class State{
private:

public:
unsigned int id;
State();
State(unsigned int id);
State(unsigned int id,std::string name);
~State();
unsigned int get_id() const;
std::string label;
bool operator==(State &s);
bool operator<( State &s);
};

namespace std {
  template <>
  struct hash<State>
  {
    typedef State      argument_type;
    typedef std::size_t  result_type;

    result_type operator()(const State & t) const
    {
      std::size_t val { 0 };
      boost::hash_combine(val,t.id);

      return val;
    }
  };
}

inline bool operator< (const State &s1, const State &s2) {
    return  s1.get_id() < s2.get_id();
}

inline bool operator== (const State &s1, const State &s2) {
    return  s1.get_id() == s2.get_id();
}

class Fsa{
private:
std::unordered_set<char> alphabet;
std::map<unsigned int, State> states;
std::map<State, std::map<char,State> >transitions;
State initial_state;
std::unordered_set<State> final_states;
unsigned int states_number;
public:
Fsa();
~Fsa();
void set_alphabet(std::unordered_set<char> alph);
void add_char_to_alphabet(char a);
void set_final_state(State s);
void add_transition(State from, char c, State to);
void set_initial_state(State s);
State get_initial_state();
std::map<unsigned int, State> get_states();
std::unordered_set<char> get_alphabet();
std::map<State, std::map<char,State> > get_transitions();
std::unordered_set<State> get_final_states();
State create_state();
State create_state(std::string name);
bool is_state_final(State s);
bool parse_string(std::string input);
};




#endif
