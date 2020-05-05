/**
    Compiler Phase 2: PRSGEN
    parsing_table_generator.h
    Purpose: Generates and maintains the logic of creating the parsing table used by the parser. That is composed of three main components: Computing first and follow sets and construction of the table.

    @author(s) Omar Swidan
    @version 1.0
    @date 21/4/2020
*/

#include <unordered_map>
#include <unordered_set>
#include "non_terminal.h"
#ifndef PRSGEN_PARSING_TABLE_GENERATOR_H
#define PRSGEN_PARSING_TABLE_GENERATOR_H

class ParsingTableGenerator {
public:
    ParsingTableGenerator(std::unordered_set<std::string>& terminals_, std::vector<NonTerminal>& non_terminals_);
    void computeFirst();
    void computeFollow();
    void constructParsingTable();
    void writeParseingTable();

private:
    std::unordered_set<std::string>& terminals_;
    std::vector<NonTerminal>& non_terminals_;
    std::unordered_map<std::string, NonTerminal*> name_non_terminal_;
    //maps a non terminal to a vector of non terminals that contain productions containing the key non terminal
    std::unordered_map<std::string, std::unordered_set<std::string>> non_terminal_non_terminal_parents;
    void fill_follow_from_production(std::unordered_set<std::string>& follow,
            const std::vector<std::string>& production, const NonTerminal& current, const NonTerminal& parent);
};

#endif //PRSGEN_PARSING_TABLE_GENERATOR_H
