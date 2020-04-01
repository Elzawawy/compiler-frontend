//
// Created by omar_swidan on 23/03/20.
//

#include "nfa_state.h"

#include <utility>
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

//NFAState *NFAState::get_acceptance_state(NFAState *start_state) {
//
//            // Create a map iterator and point to beginning of map
//            __detail::_Node_const_iterator<pair<const basic_string<char, char_traits<char>, allocator<char>>, NFAState *>, 0, 1> it = start_state->getNeighbours().begin();
//            // Iterate over the map using c++11 range based for loop
//            for (std::pair<std::string, NFAState*> element : start_state->getNeighbours()) {
//                // Accessing KEY from element
//                std::string word = element.first;
//                cout<<word;
//                // Accessing VALUE from element.
//cout<<"fassa";
//
//                cout << (element.second)->getId();
//            }
//
//
//
//
//    return nullptr;
//}

const vector<pair<string, NFAState *>> &NFAState::getNeighbours() const {
    return this->neighbours;
}

string NFAAcceptanceState::get_token() {
    return token;
}

void NFAAcceptanceState::set_token(string token) {
    this->token = std::move(token);
}
