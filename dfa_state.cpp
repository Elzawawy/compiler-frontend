
#include "dfa_state.h"
#include <utility>

/****************************** Constructor of the class. ******************************/

DFAState::DFAState(bool accepting_state, unordered_set<NFAState *> generators) : accepting_state_{accepting_state},
                                                                                 generators_{std::move(generators)} {
    static int id_counter = 0;
    this->id_ = id_counter++;
}

DFANormalState::DFANormalState(bool acceptingState, const unordered_set<NFAState *> &generators) :
        DFAState(acceptingState, generators) {}

DFAAcceptanceState::DFAAcceptanceState(bool acceptingState, const unordered_set<NFAState *> &generators, string token) :
        DFAState(acceptingState, generators), token(std::move(token)) {}

/****************************** Getters for member variables of instance. ******************************/

int DFAState::get_id() const {
    return this->id_;
}

bool DFAState::is_accepting_state() const {
    return this->accepting_state_;
}

const unordered_map<string, DFAState *> &DFAState::get_neighbours() const {
    return this->neighbours_;
}

const unordered_set<NFAState *> &DFAState::get_generators() const {
    return this->generators_;
}

/****************************** Public functions of instance. ******************************/

void DFAState::AddNeighbour(string input, DFAState *neighbour) {
    this->neighbours_.insert(make_pair(input, neighbour));
}

string DFAAcceptanceState::get_token() {
    return this->token;
}

void DFAAcceptanceState::set_token(string token) {
    this->token = token;
}
