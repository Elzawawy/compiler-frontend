//
// Created by zawawy on 4/21/20.
//

#include <fstream>
#include <iostream>
#include "grammar_parser.h"
#include "../utils.h"
#define PRODUCTION_RULE_SEPARATOR '#'
#define PRODUCTION_RULE_SIDES_SEPARATOR "::="
#define RIGHT_HAND_SIDE_INDEX 1
#define RIGHT_HAND_SIDE_SEPARATOR ' '
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
        std::string production_rule;
        while (std::getline(file, production_rule, PRODUCTION_RULE_SEPARATOR)) {
            if(production_rule.empty())
                continue;
            std::vector<std::string> rule_sides = util::splitOnStringDelimiter(production_rule, PRODUCTION_RULE_SIDES_SEPARATOR);
            std::string right_hand_side = rule_sides[RIGHT_HAND_SIDE_INDEX];
            std::vector<std::string> right_hand_terms = util::splitOnDelimiter(right_hand_side, RIGHT_HAND_SIDE_SEPARATOR);
            for (auto& term: right_hand_terms)
                if(term[0] == TERMINAL_INDICATOR) {
                    util::trimBothEnds(term);
                    util::stripFirstAndLastChars(term);
                    terminals_.insert(term);
                }
        }
        file.close();
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