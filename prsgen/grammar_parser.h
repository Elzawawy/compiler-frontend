//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <unordered_set>
#include "non_terminal.h"
class GrammarParser {

private:
    std::unordered_set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
public:
    const std::unordered_set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
    void parseFile(std::string grammar_file_path);
    void eliminateLeftFactoring();
    void eliminateRightFactoring();
};

#endif //PRSGEN_GRAMMAR_PARSER_H
