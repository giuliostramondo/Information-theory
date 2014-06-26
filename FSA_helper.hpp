/*
 * FSA_helper.hpp
 * Created on: June 25, 2014
 * Author: Giulio Stramondo
 */


#ifndef FSA_helper_HPP
#define FSA_helper_HPP

#include "FSA.hpp"
#include <list>

class FSA_helper{
	private:
		static std::unordered_set<State> FSA_clean_post_accessible(Fsa *a);
  		static int FSA_clean_post_accessible_recursion(Fsa *a, std::unordered_set<State> *post_accessible,State s,std::unordered_set<State> *called_states);

	public:
		static void FSA_clean(Fsa *a);
		static std::unordered_set<State> reachable_states(Fsa *a, State starting_state);
};

#endif
