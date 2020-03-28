
#include "dfa_state.h"

#include <utility>

int DFAState::id_counter{0};

/****************************** Constructor of the class. ******************************/

DFAState::DFAState() {
    this->id_ = id_counter++;
}

DFAState::DFAState(unordered_set<NFAState *> generators) : generators_{std::move(generators)} {
    this->id_ = id_counter++;
}

DFANormalState::DFANormalState(const unordered_set<NFAState *> &generators) :
        DFAState(generators) {}

DFAAcceptanceState::DFAAcceptanceState(const unordered_set<NFAState *> &generators, string token_name) :
        DFAState(generators), token_name(std::move(token_name)) {}

DFADeadState::DFADeadState() : DFAState() {}

/****************************** Getters for member variables of instance. ******************************/

int DFAState::get_id() const {
    return this->id_;
}

const unordered_map<string, DFAState *> &DFAState::get_neighbours() const {
    return this->neighbours_;
}

const unordered_set<NFAState *> &DFAState::get_generators() const {
    return this->generators_;
}

/****************************** Public functions of instance. ******************************/

void DFAState::AddNeighbour(const string &input, DFAState *neighbour) {
    this->neighbours_.insert(make_pair(input, neighbour));
}

string DFAAcceptanceState::get_token_name() {
    return this->token_name;
}

void DFAAcceptanceState::set_token_name(string token_name) {
    this->token_name = std::move(token_name);
}
