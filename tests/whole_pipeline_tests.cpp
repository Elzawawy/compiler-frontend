#include "catch.h"
#include "../nfa.h"
#include "../language_parser.h"
#include "../dfa.h"
#include "../dfa_state.h"
#include "../min_dfa.h"
#include "../lexical_analyzer_driver.h"
#include "../token.h"

TEST_CASE("PDF's inputs") {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());


//    constructTransitiontable(dfa_start_state, dfa_gen.getMarked_dfa_states_()), dfa_gen.getMarked_dfa_states_();
//    unordered_set<DFAState *>  newDFA = partitioning(constructTransitiontable(dfa_start_state, dfa_gen.getMarked_dfa_states_()), dfa_gen.getMarked_dfa_states_());
//
//    constructTransitiontable(*(newDFA.begin()), newDFA);

//    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/a_test_program1.txt");
//
//   Token *token = (lexicalAnalyzerDriver.GetNextToken());
//
//    REQUIRE(token->GetLexeme_() == "int");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "sum");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == ",");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "count");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == ",");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "pass");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == ",");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "mnt");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == ";");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "while");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "(");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "pass");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "!=");
//    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == "10");
////    delete token;
//    token = (lexicalAnalyzerDriver.GetNextToken());
//    REQUIRE(token->GetLexeme_() == ")");
//    delete token;
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "{");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "pass");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "=");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "pass");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "+");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "1");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == ";");
//    REQUIRE((lexicalAnalyzerDriver.GetNextToken())->GetLexeme_() == "}");
    delete dfa_start_state;
    delete nfa_start_state;

}