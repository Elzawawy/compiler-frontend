/**
    Compiler Phase 2: PRSGEN
    grammar_parser.h
    Purpose: Takes in a file of grammar rules (non-terminals definition) and parses into non-terminals, terminals and production rules.

    @author(s) Amr Elzawawy
    @version 1.0
    @date 24/4/2020
*/
#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <unordered_set>
#include "non_terminal.h"
#define EPSILON_EXPRESSION "\\L"
typedef std::vector<std::string> ProductionRule;

class GrammarParser {
public:
    const std::unordered_set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
    void parseFile(std::string grammar_file_path);
    void eliminateLeftFactoring();
    void eliminateRightFactoring();

private:
    std::unordered_set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
    std::unordered_set<std::string> non_terminals_names_;
    void validateGrammarFile(std::string grammar_file_path);
    void extractTerminalsFromRHS(std::string& right_hand_side);
    void extractProductionRulesFromRHS(std::string& right_hand_side, NonTerminal& non_terminal);
    ProductionRule getProductionRuleFromString(std::string& production_rule);
};

#endif //PRSGEN_GRAMMAR_PARSER_H
