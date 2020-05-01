//
// Created by zawawy on 4/21/20.
//

#include <iostream>
#include "grammar_parser.h"

const std::set<std::string> &GrammarParser::getTerminals_() const {
    return terminals_;
}

const std::vector<NonTerminal> &GrammarParser::getNon_terminals_() const {
    return non_terminals_;
}

void GrammarParser::parseFile(std::string file_name) {
    //TODO: PRSGEN-2
}

void GrammarParser::eliminateRightFactoring() {
    //TODO: PRSGEN-3
}

void GrammarParser::eliminateLeftFactoring() {
    
    std::vector<NonTerminal> temp_non_terminals_;
    temp_non_terminals_.push_back((this->non_terminals_)[0]);
    int non_terminals_index = 0;
    for (auto non_terminal:temp_non_terminals_) {
        std::vector<std::vector<std::string>> production_rules = non_terminal.getProduction_rules_();
        std::unordered_map<std::string, std::vector<int>> factoring_map;
        /**
         *  iterating over the production rules and getting the common starts and marking them as factors to be
         *  factorized in the next loop
         */
        for (int index = 0; index < production_rules.size(); index++) {
            std::cout << ((production_rules[index])[0]) << std::endl;

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
                std::unordered_map<std::string, std::vector<int>>::iterator it = factoring_map.find(
                        (production_rules[index])[0]);
                (it->second).push_back(index);
            }
        }
        /**
         *   Looping over the factoring map and creating new non terminals if needed by checking each array value in the map
         *   and using their indices to factor the common production rules
         */
        std::unordered_map<std::string, std::vector<int>>::iterator it = factoring_map.begin();
        std::vector<std::vector<std::string>> factored_production_rules;
        std::vector<std::vector<std::string>> editted_factored_production_rules;

        int name_index = 0, production_rules_iterator = 0;
        bool new_non_terminals_added = false;
        std::string factored_non_terminal_name;
        for (std::pair<std::string, std::vector<int>> element : factoring_map) {
            /**
             *   check if at least 2 production rules has a common start
             */
            if ((element.second).size() > 1) {
                new_non_terminals_added = true;
                factored_non_terminal_name = non_terminal.getName_() + std::to_string(name_index);

                /**
                 *  editting the production rules of the factored rule by adding the new non terminals
                 */
                (editted_factored_production_rules[name_index]).push_back(element.first);
                (editted_factored_production_rules[name_index]).push_back(factored_non_terminal_name);

                /**
                 * creating the new non terminal for the factored production rules
                 */
                for (int index = 0; index < (element.second).size(); index++) {
                    /**
                     * from the productions indices saved loop over the vector of strings in the production
                     * and add it to the new production and neglecting the first element which was the common element
                     */
                    for (int origin_production_rule_index = 1; origin_production_rule_index <
                                                               production_rules[(element.second)[index]].size(); origin_production_rule_index++) {
                        (factored_production_rules[production_rules_iterator]).push_back(
                                (production_rules[(element.second)[index]])[origin_production_rule_index]);
                    }
                }
                /**
                 * Adding new factored non terminals with factored production rule
                 */
                NonTerminal *factored_non_terminal = new NonTerminal(factored_non_terminal_name);
                factored_non_terminal->setProduction_rules_(factored_production_rules);
                temp_non_terminals_.push_back(*factored_non_terminal);

                name_index++;
                production_rules_iterator++;
            }
        }
        /**
         *  Editting the original factored non terminal by adding the eddited production rule
         */
        non_terminal.setProduction_rules_(editted_factored_production_rules);
        /**
         *If the previous rule has nothing to be factored then add new non terminal from the original vector
         */
        if (!new_non_terminals_added) {
            non_terminals_index++;
            temp_non_terminals_.push_back((non_terminals_[non_terminals_index]));
        }
    }
}