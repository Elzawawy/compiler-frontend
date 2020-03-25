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
    NFAState concat(NFAState first_nfa_state,NFAState second_nfa_state);
    NFAState or_combiner(vector<NFAState> selections, int no_of_selections);
    NFAState kleene(NFAState nfa_state);
    string infix_to_postfix(string regex);
    string pre_process_regex(string regex);
    int precedence_decision(string operator_symbol);
    string char_to_string_converter(char character);
    bool is_operator(char character);
    bool is_operand(char character);

};


#endif //LEXGEN_NFA_H