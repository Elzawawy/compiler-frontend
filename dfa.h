#ifndef LEXGEN_DFA_H
#define LEXGEN_DFA_H

#include "utils.cpp"
#include <unordered_set>
#include <queue>
#include <string>

class DFA {
private:
    std::unordered_set<DFAState *> marked_dfa_states_;
    std::queue<DFAState *> unmarked_dfa_states_queue_;
    std::unordered_set<DFAState *> unmarked_dfa_states_set_;

    /**
     * Used to get the set of NFA states reachable from some other NFA states on epsilon-transitions alone.
     * @param nfa_states A reference to a vector that contains the NFAStates.
     * @return An unordered set pointer of the NFA states on epsilon transitions.
     */
    std::unordered_set<NFAState*>* EpsilonClosureOnNFAStates(const std::vector<NFAState>& nfa_states);

    /**
     * Used to get the set of NFA states to which there is a transition on input symbol (a) from some NFA state (s) in the DFA state (T) .
     * @param dfa_state The DFAState which contains the NFA states that are the start states of the transitions.
     * @param input The input symbol of the transition.
     * @return A vector pointer of NFAState which are the destination of the transitions based on the input symbol
     */

    std::vector<NFAState>* Move(const DFAState& dfa_state, const std::string& input);

    /**
     * Used to get the set of NFA states reachable from a NFA state on epsilon-transitions alone.
     * @param nfa_state A reference to a single NFAState.
     * @return An unordered set pointer of the NFA states on epsilon transitions.
     */
    std::unordered_set<NFAState*>* EpsilonClosureOnNFAState(NFAState& nfa_state);

    std::string GetTokenNameIfAcceptanceExist(const std::unordered_set<NFAState*>& generators_);

public:

    /**
     * Used to convert the Non-Deterministic Finite Automate (NFA) to Deterministic Finite Automate (DFA).
     * The implementation of this function is based on subset construction algorithm.
     * @param nfa_root_state A reference to the first state in NFA.
     * @param input_table The input table of the language.
     * @return A DFAState pointer that point to the first state in DFA.
     */
    DFAState* GenerateDFA(NFAState& nfa_root_state, const std::unordered_set<std::string>& input_table);

    const unordered_set<DFAState *> &getMarked_dfa_states_() const;
};

#endif //LEXGEN_DFA_H
