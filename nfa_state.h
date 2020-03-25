
#ifndef LEXGEN_NFASTATE_H
#define LEXGEN_NFASTATE_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class NFAState {

public:
    typedef enum state_type
    {start_state=0, normal_state,acceptance_state}state_type;
    explicit NFAState();
    void add_neighbour(string input, NFAState* neighbour);

    // Getters for member variables of instance.
    void set_state_type(state_type type);
    state_type get_state_type();
    int getId() const;
    const unordered_map<string, NFAState *> &getNeighbours() const;


private:

    state_type type;
    int id;
    unordered_map<string, NFAState *> neighbours;
};


#endif //LEXGEN_NFASTATE_H
