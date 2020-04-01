//
// Created by omar_swidan on 23/03/20.
//

#include <stack>
#include <memory>
#include "dfa.h"

// implement subset construction
DFAState *DFA::GenerateDFA(NFAState &nfa_root_state, const unordered_set<string> &input_table) {
    auto *dfa_start_state_generators = EpsilonClosureOnNFAState(nfa_root_state);
    auto *dfa_start_state = new DFANormalState(*dfa_start_state_generators);
    unmarked_dfa_states_queue_.push(dfa_start_state);
    unmarked_dfa_states_set_.insert(*dfa_start_state);
    DFAState *current_dfa_state = nullptr, *new_dfa_state = nullptr;
    while (!unmarked_dfa_states_queue_.empty()) {
        current_dfa_state = unmarked_dfa_states_queue_.front();
        marked_dfa_states_.insert(*current_dfa_state);
        for (auto &&input : input_table) {
            auto *nfa_states_generators = Move(*current_dfa_state, input);
            auto *dfa_state_generators = EpsilonClosureOnNFAStates(*nfa_states_generators);
            new_dfa_state = new DFANormalState(*dfa_state_generators);

            bool is_unmarked = false, is_marked = false;

            for(auto&& state : unmarked_dfa_states_set_){
                if(*new_dfa_state == state){
                    *new_dfa_state = state;
                    is_unmarked = true;
                    break;
                }
            }
            for(auto&& state : marked_dfa_states_){
                if(*new_dfa_state == state){
                    *new_dfa_state = state;
                    is_marked = true;
                    break;
                }
            }
            if(!is_marked && !is_unmarked){
                unmarked_dfa_states_queue_.push(new_dfa_state);
                unmarked_dfa_states_set_.insert(*new_dfa_state);
            }

            current_dfa_state->AddNeighbour(input, new_dfa_state);
        }
        unmarked_dfa_states_queue_.pop();
        unmarked_dfa_states_set_.erase(*current_dfa_state);
    }
    return dfa_start_state;
}

unordered_set<NFAState *> *DFA::EpsilonClosureOnNFAStates(const vector<NFAState> &nfa_states) {
    auto *dfa_state_generator = new unordered_set<NFAState *>();
    if (!nfa_states.empty()) {
        for (auto nfa_state: nfa_states) {
            std::unordered_set<NFAState *> *generators = EpsilonClosureOnNFAState(nfa_state);
            dfa_state_generator->merge(*generators);
        }
    }
    return dfa_state_generator;
}

vector<NFAState> *DFA::Move(const DFAState &dfa_state, const string &input) {
    auto *nfa_states_neighbours = new vector<NFAState>;
    for (const auto &generator : dfa_state.get_generators()) {
        vector<pair<string, NFAState *>> generator_neighbours = generator->getNeighbours();
        for (auto &&generator_neighbour: generator_neighbours) {
            if (generator_neighbour.first == input) {
                nfa_states_neighbours->push_back(*generator_neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}

unordered_set<NFAState *> *DFA::EpsilonClosureOnNFAState(NFAState &nfa_state) {
    std::stack<NFAState> nfa_states_stack;
    auto *nfa_states_neighbours = new unordered_set<NFAState *>();
    auto *copy = new NFAState(nfa_state);

    nfa_states_stack.push(nfa_state);
    nfa_states_neighbours->insert(copy);

    while (!nfa_states_stack.empty()) {
        NFAState current_nfa_state = nfa_states_stack.top();
        nfa_states_stack.pop();
        vector<pair<string, NFAState *>> current_nfa_state_neighbours = current_nfa_state.getNeighbours();
        for (auto &&neighbour: current_nfa_state_neighbours) {
            if (neighbour.first == "\\L" and
                nfa_states_neighbours->find(neighbour.second) == nfa_states_neighbours->end()) {
                nfa_states_stack.push(*neighbour.second);
                nfa_states_neighbours->insert(neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}
