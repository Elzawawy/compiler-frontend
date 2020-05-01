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
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            if (non_terminal_definition.empty())
                continue;
            std::vector<std::string> rule_sides = util::splitOnStringDelimiter(non_terminal_definition,
                    NON_TERMINAL_SIDES_SEPARATOR);
            std::string right_hand_side = rule_sides[RIGHT_HAND_SIDE_INDEX];
            std::string left_hand_side = rule_sides[LEFT_HAND_SIDE_INDEX];
            util::trimBothEnds(left_hand_side);
            util::trimBothEnds(right_hand_side);
            NonTerminal non_terminal(left_hand_side);

            for (unsigned long i = 0; i<right_hand_side.size(); i++) {
                std::string found_terminal;
                if (right_hand_side[i]==TERMINAL_INDICATOR) {
                    right_hand_side.replace(i, 1, " ");
                    while (right_hand_side[++i]!=TERMINAL_INDICATOR or right_hand_side[i-1]=='\\') {
                        if (right_hand_side[i]=='\\')
                            continue;
                        found_terminal += right_hand_side[i];
                    }
                    right_hand_side.replace(i, 1, " ");
                    terminals_.insert(found_terminal);
                }
            }
            std::vector<std::vector<std::string>> production_rules;
            std::string found_rule;
            for (unsigned long i = 0; i<right_hand_side.size(); i++) {
                if (right_hand_side[i]==PRODUCTION_RULES_SEPARATOR and right_hand_side[i-1]!='\\') {
                    util::trimBothEnds(found_rule);
                    util::removeExtraSpaces(found_rule);
                    std::vector<std::string> rule_terms = util::splitOnDelimiter(found_rule,
                            PRODUCTION_RULE_TERMS_SEPARATOR);
                    for (int j = 0; j<rule_terms.size();j++) {
                        util::trimBothEnds(rule_terms[j]);
                        if (rule_terms[j][0]=='\\')
                            rule_terms[j].erase(rule_terms[j].begin());
                        else if(rule_terms[j] == " ")
                            rule_terms.erase(rule_terms.begin()+j);
                    }
                    production_rules.push_back(rule_terms);
                    found_rule = "";
                }
                else
                    found_rule += right_hand_side[i];
            }
            util::trimBothEnds(found_rule);
            util::removeExtraSpaces(found_rule);
            std::vector<std::string> rule_terms = util::splitOnDelimiter(found_rule,
                    PRODUCTION_RULE_TERMS_SEPARATOR);
            for (auto& rule_term : rule_terms) {
                util::trimBothEnds(rule_term);
                if (rule_term[0]=='\\')
                    rule_term.erase(rule_term.begin());
            }
            production_rules.push_back(rule_terms);
            non_terminal.setProduction_rules_(production_rules);
            non_terminals_.push_back(non_terminal);
        }
    }
//    for (auto& terminal: terminals_)
//        std::cout << terminal << std::endl;
    for (auto& non_terminal: non_terminals_) {
        std::cout << "---------" << non_terminal.getName_() << "----------" << std::endl;
        for (auto& rule: non_terminal.getProduction_rules_()) {
            std::cout << "==========RULE =========" << std::endl;
            for (auto& term: rule)
                std::cout << term << std::endl;
        }
    }



//            NonTerminal non_terminal(left_hand_side);
//
//
//
//
//            std::vector<std::string> production_rules = util::splitOnStringDelimiter(right_hand_side, PRODUCTION_RULES_SEPARATOR);
//            std::vector<std::vector<std::string>> non_terminal_production_rules;
//            for (auto& rule: production_rules) {
//                util::trimBothEnds(rule);
//                std::vector<std::string> rule_terms = util::splitOnDelimiter(rule, PRODUCTION_RULE_TERMS_SEPARATOR);
//                for (int rule_index = 0; rule_index<rule_terms.size();rule_index++) {
//                    if (rule_terms[rule_index][0]==TERMINAL_INDICATOR) {
//                        util::stripFirstAndLastChars(rule_terms[rule_index]);
//                        terminals_.insert(rule_terms[rule_index]);
//                    }
//                    //std::cout << rule_terms[rule_index] << std::endl;
//                }
//                non_terminal_production_rules.push_back(rule_terms);
//               // std::cout<<"========"<<std::endl;
//            }
//            non_terminal.setProduction_rules_(non_terminal_production_rules);
//            non_terminals_.push_back(non_terminal);
//        }
//        file.close();
//    }
//    for (auto& non_terminal: non_terminals_) {
//        std::cout<<"---------"<<non_terminal.getName_()<<"----------"<<std::endl;
//        for (auto& rule: non_terminal.getProduction_rules_()) {
//            std::cout << "==========RULE =========" << std::endl;
//            for (auto& term: rule)
//                std::cout << term << std::endl;
//        }
//    }

}

void GrammarParser::eliminateRightFactoring()
{
    //TODO: PRSGEN-3
}
void GrammarParser::eliminateLeftFactoring()
{
    //TODO: PRSGEN-4
}