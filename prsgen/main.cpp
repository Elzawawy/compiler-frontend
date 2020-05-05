/**
    Compiler Phase 2: PRSGEN
    grammar_parser.h
    Purpose: Takes in a file of grammar rules (non-terminals definition) and parses into non-terminals, terminals and production rules.

    @author(s) Amr Elzawawy , Abdelrahman El-Dawy, Abdallah El-Maradny, Omar Swidan, Mostafa Yousry.
    @version 1.0
    @date 24/4/2020
*/

#include "grammar_parser.h"
#include "parsing_table_generator.h"
#include "../lexgen/language_parser.h"
#include "../lexgen/nfa.h"
#include "../lexgen/dfa.h"
#include "../lexgen/lexical_analyzer_driver.h"
#include "predictive_parser.h"
#include <iostream>

using namespace std;

int main() {
    auto language_parser = new LanguageParser();
    language_parser->parseFile(
            "../lexgen/test_cases/a_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen = DFA();
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());

    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "../lexgen/test_cases/a_test_program.txt",
                                                language_parser->getExpressions());

    GrammarParser grammarParser;
    grammarParser.parseFile("../prsgen/test-cases/a_grammar.txt");
    grammarParser.eliminateLeftFactoring();
    grammarParser.eliminateLeftRecursion();
    ParsingTableGenerator parsing_table_generator(grammarParser.getTerminals_(),
                                                  grammarParser.getNon_terminals_());
    parsing_table_generator.computeFirst();
    parsing_table_generator.computeFollow();
    parsing_table_generator.constructParsingTable();
    cout << "========================================================" << endl;
    cout << "--------------------first sets--------------------------" << endl;
    for (auto &&non_terminal: grammarParser.getNon_terminals_()) {
        cout << non_terminal.getName_() << " first set: ";
        for (auto &&element: non_terminal.getFirst_()) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << "--------------------follow sets--------------------------" << endl;
    for (auto &&non_terminal: grammarParser.getNon_terminals_()) {
        cout << non_terminal.getName_() << " follow set: ";
        for (auto &&element: non_terminal.getFollow_()) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << "--------------------Parsing Table------------------------" << endl;
    parsing_table_generator.writeParsingTable("../prsgen/output/parsing_table.csv");

    PredicativeParser predicativeParser = PredicativeParser(lexicalAnalyzerDriver, grammarParser.getNon_terminals_(),
                                                            grammarParser.getTerminals_(),
                                                            "../prsgen/output/parsing_log.txt");
    predicativeParser.Parse();

    return 0;
}