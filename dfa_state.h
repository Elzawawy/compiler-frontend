//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_DFASTATE_H
#define LEXGEN_DFASTATE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "nfa_state.h"

using namespace std;

class DFAState {
private:
    int id_;
    bool accepting_state_;
    unordered_map<string, DFAState *> neighbours_;
    unordered_set<NFAState *> generators_;

public:
    // Constructor of the class.
    explicit DFAState(bool accepting_state, unordered_set<NFAState *> generators);

    // Getters for member variables of instance.
    int get_id() const;

    bool is_accepting_state() const;

    const unordered_map<string, DFAState *> &get_neighbours() const;

    const unordered_set<NFAState *> &get_generators() const;

    // Public functions of instance.
    void AddNeighbour(string input, DFAState *neighbour);

};

class DFANormalState : public DFAState {
public:
    DFANormalState(bool acceptingState, const unordered_set<NFAState *> &generators);
};

class DFAAcceptanceState : public DFAState {
public:
    DFAAcceptanceState(bool acceptingState, const unordered_set<NFAState *> &generators, string token);

    string get_token();

    void set_token(string token);

private:
    string token;
};


#endif //LEXGEN_DFASTATE_H
