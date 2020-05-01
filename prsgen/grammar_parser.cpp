//
// Created by zawawy on 4/21/20.
//
#include <iostream>
#include "grammar_parser.h"
const std::set<std::string>& GrammarParser::getTerminals_() const
{
    return terminals_;
}
const std::vector<NonTerminal>& GrammarParser::getNon_terminals_() const
{
    return non_terminals_;
}

void GrammarParser::parseFile(std::string file_name)
{
    //TODO: PRSGEN-2
}

void GrammarParser::eliminateLeftRecursion()
{
    //TODO: PRSGEN-3
	
}
std::vector<NonTerminal> GrammarParser::eliminateImmediateLeftRecursion(NonTerminal * non_terminal)
{
	//checkImmediateLeftRecursion(non_terminal)
	
	
}
bool GrammarParser::checkImmediateLeftRecursion(NonTerminal * non_terminal)
{
	//get the production rules of the non terminal
	std::vector<std::vector<std::string>> production_rules = non_terminal->getProduction_rules_();

	//iterate through the production rules  
	std::vector< std::vector<std::string> >::iterator row;
	std::vector<std::string>::iterator col;
	for (row = production_rules.begin(); row != production_rules.end(); row++) {
		col = row->begin();
		//check if the first nonterminal symbol is the same as the name of nonterminal
		if (non_terminal->getName_().compare(*col) == 0)
		{
			return true;

		}	
	}

	return false;
}



void GrammarParser::eliminateLeftFactoring()
{
    //TODO: PRSGEN-4
}