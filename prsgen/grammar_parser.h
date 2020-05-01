//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_GRAMMAR_PARSER_H
#define PRSGEN_GRAMMAR_PARSER_H

#include <set>
#include "non_terminal.h"
class GrammarParser {

private:
    std::set<std::string> terminals_;
    std::vector<NonTerminal> non_terminals_;
	std::vector<NonTerminal> after_left_recursion_;
public:
    const std::set<std::string>& getTerminals_() const;
    const std::vector<NonTerminal>& getNon_terminals_() const;
    void parseFile(std::string file_name);
    void eliminateLeftFactoring();
	void eliminateLeftRecursion();
	std::vector<NonTerminal *> eliminateImmediateLeftRecursion(NonTerminal* non_terminal);
	bool checkImmediateLeftRecursion(NonTerminal* non_terminal);
	std::vector<std::vector<std::string>> subsitution(NonTerminal* current_non_terminal, NonTerminal* input);

};

#endif //PRSGEN_GRAMMAR_PARSER_H
