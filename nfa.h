// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_NFA_H
#define LEXGEN_NFA_H

using namespace std;

#include <iostream>
#include<stack>
#include <string>
#include <unordered_set>
#include "nfa_state.h"

class NFA {

public:

    NFA();
    NFAState regex_to_nfa();

private:
    NFAState* concat(NFAState* first_nfa_state,NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map);
    NFAState* or_combiner(NFAState* first_nfa_state,NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map);
    NFAState* kleene_and_plus(NFAState* nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map,bool kleene);
    NFAState* construct_one_transition_state(string transition, vector < pair<NFAState* , NFAState *>>* start_to_acceptance_map);
    string infix_to_postfix(string regex,vector<string>input_table);
    NFAState* postfix_to_NFA(string postfix,vector<string>input_table);
    string resolve_backslash(string transition);
    int precedence_decision(string operator_symbol);
    bool isOperator(char character);



};


#endif //LEXGEN_NFA_H