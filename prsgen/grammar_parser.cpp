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

const std::unordered_set<std::string> &GrammarParser::getTerminals_() const {
    return terminals_;
}

const std::vector<NonTerminal> &GrammarParser::getNon_terminals_() const {
    return non_terminals_;
}


void GrammarParser::parseFile(std::string grammar_file_path) {
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

            for (unsigned long i = 0; i < right_hand_side.size(); i++) {
                std::string found_terminal;
                if (right_hand_side[i] == TERMINAL_INDICATOR) {
                    right_hand_side.replace(i, 1, " ");
                    while (right_hand_side[++i] != TERMINAL_INDICATOR or right_hand_side[i - 1] == '\\') {
                        if (right_hand_side[i] == '\\')
                            continue;
                        found_terminal += right_hand_side[i];
                    }
                    right_hand_side.replace(i, 1, " ");
                    terminals_.insert(found_terminal);
                }
            }
            std::vector<std::vector<std::string>> production_rules;
            std::string found_rule;
            for (unsigned long i = 0; i < right_hand_side.size(); i++) {
                if (right_hand_side[i] == PRODUCTION_RULES_SEPARATOR and right_hand_side[i - 1] != '\\') {
                    util::trimBothEnds(found_rule);
                    util::removeExtraSpaces(found_rule);
                    std::vector<std::string> rule_terms = util::splitOnDelimiter(found_rule,
                                                                                 PRODUCTION_RULE_TERMS_SEPARATOR);
                    for (int j = 0; j < rule_terms.size(); j++) {
                        util::trimBothEnds(rule_terms[j]);
                        if (rule_terms[j][0] == '\\')
                            rule_terms[j].erase(rule_terms[j].begin());
                        else if (rule_terms[j] == " ")
                            rule_terms.erase(rule_terms.begin() + j);
                    }
                    production_rules.push_back(rule_terms);
                    found_rule = "";
                } else
                    found_rule += right_hand_side[i];
            }
            util::trimBothEnds(found_rule);
            util::removeExtraSpaces(found_rule);
            std::vector<std::string> rule_terms = util::splitOnDelimiter(found_rule,
                                                                         PRODUCTION_RULE_TERMS_SEPARATOR);
            for (auto &rule_term : rule_terms) {
                util::trimBothEnds(rule_term);
                if (rule_term[0] == '\\')
                    rule_term.erase(rule_term.begin());
            }
            production_rules.push_back(rule_terms);
            non_terminal.setProduction_rules_(production_rules);
            non_terminals_.push_back(non_terminal);
        }
    }
