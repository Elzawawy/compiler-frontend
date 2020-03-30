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
    static int id_counter;
    int id_;
    unordered_map<string, DFAState *> neighbours_;
    unordered_set<NFAState *> generators_;

public:
    // Constructor of the class.
    DFAState();

    explicit DFAState(unordered_set<NFAState *> generators);

    // Getters for member variables of instance.
    int get_id() const;

    const unordered_map<string, DFAState *> &get_neighbours() const;

    const unordered_set<NFAState *> &get_generators() const;

    // Public functions of instance.
    void AddNeighbour(const string &input, DFAState *neighbour);

    bool operator==(DFAState &other) const;

};

class DFANormalState : public DFAState {
public:
    explicit DFANormalState(const unordered_set<NFAState *> &generators);
};

class DFAAcceptanceState : public DFAState {
public:
    explicit DFAAcceptanceState(const unordered_set<NFAState *> &generators, string token_name);

    string get_token_name();

    void set_token_name(string token_name);

private:
    string token_name;
};

class DFADeadState : public DFAState {
public:
    DFADeadState();
};


#endif //LEXGEN_DFASTATE_H
