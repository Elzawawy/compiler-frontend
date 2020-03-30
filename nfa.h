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
    NFAState* concat(NFAState* first_nfa_state,NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state);
    NFAState* or_combiner(NFAState* first_nfa_state,NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state);
    NFAState* kleene_and_plus(NFAState* nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map,bool kleene, bool final_finish_state);
    NFAState* construct_one_transition_state(string transition, vector < pair<NFAState* , NFAState *>>* start_to_acceptance_map, bool final_finish_state);
    string infix_to_postfix(string regex,unordered_set<string>input_table);
    NFAState* postfix_to_NFA(string postfix,unordered_set<string>input_table);
    string resolve_backslash(string transition);
    int precedence_decision(string operator_symbol);
    bool isOperator(char character);
    void resolve_input_table(unordered_set<string>*input_table);
    bool acceptance_nfa_identifier(int size_of_stack,int postfix_length,int current_iteration,char next_character);
    NFAState *acceptance_state_generator(bool final_finish_state);
};


#endif //LEXGEN_NFA_H