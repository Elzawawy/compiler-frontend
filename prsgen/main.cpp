//
// Created by zawawy on 4/25/20.
//

#include "grammar_parser.h"
int main(){
    GrammarParser grammarParser;
    grammarParser.parseFile("../prsgen/test-cases/a_grammar.txt");
    grammarParser.eliminateLeftFactoring();
}