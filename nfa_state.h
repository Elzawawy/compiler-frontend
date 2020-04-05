
#ifndef LEXGEN_NFASTATE_H
#define LEXGEN_NFASTATE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "regular_expression.h"
#include "nfa_state.h"

using namespace std;

class NFAState {

public:
    virtual ~NFAState()=default;
    explicit NFAState();
    void add_neighbour(string input, NFAState* neighbour);
    // Getters for member variables of instance.
    int getId() const;
    const vector < pair<string , NFAState *>> &getNeighbours() const;



private:
    int id;
    vector < pair<string , NFAState *> > neighbours;

};
class NFANormalState:public NFAState{

};
class NFAAcceptanceState:public NFAState{
public:
    string get_token();
    void set_priority(int priority);
    int get_priority();
    void set_token(string token);
private:
    int priority;
    string token;
};


#endif //LEXGEN_NFASTATE_H
