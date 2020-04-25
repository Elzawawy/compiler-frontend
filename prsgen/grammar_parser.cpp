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

const std::set<std::string>& GrammarParser::getTerminals_() const
{
    return terminals_;
}
const std::vector<NonTerminal>& GrammarParser::getNon_terminals_() const
{
    return non_terminals_;
}

void GrammarParser::parseFile(std::string grammar_file_path)
{
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            if (non_terminal_definition.empty())
                continue;
            std::vector<std::string> rule_sides = util::splitOnStringDelimiter(non_terminal_definition, NON_TERMINAL_SIDES_SEPARATOR);
            std::string right_hand_side = rule_sides[RIGHT_HAND_SIDE_INDEX];
            std::string left_hand_side = rule_sides[LEFT_HAND_SIDE_INDEX];
            util::trimBothEnds(left_hand_side);
            util::trimBothEnds(right_hand_side);
            NonTerminal non_terminal(left_hand_side);
            std::vector<std::string> production_rules = util::splitOnDelimiter(right_hand_side, PRODUCTION_RULES_SEPARATOR);
            std::vector<std::vector<std::string>> non_terminal_production_rules;
            for (auto& rule: production_rules) {
                util::trimBothEnds(rule);
                std::vector<std::string> rule_terms = util::splitOnDelimiter(rule, PRODUCTION_RULE_TERMS_SEPARATOR);
                for (auto& term: rule_terms) {
                    if (term[0]==TERMINAL_INDICATOR) {
                        util::stripFirstAndLastChars(term);
                        terminals_.insert(term);
                    }
                   // std::cout<<term<<std::endl;
                }
                non_terminal_production_rules.push_back(rule_terms);
               // std::cout<<"========"<<std::endl;
            }
            non_terminal.setProduction_rules_(non_terminal_production_rules);
            non_terminals_.push_back(non_terminal);
        }
        file.close();
    }
    for (auto& non_terminal: non_terminals_) {
        std::cout<<"NON TERMINAL ---------"<<std::endl;
        for (auto& rule: non_terminal.getProduction_rules_()) {
            std::cout << "RULE =========" << std::endl;
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