//
// Created by zawawy on 4/21/20.
//

#include <fstream>
#include <iostream>
#include "grammar_parser.h"
#include "../utils.h"
#define NON_TERMINAL_SEPARATOR '#'
#define NON_TERMINAL_SIDES_SEPARATOR "::="
#define LEFT_HAND_SIDE_INDEX 0
#define RIGHT_HAND_SIDE_INDEX 1
#define PRODUCTION_RULES_SEPARATOR '|'
#define PRODUCTION_RULE_TERMS_SEPARATOR ' '
#define TERMINAL_INDICATOR '\''
#define ESCAPE_CHARACTER '\\'
#define ONE_SPACE_STRING " "
#define isInvalidNonTerminal(term) !non_terminals_names_.count(term) and !terminals_.count(term) and term!=EPSILON_EXPRESSION
#define isEscapedTerminal(term) term[0]==ESCAPE_CHARACTER and term!=EPSILON_EXPRESSION

const std::unordered_set<std::string>& GrammarParser::getTerminals_() const
{
    return terminals_;
}
const std::vector<NonTerminal>& GrammarParser::getNon_terminals_() const
{
    return non_terminals_;
}

void GrammarParser::parseFile(std::string grammar_file_path)
{
    // extract all non terminal names (L.H.S of all rules) at the beginning.
    extractNonTerminalNamesFromFile(grammar_file_path);
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            // guard against any empty lines detected.
            if (non_terminal_definition.empty()) continue;
            // split sides of the non-terminal definition.
            std::vector<std::string> definition_sides = util::splitOnStringDelimiter(non_terminal_definition,
                    NON_TERMINAL_SIDES_SEPARATOR);
            std::string right_hand_side = definition_sides[RIGHT_HAND_SIDE_INDEX];
            std::string left_hand_side = definition_sides[LEFT_HAND_SIDE_INDEX];
            util::trimBothEnds(left_hand_side);
            NonTerminal non_terminal(left_hand_side);
            extractTerminalsFromRHS(right_hand_side);
            extractProductionRulesFromRHS(right_hand_side, non_terminal);
            non_terminals_.push_back(non_terminal);
        }
        file.close();
    }
    for (auto& terminal: terminals_)
        std::cout << terminal << std::endl;
    for (auto& non_terminal: non_terminals_) {
        std::cout << "---------" << non_terminal.getName_() << "----------" << std::endl;
        for (auto& rule: non_terminal.getProduction_rules_()) {
            std::cout << "==========RULE =========" << std::endl;
            for (auto& term: rule)
                std::cout << term << std::endl;
        }
    }
}

void GrammarParser::eliminateRightFactoring()
{
    //TODO: PRSGEN-3
}
void GrammarParser::eliminateLeftFactoring()
{
    //TODO: PRSGEN-4
}

void GrammarParser::extractNonTerminalNamesFromFile(std::string grammar_file_path)
{
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            // guard against any empty lines detected.
            if (non_terminal_definition.empty()) continue;
            // split sides of the non-terminal definition.
            std::vector<std::string> definition_sides = util::splitOnStringDelimiter(non_terminal_definition,
                    NON_TERMINAL_SIDES_SEPARATOR);
            util::trimBothEnds(definition_sides[LEFT_HAND_SIDE_INDEX]);
            non_terminals_names_.insert(definition_sides[LEFT_HAND_SIDE_INDEX]);
        }
        file.close();
    }
}

void GrammarParser::extractTerminalsFromRHS(std::string& right_hand_side)
{
    util::trimBothEnds(right_hand_side);
    for (unsigned long i = 0; i<right_hand_side.size(); i++) {
        std::string found_terminal;
        if (right_hand_side[i]==TERMINAL_INDICATOR) {
            right_hand_side.replace(i, 1, ONE_SPACE_STRING);
            while (i<right_hand_side.size()
                    and (right_hand_side[++i]!=TERMINAL_INDICATOR or right_hand_side[i-1]==ESCAPE_CHARACTER)) {
                if (right_hand_side[i]==ESCAPE_CHARACTER) continue;
                found_terminal += right_hand_side[i];
            }
            right_hand_side.replace(i, 1, ONE_SPACE_STRING);
            terminals_.insert(found_terminal);
        }
    }
}

void GrammarParser::extractProductionRulesFromRHS(std::string& right_hand_side,
        NonTerminal& non_terminal)
{
    util::trimBothEnds(right_hand_side);
    std::vector<std::vector<std::string>> production_rules;
    std::string found_rule;
    for (unsigned long i = 0; i<right_hand_side.size(); i++) {
        if (right_hand_side[i]==PRODUCTION_RULES_SEPARATOR and right_hand_side[i-1]!=ESCAPE_CHARACTER) {
            production_rules.push_back(vectorizeProductionRuleString(found_rule));
            found_rule.clear();
        }
        else
            found_rule += right_hand_side[i];
    }
    production_rules.push_back(vectorizeProductionRuleString(found_rule));
    non_terminal.setProduction_rules_(production_rules);
}

std::vector<std::string> GrammarParser::vectorizeProductionRuleString(std::string& production_rule)
{
    util::trimBothEnds(production_rule);
    util::removeExtraSpaces(production_rule);
    std::vector<std::string> rule_terms = util::splitOnDelimiter(production_rule,
            PRODUCTION_RULE_TERMS_SEPARATOR);
    for (auto& rule_term : rule_terms) {
        util::trimBothEnds(rule_term);
        if (isEscapedTerminal(rule_term))
            rule_term.erase(rule_term.begin());

        if (isInvalidNonTerminal(rule_term)) {
            std::cerr << "Error found in grammar rules ! A non-terminal (" << rule_term
                      << ") was used but not defined. This maybe also because of wrong input file format required."
                      << std::endl;
            std::exit(0);
        }
    }
    return rule_terms;
}