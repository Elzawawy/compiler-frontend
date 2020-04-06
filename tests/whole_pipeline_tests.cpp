#include "catch.h"
#include "../nfa.h"
#include "../language_parser.h"
#include "../dfa.h"
#include "../dfa_state.h"
#include "../min_dfa.h"
#include "../lexical_analyzer_driver.h"
#include "../token.h"
#include <string>
#include <fstream>
#include <streambuf>

#define PUNCTUATION_NAME "Punctuation"
#define KEYWORD_NAME "Keyword"


TEST_CASE("PDF's inputs") {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());


    unordered_set<DFAState *> newDFA = partitioning(nullptr, dfa_gen.getMarked_dfa_states_());


    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/a_test_program.txt");

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

TEST_CASE("Test B") {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/case_1/b_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
    constructTransitiontable(dfa_start_state,dfa_gen.getMarked_dfa_states_(),"../test_cases/case_1/transition_table.csv");

    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/case_1/b_test_program.txt");
    string output;
    vector<Token *> tokens;
    int i = 0;
    ofstream out_file("../test_cases/case_1/output_tokens.txt", ios::out);
    while (!lexicalAnalyzerDriver.IsInputOver()) {
        Token *token = (lexicalAnalyzerDriver.GetNextToken());
        if (token == nullptr) break;
        tokens.push_back(token);
        if (token->GetTokenName() == KEYWORD_NAME || token->GetTokenName() == PUNCTUATION_NAME) {
            output += token->GetLexeme();
        } else {
            output += token->GetTokenName();
        }
        output += '\n';
        i++;
    }
    output.erase(output.end() - 1);
    std::ifstream t("../test_cases/case_1/b_output_program.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    REQUIRE(output == str);
    t.close();


    for (auto &&item  : tokens) {
        delete item;
    }
};

TEST_CASE("Test C") {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/case_2/c_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
    constructTransitiontable(dfa_start_state,dfa_gen.getMarked_dfa_states_(),"../test_cases/case_2/transition_table.csv");


    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/case_2/c_test_program.txt");
    string output;
    vector<Token *> tokens;
    int i = 0;
    ofstream out_file("../test_cases/case_2/output_tokens.txt", ios::out);
    while (!lexicalAnalyzerDriver.IsInputOver()) {
        Token *token = (lexicalAnalyzerDriver.GetNextToken());
        if (token == nullptr) break;
        tokens.push_back(token);
        if (token->GetTokenName() == KEYWORD_NAME || token->GetTokenName() == PUNCTUATION_NAME) {
            output += token->GetLexeme();
        } else {
            output += token->GetTokenName();
        }
        output += '\n';
        i++;
    }
    output.erase(output.end() - 1);
    out_file<<output;
    std::ifstream t("../test_cases/case_2/c_output_program.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    REQUIRE(output == str);
    t.close();


    for (auto &&item  : tokens) {
        delete item;
    }
};

TEST_CASE("Test D") {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/case_3/d_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen;
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
    constructTransitiontable(dfa_start_state,dfa_gen.getMarked_dfa_states_(),"../test_cases/case_3/transition_table.csv");


    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../test_cases/case_3/d_test_program.txt");
    string output;
    vector<Token *> tokens;
    int i = 0;
    ofstream out_file("../test_cases/case_3/output_tokens.txt", ios::out);
    while (!lexicalAnalyzerDriver.IsInputOver()) {
        Token *token = (lexicalAnalyzerDriver.GetNextToken());
        if (token == nullptr) break;
        tokens.push_back(token);
        if (token->GetTokenName() == KEYWORD_NAME || token->GetTokenName() == PUNCTUATION_NAME) {
            output += token->GetLexeme();
        } else {
            output += token->GetTokenName();
        }
        output += '\n';
        i++;
    }
    output.erase(output.end() - 1);
    std::ifstream t("../test_cases/case_3/d_output_program.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    REQUIRE(output == str);
    t.close();


    for (auto &&item  : tokens) {
        delete item;
    }
};