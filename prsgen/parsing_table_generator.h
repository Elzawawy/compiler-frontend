/**
    Compiler Phase 2: PRSGEN
    parsing_table_generator.h
    Purpose: Generates and maintains the logic of creating the parsing table used by the parser. That is composed of three main components: Computing first and follow sets and construction of the table.

    @author(s) Omar Swidan
    @version 1.0
    @date 21/4/2020
*/

#include <unordered_map>
#include "non_terminal.h"
#ifndef PRSGEN_PARSING_TABLE_GENERATOR_H
#define PRSGEN_PARSING_TABLE_GENERATOR_H

class ParsingTableGenerator {
private:
    std::unordered_set<std::string>& terminals_;
    std::vector<NonTerminal>& non_terminals_;
    std::unordered_map<std::string, NonTerminal*> name_non_terminal_;
public:
    ParsingTableGenerator(std::unordered_set<std::string>& terminals_, std::vector<NonTerminal>& non_terminals_);
    void computeFirst();
    void computeFollow();
    void constructParsingTable();
    void writeParseingTable();
};

#endif //PRSGEN_PARSING_TABLE_GENERATOR_H
