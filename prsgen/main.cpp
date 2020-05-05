/**
    Compiler Phase 2: PRSGEN
    grammar_parser.h
    Purpose: Takes in a file of grammar rules (non-terminals definition) and parses into non-terminals, terminals and production rules.

    @author(s) Amr Elzawawy , Abdelrahman El-Dawy, Abdallah El-Maradny, Omar Swidan, Mostafa Yousry.
    @version 1.0
    @date 24/4/2020
*/

#include "grammar_parser.h"
int main(){
    GrammarParser grammarParser;
    grammarParser.parseFile("../prsgen/test-cases/a_grammar.txt");
    grammarParser.eliminateLeftFactoring();
    grammarParser.eliminateLeftRecursion();
}