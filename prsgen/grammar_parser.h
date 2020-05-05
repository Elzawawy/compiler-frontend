/**
    Compiler Phase 2: PRSGEN
    grammar_parser.h
    Purpose: Takes in a file of grammar rules (non-terminals definition) and parses into non-terminals, terminals and production rules.

    @author(s) Amr Elzawawy , Abdelrahman El-Dawy, Abdallah El-Maradny
    @version 1.0
    @date 21/4/2020
*/
#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <unordered_set>
#include "non_terminal.h"
#include <unordered_map>
#include <iostream>
#define EPSILON_EXPRESSION "\\L"
typedef std::vector<std::string> ProductionRule;

class GrammarParser {
public:
	std::unordered_set<std::string>& getTerminals_();
	std::vector<NonTerminal>& getNon_terminals_();
    void parseFile(std::string grammar_file_path);
    void eliminateLeftRecursion();
    void applyLeftFactoring();

private:
    std::unordered_set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
    std::unordered_set<std::string> non_terminals_names_;
    std::vector<NonTerminal> after_left_recursion_;
    /** Parse Grammar File Needed Helper Methods **/
    void validateGrammarFile(std::string grammar_file_path);
    void extractTerminalsFromRHS(std::string& right_hand_side);
    void extractProductionRulesFromRHS(std::string& right_hand_side, NonTerminal& non_terminal);
    ProductionRule getProductionRuleFromString(std::string& production_rule);
    /** Eliminate Left Recursion Needed Helper Methods **/
    std::vector<NonTerminal*> eliminateImmediateLeftRecursion(NonTerminal* non_terminal);
    bool checkImmediateLeftRecursion(NonTerminal* non_terminal);
    NonTerminal* substitution(NonTerminal* current_non_terminal, NonTerminal* input);
};

#endif //PRSGEN_GRAMMAR_PARSER_H