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

    NFAState *regex_to_nfa(std::unordered_set<std::string> input_table, std::vector<RegularExpression> regex);

    unordered_set<string> get_input_table();


private:
    NFAState *concat(NFAState *first_nfa_state, NFAState *second_nfa_state,
                     vector<pair<NFAState *, NFAState *>> *start_to_acceptance_map, bool final_finish_state);

    NFAState *or_combiner(NFAState *first_nfa_state, NFAState *second_nfa_state,
                          vector<pair<NFAState *, NFAState *>> *start_to_acceptance_map, bool final_finish_state);

    NFAState *
    kleene_and_plus(NFAState *nfa_state, vector<pair<NFAState *, NFAState *>> *start_to_acceptance_map, bool kleene,
                    bool final_finish_state);

    NFAState *
    construct_one_transition_state(string transition, vector<pair<NFAState *, NFAState *>> *start_to_acceptance_map,
                                   bool final_finish_state);

    NFAState *postfix_to_NFA(string postfix, unordered_set<string> input_table, string regex_name);

    string resolve_backslash(string transition);

    unordered_set<string> resolve_input_table(unordered_set<string> input_table);

    NFAState *acceptance_state_generator(bool final_finish_state);

    bool isOperator(char character);

    void set_input_table(unordered_set<string> input_table);

    unordered_set<string> input_table;
};


#endif //LEXGEN_NFA_H