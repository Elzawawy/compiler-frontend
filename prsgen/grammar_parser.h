//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <set>
#include "non_terminal.h"
#include <unordered_map>
#include <iostream>

class GrammarParser {

private:
    std::set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
public:
    const std::set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
    void parseFile(std::string file_name);
    void eliminateLeftFactoring();
    void eliminateRightFactoring();
};

#endif //PRSGEN_GRAMMAR_PARSER_H