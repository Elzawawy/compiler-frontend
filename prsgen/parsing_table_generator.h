//
// Created by zawawy on 4/21/20.
//
#include "non_terminal.h"

#ifndef PRSGEN_PARSING_TABLE_GENERATOR_H
#define PRSGEN_PARSING_TABLE_GENERATOR_H

class ParsingTableGenerator {
private:
    std::set<std::string>& terminals_;
    std::vector<NonTerminal>& non_terminals_;
public:
    ParsingTableGenerator(std::set<std::string>& terminals_, std::vector<NonTerminal>& non_terminals_);
    void computeFirst();
    void computeFollow();
    void constructParsingTable();
    void writeParseingTable();
};

#endif //PRSGEN_PARSING_TABLE_GENERATOR_H
