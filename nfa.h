//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_NFA_H
#define LEXGEN_NFA_H

using namespace std;

#include <string>
#include <unordered_set>
#include "nfa_state.h"

class NFA {
public:
    NFA();
    NFAState regex_to_nfa(string regex, unordered_set<string> input_table);

};


#endif //LEXGEN_NFA_H
