/**
    Compiler Phase 2: PRSGEN
    parsing_table_generator.cpp
    Purpose: Generates and maintains the logic of creating the parsing table used by the parser. That is composed of three main components: Computing first and follow sets and construction of the table.

    @author(s) Omar Swidan
    @version 1.0
    @date 21/4/2020
*/

#include "parsing_table_generator.h"
#include "grammar_parser.h"
#include <utility>
#include <unordered_set>
#include <iostream>
using std::vector;
using std::string;
using std::unordered_set;
using std::make_pair;
using std::cout;
using std::endl;
const string epsilon = EPSILON_EXPRESSION;

/******** Public Methods ********/

ParsingTableGenerator::ParsingTableGenerator(std::unordered_set<std::string>& terminals_,
        std::vector<NonTerminal>& non_terminals_)
        :terminals_(terminals_), non_terminals_(non_terminals_)
{
    for (auto&& non_terminal:non_terminals_) {
        name_non_terminal_.insert(make_pair(non_terminal.getName_(), &non_terminal));
    }
    //for each production element if it's a non terminal then add it to the map with the value to be the set of its parents
    for (auto&& non_terminal:non_terminals_) {
        for (auto&& production  : non_terminal.getProduction_rules_()) {
            for (auto&& production_element: production) {
                //If the element is a non terminal
                if (name_non_terminal_.count(production_element)) {
                    //Check if this non terminal production element is added to the map before
                    if (non_terminal_non_terminal_parents.count(production_element)) {
                        non_terminal_non_terminal_parents[production_element].insert(
                                non_terminal.getName_());
                    }
                    else {
                        non_terminal_non_terminal_parents.
                                insert(
                                make_pair(production_element, unordered_set<string>{non_terminal.getName_()}));
                    }
                }
            }
        }
    }
}

/**
 * It's assumed in this function that the non terminals vector member variable is ordered so that the last non terminal
 * corresponds to the last production in the grammar and that its first set contains no other non terminal
 */
void ParsingTableGenerator::computeFirst()
{
    for (int i = static_cast<int>(non_terminals_.size()-1); i>=0; i--) {
        //Get all production rules of the current non terminal
        const vector<vector<string>>& productions = non_terminals_[i].getProduction_rules_();
        unordered_set<string> first;
        for (auto&& production: productions) {
            int j = 0;
            //loop on the elements of each production which can be a terminal, a non terminal or an epsilon
            for (auto&& production_element: production) {
                if (production_element==epsilon) {
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
                if (j==production.size()-1 && name_non_terminal_[production_element]->getFirst_().count(epsilon))
                    first.insert(epsilon);
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

void ParsingTableGenerator::computeFollow()
{
    for (int i = 0; i<non_terminals_.size(); ++i) {
        unordered_set<string> follow;
        if (i==0) follow.insert("$");
        //Get a vector of the parents of this non terminal to iterate on the productions that contains the current non terminal
        const unordered_set<string>& non_terminal_parents = non_terminal_non_terminal_parents[non_terminals_[i].getName_()];
        //Loop on the parents of the current non terminal
        for (auto&& non_terminal_parent_name : non_terminal_parents) {
            NonTerminal* non_terminal_parent = name_non_terminal_[non_terminal_parent_name];
            //Loop on the productions of this parent to get compute the follow set
            for (auto&& production: non_terminal_parent->getProduction_rules_()) {
                fill_follow_from_production(follow, production, non_terminals_[i],
                        *non_terminal_parent);
            }
        }
        non_terminals_[i].setFollow_(follow);
    }
}

void ParsingTableGenerator::constructParsingTable()
{
    //TODO: PRSGEN-7
}

void ParsingTableGenerator::writeParseingTable()
{
    //TODO: PRSGEN-9
}

/******** Private Methods ********/

void ParsingTableGenerator::fill_follow_from_production(std::unordered_set<std::string>& follow,
        const vector<string>& production,
        const NonTerminal& current, const NonTerminal& parent)
{
    //Loop on the elements of this production
    for (int j = 0; j<production.size(); ++j) {
        //This check is done to locate the current non terminal in the current production
        //Take care that not all of the productions of this parent have to contain this non terminal as only the parent is stored
        //so it's an at least once relationship
        if (production[j]==current.getName_()) {
            //Check if the non terminal is the last element in the production
            if (j==production.size()-1) {
                unordered_set<string> parent_follow = parent.getFollow_();
                follow.merge(parent_follow);
                //Break and move to the next production
                break;
            }
            if (terminals_.count(production[j+1])) {
                //Insert the terminal as is as in the follow set as it first is the same as its name
                follow.insert(production[j+1]);
                //Continue iterating in case the current non terminal is repeated in the production again
                j++;
                continue;
            }
            unordered_set<string> right_sibling_first = name_non_terminal_[production[j+1]]->getFirst_();
            //Check if the right sibling is the last element in the production and it contains an epsilon in its first set
            if (j+1==production.size()-1 && right_sibling_first.count(epsilon)) {
                unordered_set<string> parent_follow = parent.getFollow_();
                follow.merge(parent_follow);
            }
            right_sibling_first.erase(epsilon);
            //Add the right sibling's first to the current non terminal's follow set
            follow.merge(right_sibling_first);
        }
    }
}
