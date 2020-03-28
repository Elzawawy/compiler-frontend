
#ifndef LEXGEN_NFASTATE_H
#define LEXGEN_NFASTATE_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class NFAState {

public:

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
    void set_token();
private:
    string token;
};


#endif //LEXGEN_NFASTATE_H
