
#include "dfa_state.h"

#include <utility>

int DFAState::id_counter{0};

/****************************** Constructor of the class. ******************************/

DFAState::DFAState() : id_(id_counter++) {}

DFAState::DFAState(unordered_set<NFAState *> generators) : id_(id_counter++), generators_(std::move(generators)) {}

DFANormalState::DFANormalState(const unordered_set<NFAState *> &generators) :
        DFAState(generators) {}

DFANormalState::DFANormalState() {}

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

string DFAAcceptanceState::get_token_name() {
    return this->token_name;
}

void DFAAcceptanceState::set_token_name(string token_name) {
    this->token_name = std::move(token_name);
}

DFAAcceptanceState::DFAAcceptanceState() {}

/****************************** Public functions of instance. ******************************/

void DFAState::AddNeighbour(const string &input, DFAState *neighbour) {
    this->neighbours_.insert({input, neighbour});
}

bool DFAState::operator==(const DFAState &other) const {
    if(this->generators_.size() != other.generators_.size()){
        return false;
    }
    for (auto generator : this->generators_) {
        bool is_equal = false;
        for(auto other_generator: other.generators_ ){
            if(generator->getId() == other_generator->getId()){
                is_equal= true;
            }
        }
        if(!is_equal){
            return false;
        }
    }
    return true;
}
DFAState* DFAState::GetNeighbour(const string &input) {
  return this->neighbours_[input];
}

bool DFAState::IsDeadState() {
  return false;
}

bool DFADeadState::IsDeadState() {
    return true;
}
