
#ifndef LEXGEN_DFASTATE_H
#define LEXGEN_DFASTATE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "nfa_state.h"

class DFAState {
private:
    static int id_counter;
    int id_;
    std::unordered_map<string, DFAState *> neighbours_;
    std::unordered_set<NFAState *> generators_;
    string combiningSymbol;
    DFAState* equivState;

public:
    // Constructor of the class.
    DFAState();

    explicit DFAState(unordered_set<NFAState *> generators);

    // Getters for member variables of instance.
    int get_id() const;

    const unordered_map<string, DFAState *> &get_neighbours() const;

    // Public functions of instance.
    void AddNeighbour(const string &input, DFAState *neighbour);


    DFAState* GetNeighbour(const string& input);

    bool operator==(const DFAState &other) const;


    virtual bool IsAcceptingState() {
        return false;
    };

    const unordered_set<NFAState *> &get_generators() const;
    string getCombiningsymbol();
    void setCombiningsymbol(string& Symbol);
    DFAState* getEquivstate();
    void setEquivstate(DFAState* state);
    void UpdateNeighbours(string symbol, DFAState * state);

    virtual bool IsDeadState();
};

class DFANormalState : public DFAState {
public:
    explicit DFANormalState(const unordered_set<NFAState *> &generators);


    DFANormalState();

    bool IsAcceptingState() override {
        return false;
    }
};

class DFAAcceptanceState : public DFAState {
private:
    string token_name;
public:
    explicit DFAAcceptanceState(const unordered_set<NFAState *> &generators, string token_name);

    DFAAcceptanceState();

    string get_token_name();

    void set_token_name(string token_name);

    bool IsAcceptingState() override {
        return true;
    }
};

class DFADeadState : public DFAState {
public:
    DFADeadState();

    bool IsAcceptingState() override {
        return false;
    }

    bool IsDeadState() override;
};


#endif //LEXGEN_DFASTATE_H
