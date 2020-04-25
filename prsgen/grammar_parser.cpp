//
// Created by zawawy on 4/21/20.
//

#include <fstream>
#include <iostream>
#include "grammar_parser.h"
#define PRODUCTION_RULE_SEPARTOR '#'
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
        while (std::getline(file, production_rule, PRODUCTION_RULE_SEPARTOR)){

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