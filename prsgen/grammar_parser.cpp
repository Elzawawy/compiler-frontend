//
// Created by zawawy on 4/21/20.
//
#include <iostream>
#include "grammar_parser.h"
#include <algorithm>    // std::transform

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

void GrammarParser::eliminateLeftFactoring()
{
    //TODO: PRSGEN-4
}

template<typename T>
std::vector<T*> convertFrom(std::vector<T>& source)
{
    std::vector<T*> target(source.size());
    std::transform(source.begin(), source.end(), target.begin(), [](T& t) { return &t; });
    return target;
}

void GrammarParser::eliminateLeftRecursion(std::vector<NonTerminal> non_terminal_list)
{
    std::vector<NonTerminal*> non_terminal_list_p = convertFrom(non_terminal_list);

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
            new_non_terminal_list.push_back(*non_terminal_list_p.begin()+i);
        }
    }
    non_terminals_.clear();
    non_terminals_.reserve(non_terminal_list_p.size());

    for (int j = 0; j<new_non_terminal_list.size(); j++) {
        non_terminals_.push_back(**(new_non_terminal_list.begin()+j));

    }

}
