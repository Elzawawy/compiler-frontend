#include <stack>
#include <memory>
#include <climits>
#include "dfa.h"

#define EPSILON "\\L"


DFAState *DFA::GenerateDFA(NFAState &nfa_root_state, const unordered_set<string> &input_table) {
    DFAState *current_dfa_state = nullptr, *new_dfa_state = nullptr;
    DFAState *dead_dfa_state = new DFADeadState();

    // Create the start state of DFA
    auto *dfa_start_state_generators = EpsilonClosureOnNFAState(nfa_root_state);
    auto *dfa_start_state = new DFANormalState(*dfa_start_state_generators);

    unmarked_dfa_states_queue_.push(dfa_start_state);
    unmarked_dfa_states_set_.insert(dfa_start_state);

    while (!unmarked_dfa_states_queue_.empty()) {
        current_dfa_state = unmarked_dfa_states_queue_.front();
        marked_dfa_states_.insert(current_dfa_state);
        for (auto &&input : input_table) {
            // Create the generators (set of NFA states) of the new DFA state
            auto *nfa_states_base_generators = Move(*current_dfa_state, input);
            auto *dfa_state_generators = EpsilonClosureOnNFAStates(*nfa_states_base_generators);

            if (dfa_state_generators->empty()) {
                new_dfa_state = dead_dfa_state;
            } else {
                // Check if the generators contains an acceptance state to make the new dfa state of type acceptance state ot normal state
                string token_name = GetTokenNameIfAcceptanceExist(*dfa_state_generators);
                if (token_name.empty()) {
                    new_dfa_state = new DFANormalState(*dfa_state_generators);
                } else {
                    new_dfa_state = new DFAAcceptanceState(*dfa_state_generators, token_name);
                }
            }

            bool is_unmarked = false, is_marked = false;

            // Check if the new dfa state is in the unmarked set to not add it.
            for (auto &&state : unmarked_dfa_states_set_) {
                if (*new_dfa_state == *state) {
                    new_dfa_state = state;
                    is_unmarked = true;
                    break;
                }
            }
            // Check if the new dfa state is in the marked set to not add it.
            for (auto &&state : marked_dfa_states_) {
                if (*new_dfa_state == *state) {
                    new_dfa_state = state;
                    is_marked = true;
                    break;
                }
            }
            if (!is_marked && !is_unmarked) {
                unmarked_dfa_states_queue_.push(new_dfa_state);
                unmarked_dfa_states_set_.insert(new_dfa_state);
            }

            current_dfa_state->AddNeighbour(input, new_dfa_state);
        }
        unmarked_dfa_states_queue_.pop();
        unmarked_dfa_states_set_.erase(current_dfa_state);
    }
    return dfa_start_state;
}
std::unordered_set<NFAState *> *DFA::EpsilonClosureOnNFAStates(const std::vector<NFAState> &nfa_states) {
    auto *dfa_state_generators = new std::unordered_set<NFAState *>();
    std::unordered_set<NFAState *> *generators = nullptr;
    if (!nfa_states.empty()) {
        // Get the neighbours of each nfa state generator (base) on epsilon transition
        for (auto nfa_state: nfa_states) {
            generators = EpsilonClosureOnNFAState(nfa_state);
            dfa_state_generators->merge(*generators);
        }
    }
    return dfa_state_generators;
}

std::vector<NFAState> *DFA::Move(const DFAState &dfa_state, const string &input) {
    auto *nfa_states_neighbours = new vector<NFAState>;

    // Search in the generators if there are neighbours based on the given input transition
    for (auto &&generator : dfa_state.get_generators()) {
        std::vector<std::pair<string, NFAState *>> generator_neighbours = generator->getNeighbours();
        for (auto &&generator_neighbour: generator_neighbours) {
            if (generator_neighbour.first == input) {
                nfa_states_neighbours->push_back(*generator_neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}

std::unordered_set<NFAState *> *DFA::EpsilonClosureOnNFAState(NFAState &nfa_state) {
    std::stack<NFAState> nfa_states_stack;
    auto *nfa_states_neighbours = new std::unordered_set<NFAState *>();
    auto *copy = new NFAState(nfa_state);

    nfa_states_stack.push(nfa_state);
    nfa_states_neighbours->insert(copy);

    while (!nfa_states_stack.empty()) {
        NFAState current_nfa_state = nfa_states_stack.top();
        nfa_states_stack.pop();
        std::vector<std::pair<string, NFAState *>> current_nfa_state_neighbours = current_nfa_state.getNeighbours();

        // Search in the generators if there are neighbours based on epsilon transition
        for (auto &&neighbour: current_nfa_state_neighbours) {
            if (neighbour.first == EPSILON and
                nfa_states_neighbours->find(neighbour.second) == nfa_states_neighbours->end()) {
                // Add the neighbour to the stack so it maybe has a neighbour on epsilon transition
                nfa_states_stack.push(*neighbour.second);
                nfa_states_neighbours->insert(neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}

string DFA::GetTokenNameIfAcceptanceExist(const std::unordered_set<NFAState *> &generators_) {
//    int priority = INT_MAX;
    std::string token_name = "";
    for (auto generator : generators_) {
        if (dynamic_cast<NFAAcceptanceState *> (generator)) {
//            if (((NFAAcceptanceState *) generator)->get_priority() < priority) {
//                priority = ((NFAAcceptanceState *) generator)->get_priority();
                token_name = ((NFAAcceptanceState *) generator)->get_token();
                break;
//            }
        }
    }

    return token_name;
}

const unordered_set<DFAState *> &DFA::getMarked_dfa_states_() const {
    return marked_dfa_states_;
}
