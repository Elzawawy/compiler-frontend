
#include "dfa_state.h"

bool DFAState::isAccepting_state() const {
    return accepting_state;
}

const unordered_map<string, DFAState *> &DFAState::getNeighbours() const {
    return this->neighbours;
}

int DFAState::getId() const {
    return id;
}

void DFAState::add_neighbour(string input, DFAState *neighbour) {
    this->neighbours.insert(make_pair(input, neighbour));
	
}

DFAState::DFAState(bool accepting_state): accepting_state(accepting_state) {
	
	static int id_counter = 0;
	id = id_counter++;
	
}

void DFAState::updateNeighbours(string symbol, DFAState * state)
{

	neighbours[symbol] = state;
}

const vector<NFAState *> &DFAState::getGenerators() const {
    return generators;
}

string DFAState::getCombiningsymbol()
{
	return combiningSymbol;
}

void DFAState::setCombiningsymbol(string Symbol)
{
	this->combiningSymbol = Symbol;
}

DFAState * DFAState::getEquivstate()
{
	return equivState;
}

void DFAState::setEquivstate(DFAState * state)
{
	equivState = state;
}
