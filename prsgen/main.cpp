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
    cout<<"========================================================"<<endl;
    cout<<"--------------------first sets--------------------------"<<endl;
    for (auto &&non_terminal: grammarParser.getNon_terminals_()) {
        cout<<non_terminal.getName_()<<" first set: ";
        for(auto &&element: non_terminal.getFirst_()) {
            cout<<element<<" ";
        }
        cout<<endl;
    }
    cout<<"--------------------follow sets--------------------------"<<endl;
    for (auto &&non_terminal: grammarParser.getNon_terminals_()) {
        cout<<non_terminal.getName_()<<" follow set: ";
        for(auto &&element: non_terminal.getFollow_()) {
            cout<<element<<" ";
        }
        cout<<endl;
    }

}