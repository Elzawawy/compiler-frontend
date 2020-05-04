//
// Created by zawawy on 4/21/20.
//
#include <iostream>
#include "grammar_parser.h"
#include <algorithm>    // std::transform


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

std::unordered_set<std::string> &GrammarParser::getTerminals_() {
    return terminals_;
}

std::vector<NonTerminal> &GrammarParser::getNon_terminals_() {
    return non_terminals_;
}


void GrammarParser::parseFile(std::string grammar_file_path) {
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
            std::unordered_set<std::string> terminals = extractTerminalsFromRHS(right_hand_side);
            terminals_.insert(terminals.begin(), terminals.end());
            non_terminal.setProduction_rules_(extractProductionRulesFromRHS(right_hand_side, non_terminal));
            non_terminals_.push_back(non_terminal);
        }
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

std::vector<NonTerminal*> GrammarParser::eliminateImmediateLeftRecursion(NonTerminal* non_terminal)
{
    //create new non terminal and new nonterminal `
    NonTerminal* new_non_terminal = new NonTerminal(non_terminal->getName_());
    NonTerminal* non_terminal_dash = new NonTerminal(non_terminal->getName_()+"`");

    //create 2 lists of betas and alpahas to store the proper values extracted from the production rules
    std::vector<std::vector<std::string>> betas;
    std::vector<std::vector<std::string>> alphas;
    //get the prduction rules and extract alphas and betas from it
    std::vector<std::vector<std::string>> production_rules = non_terminal->getProduction_rules_();

    //iterate through the production rules
    std::vector<std::vector<std::string> >::iterator row;
    std::vector<std::string>::iterator col;
    for (row = production_rules.begin(); row!=production_rules.end(); row++) {
        std::vector<std::string> tmp_alpha;
        std::vector<std::string> tmp_beta;
        //check if nonterminal name equals  to first letter or not  to determine will it be added to alpha or beta vector
        col = row->begin();
        if (non_terminal->getName_().compare(*col)==0) {
            // it's alpha then push the next of this non terminal to alpha vector
            for (col = col+1; col!=row->end(); col++) {

                tmp_alpha.push_back(*col);
            }
            //append  nonterminal` as the given rule in the end of the alpha
            tmp_alpha.push_back(non_terminal->getName_()+"`");
            alphas.push_back(tmp_alpha);
        }
        else {
            //same for beta but it will work from the start of the string
            for (col = row->begin(); col!=row->end(); col++) {

                tmp_beta.push_back(*col);

            }
            tmp_beta.push_back(non_terminal->getName_()+"`");
            betas.push_back(tmp_beta);
        }

    }
    //addinng epsilon to nonterminal`
    std::vector<std::string> epsilon;
    epsilon.push_back("\\L");
    alphas.push_back(epsilon);

    new_non_terminal->setProduction_rules_(betas);
    non_terminal_dash->setProduction_rules_(alphas);

    std::vector<NonTerminal*> returned_terminals;
    returned_terminals.push_back(new_non_terminal);
    returned_terminals.push_back(non_terminal_dash);

    return returned_terminals;
}

bool GrammarParser::checkImmediateLeftRecursion(NonTerminal* non_terminal)
{
    //get the production rules of the non terminal
    std::vector<std::vector<std::string>> production_rules = non_terminal->getProduction_rules_();

    //iterate through the production rules
    std::vector<std::vector<std::string> >::iterator row;
    std::vector<std::string>::iterator col;
    for (row = production_rules.begin(); row!=production_rules.end(); row++) {
        col = row->begin();
        //check if the first nonterminal symbol is the same as the name of nonterminal
        if (non_terminal->getName_().compare(*col)==0) {
            return true;

        }
    }

    return false;
}