//    for (auto& terminal: terminals_)
//        std::cout << terminal << std::endl;
    for (auto &non_terminal: non_terminals_) {
        std::cout << "---------" << non_terminal.getName_() << "----------" << std::endl;
        for (auto &rule: non_terminal.getProduction_rules_()) {
            std::cout << "==========RULE =========" << std::endl;
            for (auto &term: rule)
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

void GrammarParser::eliminateRightFactoring() {
    //TODO: PRSGEN-3
}

void GrammarParser::eliminateLeftFactoring() {
    std::vector<NonTerminal> temp_non_terminals_;
    temp_non_terminals_.push_back((this->non_terminals_)[0]);
    int non_terminals_index = 0;
    bool possible_factoring = false;
    for (int iterator = 0; iterator < temp_non_terminals_.size(); iterator++) {
        possible_factoring = false;
        std::vector<std::vector<std::string>> production_rules = (temp_non_terminals_[iterator]).getProduction_rules_();
        std::map<std::string, std::vector<int>> factoring_map;

        /**
         *  iterating over the production rules and getting the common starts and marking them as factors to be
         *  factorized in the next loop
         */
        for (int index = 0; index < production_rules.size(); index++) {

            /**if the start of the production rule is not present in the factoring map
             * then add a new key in the factoring map with the new start of this production rule and add the index of the
             * production rule as the first element in the array of values of the factoring map
             */
            if (factoring_map.find((production_rules[index])[0]) == factoring_map.end()) {
                std::vector<int> factored_index;
                factored_index.push_back(index);
                factoring_map.insert({(production_rules[index])[0], factored_index});

            }
                /**if the start of the production rule is present in the factoring map which means that it should be factore
                 * then push the index of the production rule in the array of the value of the map
                 */
            else {
                possible_factoring = true;
                std::map<std::string, std::vector<int>>::iterator it = factoring_map.find(
                        (production_rules[index])[0]);
                (it->second).push_back(index);
            }
        }
        /**
         *   Looping over the factoring map and creating new non terminals if needed by checking each array value in the map
         *   and using their indices to factor the common production rules
         */
        std::map<std::string, std::vector<int>>::iterator it = factoring_map.begin();
        std::vector<std::vector<std::string>> factored_production_rules;
        std::vector<std::vector<std::string>> editted_factored_production_rules;

        int name_index = 0, production_rules_iterator = 0, non_production_rules_iterator = 0;
        bool new_non_terminals_added = false;
        std::string factored_non_terminal_name;
        for (std::pair<std::string, std::vector<int>> element : factoring_map) {
            /**
             *   check if at least 2 production rules has a common start
             */
            std::vector<std::string> pr;
            if ((element.second).size() > 1) {

                new_non_terminals_added = true;
                factored_non_terminal_name = (temp_non_terminals_[iterator]).getName_() + std::to_string(name_index);

                /**
                 *  editting the production rules of the factored rule by adding the new non terminals
                 */
                pr.push_back(element.first);
                pr.push_back(factored_non_terminal_name);
                (editted_factored_production_rules).push_back(pr);
                pr.clear();

                /**
                 * creating the new non terminal for the factored production rules
                 */
                for (int index = 0; index < (element.second).size(); index++) {
                    /**
                     * from the productions indices saved , loop over the vector of strings in the production
                     * and add it to the new production and neglecting the first element which was the common element
                     */
                    std::vector<std::string> temp_pr;

                    for (int origin_production_rule_index = 1; origin_production_rule_index <
                                                               production_rules[(element.second)[index]].size(); origin_production_rule_index++) {
                        temp_pr.push_back((production_rules[(element.second)[index]])[origin_production_rule_index]);
                    }
                    if (temp_pr.size() == 0) {
                        temp_pr.push_back("\\L");
                    }
                    (factored_production_rules).push_back(temp_pr);

                }
                /**
                 * Adding new factored non terminals with factored production rule
                 */
                NonTerminal *factored_non_terminal = new NonTerminal(factored_non_terminal_name);
                factored_non_terminal->setProduction_rules_(factored_production_rules);
                temp_non_terminals_.push_back(*factored_non_terminal);
                factored_production_rules.clear();

                name_index++;
                production_rules_iterator++;
            } else {
                std::vector<std::string> temp_pr;

                for (int origin_production_rule_index = 0; origin_production_rule_index <
                                                           production_rules[(element.second)[0]].size(); origin_production_rule_index++) {
                    temp_pr.push_back((production_rules[(element.second)[0]])[origin_production_rule_index]);
                }

                editted_factored_production_rules.push_back((temp_pr));

            }
            non_production_rules_iterator++;
        }
        /**
         *  Editting the original factored non terminal by adding the eddited production rule
         */
        if (new_non_terminals_added) {
            (temp_non_terminals_[iterator]).setProduction_rules_(editted_factored_production_rules);
        }
        /**
         *If the previous rule has nothing to be factored then add new non terminal from the original vector
         */
        if (!new_non_terminals_added && non_terminals_index < non_terminals_.size() - 1) {
            non_terminals_index++;
            temp_non_terminals_.push_back((non_terminals_[non_terminals_index]));

        }
    }
    this->non_terminals_ = temp_non_terminals_;
}