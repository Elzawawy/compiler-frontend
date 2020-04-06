//
// Created by omar_swidan on 03/04/20.
//

#ifndef LEXGEN_MIN_DFA_H
#define LEXGEN_MIN_DFA_H

#include "dfa_state.h"

unordered_set<DFAState *>  partitioning(DFAState *** transitionTable , unordered_set<DFAState *> listofstates);

DFAState ***   constructTransitiontable( DFAState* root , unordered_set<DFAState *> listofstates, const string &out_file_relative_path);


#endif //LEXGEN_MIN_DFA_H