NonTerminal* GrammarParser::subsitution(NonTerminal* current_non_terminal, NonTerminal* input)
{

    std::vector<std::vector<std::string>> production_rules_current = current_non_terminal->getProduction_rules_();
    std::vector<std::vector<std::string>> production_rules_input = input->getProduction_rules_();

    std::vector<std::vector<std::string> >::iterator row;
    std::vector<std::string>::iterator col;

    std::vector<std::vector<std::string> > tmp_prod_rules;
    std::vector<std::string> tmp_vstr;

    //loop through current non terminal elements
    for (row = production_rules_current.begin(); row!=production_rules_current.end(); row++) {

        col = row->begin();
        // check if first letter is identical to the input name
        if (input->getName_().compare(*col)!=0) {
            //if not identical copy all vectors to new production rule as there wont be any change in them
            for (col = row->begin(); col!=row->end(); col++) {

                tmp_vstr.push_back(*col);

            }
            tmp_prod_rules.push_back(tmp_vstr);
            tmp_vstr.clear();
        }
        else {
            //if identical clone the current vector into the new production rule times the input length


            std::vector<std::vector<std::string> >::iterator input_row;
            std::vector<std::string>::iterator input_col;

//					

            for (input_row = production_rules_input.begin(); input_row!=production_rules_input.end(); input_row++) {

                //concat input production rules with one I want to substitue with from the beginning
                std::vector<std::string> the_copy(*input_row);
                //skip the substituted symbol and continue concat with the given non terminal
                for (col = row->begin()+1; col!=row->end(); col++) {
                    the_copy.push_back(*col);
                }
                tmp_prod_rules.push_back(the_copy);
            }
        }

    }

    NonTerminal* new_non_terminal = new NonTerminal(current_non_terminal->getName_());
    new_non_terminal->setProduction_rules_(tmp_prod_rules);

    return new_non_terminal;
}

template<typename T>
std::vector<T*> convertFrom(std::vector<T>& source)
{
    std::vector<T*> target(source.size());
    std::transform(source.begin(), source.end(), target.begin(), [](T& t) { return &t; });
    return target;
}

void GrammarParser::eliminateLeftRecursion()
{
    std::vector<NonTerminal*> non_terminal_list_p = convertFrom(non_terminals_);

    std::vector<NonTerminal*> new_non_terminal_list;
    std::vector<NonTerminal*>::iterator non_terminal_iterator = non_terminal_list_p.begin();

    for (int i = 0; i<non_terminal_list_p.size(); i++) {
        NonTerminal* processing_non_terminal = *(non_terminal_list_p.begin()+i);
        for (int j = 0; j<i; j++) {
            processing_non_terminal = subsitution(processing_non_terminal, *(non_terminal_iterator+j));

        }
        if (checkImmediateLeftRecursion(processing_non_terminal)) {
            std::vector<NonTerminal*> after_immediate_fix = eliminateImmediateLeftRecursion(processing_non_terminal);
            new_non_terminal_list.insert(new_non_terminal_list.end(), after_immediate_fix.begin(),
                    after_immediate_fix.end());
            *(non_terminal_list_p.begin()+i) = after_immediate_fix[0];
        }
        else {
            NonTerminal* x = new NonTerminal(*(*non_terminal_list_p.begin()+i));
            new_non_terminal_list.push_back(x);
        }
    }
    non_terminals_.clear();
    non_terminals_.reserve(non_terminal_list_p.size());

    for (int j = 0; j<new_non_terminal_list.size(); j++) {
        non_terminals_.push_back(**(new_non_terminal_list.begin()+j));

    }
//    for (auto& terminal: terminals_)
//        std::cout << terminal << std::endl;
    std::cout << "**************After Abdo************" << std::endl;
    for (auto& non_terminal: non_terminals_) {
        std::cout << "---------" << non_terminal.getName_() << "----------" << std::endl;
        for (auto &rule: non_terminal.getProduction_rules_()) {
            std::cout << "==========RULE =========" << std::endl;
            for (auto &term: rule)
                std::cout << term << std::endl;
        }
    }

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

    std::cout<<"********* After Abdallah ************"<<std::endl;
    for (auto &non_terminal: non_terminals_) {
        std::cout << "---------" << non_terminal.getName_() << "----------" << std::endl;
        for (auto &rule: non_terminal.getProduction_rules_()) {
            std::cout << "==========RULE =========" << std::endl;
            for (auto &term: rule)
                std::cout << term << std::endl;
        }
    }
}

std::unordered_set<std::string> GrammarParser::extractTerminalsFromRHS(std::string& right_hand_side)
{
    util::trimBothEnds(right_hand_side);
    std::unordered_set<std::string> terminals;
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
            terminals.insert(found_terminal);
        }
    }
    return terminals;
}

std::vector<std::vector<std::string>> GrammarParser::extractProductionRulesFromRHS(std::string& right_hand_side,
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
    return production_rules;
}

std::vector<std::string> GrammarParser::vectorizeProductionRuleString(std::string& production_rule)
{
    util::trimBothEnds(production_rule);
    util::removeExtraSpaces(production_rule);
    std::vector<std::string> rule_terms = util::splitOnDelimiter(production_rule,
            PRODUCTION_RULE_TERMS_SEPARATOR);
    for (auto& rule_term : rule_terms) {
        util::trimBothEnds(rule_term);
        if (rule_term[0]==ESCAPE_CHARACTER and rule_term!=EPSILON_EXPRESSION)
            rule_term.erase(rule_term.begin());
    }
    return rule_terms;
}

