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
private:
    int id_;
    bool accepting_state_;
    unordered_map<string, DFAState *> neighbours_;
    vector<NFAState *> generators_;

public:
    // Constructor of the class.
    explicit DFAState(bool accepting_state);

    // Getters for member variables of instance.
    int get_id() const;

    bool is_accepting_state() const;

    const unordered_map<string, DFAState *> &get_neighbours() const;

    const vector<NFAState *> &get_generators() const;

    // Public functions of instance.
    void AddNeighbour(string input, DFAState *neighbour);

};


#endif //LEXGEN_DFASTATE_H
