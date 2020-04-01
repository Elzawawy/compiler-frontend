#include <iostream>
#include "nfa_state.h"
#include "dfa.h"
#include <queue>
#include <unordered_set>

using namespace std;

#include "nfa.h"
#include "language_parser.h"

int main()
{

    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x=NFA();
    x.regex_to_nfa(language_parser->getInput_table(),language_parser->getExpressions());
//    DFA dfa_gen = DFA();
//    DFAState *dfa_start_state = dfa_gen.GenerateDFA(zero, input_table);
//
//    queue<DFAState> q;
//    unordered_set<long> s;
//    q.push(*dfa_start_state);
//    while (!q.empty()) {
//        DFAState d = q.front();
//        q.pop();
//
//        s.insert(d.get_id());
//        for (auto g : d.get_generators()) {
//            cout << g->getId() << " ";
//        }
//        cout << endl;
//        if(dynamic_cast<DFAAcceptanceState *>(&d)){
//            cout << "accepting: true"<< endl;
//        }
//        else{
//            cout << "accepting: false"<< endl;
//        }
//        unordered_map<string, DFAState *> ns = d.get_neighbours();
//        for (auto n : ns) {
//            DFAState temp = *n.second;
//            cout << "under " << n.first << " go to dfa state with id " << temp.get_id() << endl;
//            if (s.find(n.second->get_id()) == s.end()) {
//                s.insert(temp.get_id());
//                q.push(temp);
//            }
//        }
//        cout << "=================================================================================" << endl;
//    }
    return 0;
}