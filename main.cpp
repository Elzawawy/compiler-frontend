#include <iostream>
#include "nfa_state.h"
#include "dfa.h"
#include <queue>
#include <unordered_set>

using namespace std;

#include "nfa.h"
#include "language_parser.h"

int main() {

    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen = DFA();
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
    return 0;
}