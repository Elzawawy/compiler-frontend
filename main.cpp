#include <iostream>
#include "nfa_state.h"
#include "dfa.h"
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    NFAState zero = NFANormalState();
    NFAState one = NFANormalState();
    NFAState two = NFANormalState();
    NFAState three = NFANormalState();
    NFAState four = NFANormalState();
    NFAState five = NFANormalState();
    NFAState six = NFANormalState();
    NFAState seven = NFANormalState();
    NFAState eight = NFANormalState();
    NFAState nine = NFANormalState();
    NFAAcceptanceState ten{ NFAAcceptanceState()};

    ten.set_token("(a|b)*abb");

    zero.add_neighbour("\\L", &one);
    zero.add_neighbour("\\L", &seven);

    one.add_neighbour("\\L", &two);
    one.add_neighbour("\\L", &four);

    two.add_neighbour("a", &three);

    three.add_neighbour("\\L", &six);

    four.add_neighbour("b", &five);

    five.add_neighbour("\\L", &six);

    six.add_neighbour("\\L", &one);
    six.add_neighbour("\\L", &seven);

    seven.add_neighbour("a", &eight);

    eight.add_neighbour("b", &nine);

    nine.add_neighbour("b", &ten);

    unordered_set<string> input_table{"a", "b"};
    DFA dfa_gen = DFA();
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(zero, input_table);

    queue<DFAState> q;
    unordered_set<long> s;
    q.push(*dfa_start_state);
    while (!q.empty()) {
        DFAState d = q.front();
        q.pop();

        s.insert(d.get_id());
        for (auto g : d.get_generators()) {
            cout << g->getId() << " ";
        }
        cout << endl;
        if(dynamic_cast<DFAAcceptanceState *>(&d)){
            cout << "accepting: true"<< endl;
        }
        else{
            cout << "accepting: false"<< endl;
        }
        unordered_map<string, DFAState *> ns = d.get_neighbours();
        for (auto n : ns) {
            DFAState temp = *n.second;
            cout << "under " << n.first << " go to dfa state with id " << temp.get_id() << endl;
            if (s.find(n.second->get_id()) == s.end()) {
                s.insert(temp.get_id());
                q.push(temp);
            }
        }
        cout << "=================================================================================" << endl;
    }
    return 0;
}