//
// Created by zawawy on 4/25/20.
//

#include "grammar_parser.h"
#include "parsing_table_generator.h"
#include <iostream>

using namespace std;

int main() {
    GrammarParser grammarParser;
    grammarParser.parseFile("../prsgen/test-cases/a_grammar.txt");
//    grammarParser.eliminateLeftFactoring();
//    grammarParser.eliminateLeftRecursion();
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
    parsing_table_generator.writeParsingTable();
}