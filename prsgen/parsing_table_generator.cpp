//
// Created by zawawy on 4/21/20.
//

#include "parsing_table_generator.h"

ParsingTableGenerator::ParsingTableGenerator(std::set<std::string>& terminals_,
        std::vector<NonTerminal>& non_terminals_)
        :terminals_(terminals_), non_terminals_(non_terminals_) { }

void ParsingTableGenerator::computeFirst()
{
    //TODO: PRSGEN-5
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
