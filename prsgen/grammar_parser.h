//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <unordered_set>
#include "non_terminal.h"
#define EPSILON_EXPRESSION "\\L"
class GrammarParser {

private:
    std::unordered_set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
    std::unordered_set<std::string> non_terminals_names_;
    void extractNonTerminalNamesFromFile(std::string grammar_file_path);
    void extractTerminalsFromRHS(std::string& right_hand_side);
    void extractProductionRulesFromRHS(std::string& right_hand_side, NonTerminal& non_terminal);
    std::vector<std::string> vectorizeProductionRuleString(std::string& production_rule);
public:
    const std::unordered_set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
    void parseFile(std::string grammar_file_path);
    void eliminateLeftFactoring();
    void eliminateRightFactoring();
};

#endif //PRSGEN_GRAMMAR_PARSER_H
