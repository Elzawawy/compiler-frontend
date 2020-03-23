//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_DFASTATE_H
#define LEXGEN_DFASTATE_H

#include <vector>
#include <unordered_map>
#include "nfa_state.h"

using namespace std;

class DFAState {
public:
    explicit DFAState(bool accepting_state);
    void add_neighbour(string input, DFAState* neighbour);

    // Getters for member variables of instance.
    int getId() const;
    const unordered_map<string, DFAState *> &getNeighbours() const;
    bool isAccepting_state() const;

private:
    int id;
    bool accepting_state;
    unordered_map<string, DFAState *> neighbours;
    vector<NFAState*> generators;
public:
    const vector<NFAState *> &getGenerators() const;

};


#endif //LEXGEN_DFASTATE_H
