//
// Created by omar_swidan on 23/03/20.
//

#include "nfa_state.h"

NFAState::NFAState(bool accepting_state) : accepting_state(accepting_state){
    static int id_counter = 0;
    id=id_counter++;

}

void NFAState::add_neighbour(string input, NFAState *neighbour) {
    this->neighbours.insert(make_pair(input, neighbour));
}

bool NFAState::isAccepting_state() const {
    return accepting_state;
}

int NFAState::getId() const {
    return id;
}

const unordered_map<string, NFAState *> &NFAState::getNeighbours() const {
    return neighbours;
}
