//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <set>
#include "non_terminal.h"
class GrammarParser {

private:
    std::set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
public:
    const std::set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
};

#endif //PRSGEN_GRAMMAR_PARSER_H
