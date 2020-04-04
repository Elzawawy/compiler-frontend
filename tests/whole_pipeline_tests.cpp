#include "catch.h"
#include "../nfa.h"
#include "../language_parser.h"
#include "../dfa.h"
#include "../dfa_state.h"
#include "../min_dfa.h"
#include "../lexical_analyzer_driver.h"
#include "../token.h"

TEST_CASE("PDF's inputs"){
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, language_parser->getInput_table());


    constructTransitiontable(dfa_start_state, dfa_gen.getMarked_dfa_states_()), dfa_gen.getMarked_dfa_states_();
//    unordered_set<DFAState *>  newDFA = partitioning(constructTransitiontable(dfa_start_state, dfa_gen.getMarked_dfa_states_()), dfa_gen.getMarked_dfa_states_());
//    constructTransitiontable(*(newDFA.begin()), newDFA);


}