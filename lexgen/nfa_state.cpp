//
// Created by omar_swidan on 23/03/20.
//

#include "nfa_state.h"
NFAState::NFAState() {
    static int id_counter = 0;
    id=id_counter++;

}

void NFAState::add_neighbour(string input, NFAState *neighbour) {
    this->neighbours.push_back(pair<string, NFAState*> (input, neighbour));
}



int NFAState::getId() const {
    return id;
}

const vector<pair<string, NFAState *>> &NFAState::getNeighbours() const {
    return this->neighbours;
}



string NFAAcceptanceState::get_token() {
    return this->token;
}

void NFAAcceptanceState::set_token(string token) {
this->token=token;
}

int NFAAcceptanceState::get_priority() {
    return this->priority;
}

void NFAAcceptanceState::set_priority(int priority) {
this->priority=priority;
}
