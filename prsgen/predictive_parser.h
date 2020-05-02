#ifndef PRSGEN_PREDICTIVE_PARSER_H
#define PRSGEN_PREDICTIVE_PARSER_H

#include "../lexgen/lexical_analyzer_driver.h"
#include "non_terminal.h"
#include <vector>
#include <string>
#include <fstream>

class PredicativeParser {

private:
    std::stack<std::string> stack_;
    LexicalAnalyzerDriver &lexical_analyzer_;
    std::set<std::string> &terminals_;
    std::map<std::string, NonTerminal> non_terminals_;
    std::ofstream output_file_;

    void ProceedOnTerminal(std::string &stackTopEntry, Token *currentToken);

    void ProceedOnNonTerminal(std::string &stackTopEntry, Token *currentToken);

public:
    PredicativeParser(LexicalAnalyzerDriver &lexicalAnalyzer, std::map<std::string, NonTerminal> &nonTerminals,
                      std::set<std::string> &terminals, const std::string& outputFilePath);

    void Parse();

    virtual ~PredicativeParser();
};

#endif //PRSGEN_PREDICTIVE_PARSER_H
