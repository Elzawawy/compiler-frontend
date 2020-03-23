
#ifndef LEXGEN_NFASTATE_H
#define LEXGEN_NFASTATE_H

#include <vector>
#include <unordered_map>

using namespace std;

class NFAState {
public:
    explicit NFAState(bool accepting_state);
    void add_neighbour(string input, NFAState* neighbour);

    // Getters for member variables of instance.
    int getId() const;
    const unordered_map<string, NFAState *> &getNeighbours() const;
    bool isAccepting_state() const;

private:
    int id;
    bool accepting_state;
    unordered_map<string, NFAState *> neighbours;
};


#endif //LEXGEN_NFASTATE_H
