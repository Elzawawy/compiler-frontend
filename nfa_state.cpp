//
// Created by omar_swidan on 23/03/20.
//

#include "nfa_state.h"
NFAState::NFAState() {
    static int id_counter = 0;
    id=id_counter++;

}

void NFAState::add_neighbour(string input, NFAState *neighbour) {
    this->neighbours.insert(make_pair(input, neighbour));
}



int NFAState::getId() const {
    cout<<id;
    return id;
}

const unordered_map<string, NFAState *> &NFAState::getNeighbours() const {
    return neighbours;
}



void NFAState::set_state_type(NFAState::state_type type) {
this->type=type;
}

NFAState::state_type NFAState::get_state_type() {
    return this->type;
}
