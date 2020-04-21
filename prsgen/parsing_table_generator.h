//
// Created by zawawy on 4/21/20.
//
#include "non_terminal.h"

#ifndef PRSGEN_PARSING_TABLE_GENERATOR_H
#define PRSGEN_PARSING_TABLE_GENERATOR_H

class ParsingTableGenerator {
public:
    void computeFirst(NonTerminal& non_terminal);
    void computeFollow(NonTerminal& non_terminal);
    void constructParsingTable(std::set<std::string>& terminals, std::vector<NonTerminal>& non_terminals);
    void writeParseingTable();
};

#endif //PRSGEN_PARSING_TABLE_GENERATOR_H
