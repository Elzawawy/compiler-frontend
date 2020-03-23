
#include "dfa_state.h"

bool DFAState::isAccepting_state() const {
    return false;
}

const unordered_map<string, DFAState *> &DFAState::getNeighbours() const {
    return this->neighbours;
}

int DFAState::getId() const {
    return 0;
}

void DFAState::add_neighbour(string input, DFAState *neighbour) {
    this->neighbours.insert(make_pair(input, neighbour));
}

DFAState::DFAState(bool accepting_state): accepting_state(accepting_state) {

}

const vector<NFAState *> &DFAState::getGenerators() const {
    return generators;
}
