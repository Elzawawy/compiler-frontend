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


    unordered_set<DFAState *>  newDFA = partitioning(nullptr, dfa_gen.getMarked_dfa_states_());

    constructTransitiontable(*(newDFA.begin()), newDFA);

    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/a_test_program1.txt");

   Token *token = (lexicalAnalyzerDriver.GetNextToken());

    REQUIRE(token->GetLexeme() == "int");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "sum");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ",");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "count");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ",");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "pass");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ",");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "mnt");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ";");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "while");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "(");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "pass");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "!=");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "10.2E2000");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ")");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "{");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "pass");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "=");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "pass");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "+");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "1");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == ";");
    delete token;
    token = (lexicalAnalyzerDriver.GetNextToken());
    REQUIRE(token->GetLexeme() == "}");
    delete token;

    delete dfa_start_state;
    delete nfa_start_state;

}