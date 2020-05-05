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
using std::vector;
using std::string;
using std::unordered_set;

const string epsilon = EPSILON_EXPRESSION;

ParsingTableGenerator::ParsingTableGenerator(std::unordered_set<std::string>& terminals_,
        std::vector<NonTerminal>& non_terminals_)
        :terminals_(terminals_), non_terminals_(non_terminals_)
{
    for (auto&& non_terminal:non_terminals_) {
        name_non_terminal_.insert(std::make_pair(non_terminal.getName_(), &non_terminal));
    }
};

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
    //TODO: PRSGEN-6
}

void ParsingTableGenerator::constructParsingTable()
{
    //TODO: PRSGEN-7
}

void ParsingTableGenerator::writeParseingTable()
{
    //TODO: PRSGEN-9
}
