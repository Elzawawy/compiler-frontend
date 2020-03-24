
#include "dfa_state.h"

/****************************** Constructor of the class. ******************************/

DFAState::DFAState(bool accepting_state): accepting_state_(accepting_state) {

}

/****************************** Getters for member variables of instance. ******************************/

int DFAState::get_id() const {
    return this->id_;
}

bool DFAState::is_accepting_state() const {
    return false;
}

const unordered_map<string, DFAState *> &DFAState::get_neighbours() const {
    return this->neighbours_;
}

const vector<NFAState *> &DFAState::get_generators() const {
    return generators_;
}

/****************************** Public functions of instance. ******************************/

void DFAState::AddNeighbour(string input, DFAState *neighbour) {
    this->neighbours_.insert(make_pair(input, neighbour));
}