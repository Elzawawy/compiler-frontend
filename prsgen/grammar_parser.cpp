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
std::vector<NonTerminal *> GrammarParser::eliminateImmediateLeftRecursion(NonTerminal * non_terminal)
{
	//create new non terminal and new nonterminal `
	NonTerminal * new_non_terminal = new NonTerminal(non_terminal->getName_());
	NonTerminal * non_terminal_dash = new NonTerminal(non_terminal->getName_() + "`");

	//create 2 lists of betas and alpahas to store the proper values extracted from the production rules
	std::vector<std::vector<std::string>> betas;
	std::vector<std::vector<std::string>> alphas;
	//get the prduction rules and extract alphas and betas from it
		std::vector<std::vector<std::string>> production_rules = non_terminal->getProduction_rules_();

		//iterate through the production rules  
		std::vector< std::vector<std::string> >::iterator row;
		std::vector<std::string>::iterator col;
		for (row = production_rules.begin(); row != production_rules.end(); row++) {
			std::vector<std::string> tmp_alpha;
			std::vector<std::string> tmp_beta;
			//check if nonterminal name equals  to first letter or not  to determine will it be added to alpha or beta vector
			col = row->begin();
			if (non_terminal->getName_().compare(*col) == 0)
			{
				// it's alpha then push the next of this non terminal to alpha vector
				for (col = col +1; col != row->end(); col++) {

					tmp_alpha.push_back(*col);
					
				}
				//append  nonterminal` as the given rule in the end of the alpha
				tmp_alpha.push_back(non_terminal->getName_() + "`");
				alphas.push_back(tmp_alpha);
			}
			else {
				//same for beta but it will work from the start of the string
				for (col = row->begin(); col != row->end(); col++) {

					tmp_beta.push_back(*col);

				}
				tmp_beta.push_back(non_terminal->getName_() + "`");
				betas.push_back(tmp_beta);
			}


		}
		//addinng epsilon to nonterminal` 
		std::vector<std::string> epsilon;
		epsilon.push_back( "\\L");
		alphas.push_back(epsilon);



		new_non_terminal->setProduction_rules_(betas);
		non_terminal_dash->setProduction_rules_(alphas);

		std::vector<NonTerminal *> returned_terminals;
		returned_terminals.push_back(new_non_terminal);
		returned_terminals.push_back(non_terminal_dash);

	return  returned_terminals;
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