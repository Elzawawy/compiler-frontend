//
// Created by zawawy on 4/21/20.
//

#ifndef PRSGEN_PREDICTIVE_PARSER_H
#define PRSGEN_PREDICTIVE_PARSER_H

#include "../lexgen/lexical_analyzer_driver.h"
#include "non_terminal.h"
#include <vector>
#include <string>

class PredicativeParser {

private:
    std::stack<std::string> stack_;
    LexicalAnalyzerDriver &lexical_analyzer_;
    std::set<std::string> &terminals_;
    std::map<std::string, NonTerminal> non_terminals_;


public:
    //TODO: PRSGEN-8
    PredicativeParser(LexicalAnalyzerDriver &lexicalAnalyzer, std::map<std::string, NonTerminal> &nonTerminals,
                      std::set<std::string> &terminals);

    void Parse();
};

#endif //PRSGEN_PREDICTIVE_PARSER_H
