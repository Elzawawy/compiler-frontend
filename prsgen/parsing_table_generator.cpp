#include "parsing_table_generator.h"
#include <utility>
#include <set>
#include <unordered_set>
#include <iostream>

using std::vector;
using std::string;
using std::set;
using std::unordered_set;
using std::make_pair;
using std::cout;
using std::endl;

const string epsilon = "\\L";

ParsingTableGenerator::ParsingTableGenerator(std::unordered_set<std::string> &terminals_,
                                             std::vector<NonTerminal> &non_terminals_)
        : terminals_(terminals_), non_terminals_(non_terminals_) {
    for (auto &&non_terminal:non_terminals_) {
        name_non_terminal_.insert(make_pair(non_terminal.getName_(), &non_terminal));
    }
    //for each production element if it's a non terminal then add it to the map with the value to be the set of its parents
    for (auto &&non_terminal:non_terminals_) {
        for (auto &&production  : non_terminal.getProduction_rules_()) {
            for (auto &&production_element: production) {
                //If the element is a non terminal
                if (name_non_terminal_.count(production_element)) {
                    //Check if this non terminal production element is added to the map before
                    if (non_terminal_parent_non_terminals.count(production_element)) {
                        non_terminal_parent_non_terminals[production_element].insert(
                                non_terminal.getName_());
                    } else {
                        non_terminal_parent_non_terminals.
                                insert(
                                make_pair(production_element, unordered_set<string>{non_terminal.getName_()}));
                    }
                }
            }
        }
    }
};

/**
 * It's assumed in this function that the non terminals vector member variable is ordered so that the last non terminal
 * corresponds to the last production in the grammar and that its first set contains no other non terminal
 */
void ParsingTableGenerator::computeFirst() {
    for (int i = static_cast<int>(non_terminals_.size() - 1); i >= 0; i--) {
        //Get all production rules of the current non terminal
        const vector<vector<string>> &productions = non_terminals_[i].getProduction_rules_();
        unordered_set<string> first;
        for (auto &&production: productions) {
            int j = 0;
            //loop on the elements of each production which can be a terminal, a non terminal or an epsilon
            for (auto &&production_element: production) {
                if (production_element == epsilon) {
                    first.insert(epsilon);
                    break;
                }
                //If this condition is true then we should break the loop as if a terminal is found then no other non terminal or terminal
                //after it will be added to the first set
                if (terminals_.count(production_element)) {
                    first.insert(production_element);
                    break;
                }

                //if epsilon is in all the non terminals in the production then add epsilon the first set
                if (j == production.size() - 1 && name_non_terminal_[production_element]->getFirst_().count(epsilon)) {
                    first.insert(epsilon);
                }
                //Has to be copied to  variable as the getter returns a const
                unordered_set<string> production_non_terminal_first = name_non_terminal_[production_element]->getFirst_();
                //Add to the first the first of Yi
                first.merge(production_non_terminal_first);

                //Break if Yi doesn't  derive epsilon
                if (!name_non_terminal_[production_element]->getFirst_().count(epsilon)) break;
                j++;

            }
        }
        //add first to non terminal
        non_terminals_[i].setFirst_(first);
    }
}

void ParsingTableGenerator::computeFollow() {
    //TODO: PRSGEN-6
}

void ParsingTableGenerator::constructParsingTable() {
    //TODO: PRSGEN-7
}

void ParsingTableGenerator::writeParseingTable() {
    //TODO: PRSGEN-9
}
