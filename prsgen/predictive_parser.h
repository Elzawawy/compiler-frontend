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
    std::unordered_set<std::string> &terminals_;
    std::unordered_map<std::string, NonTerminal> non_terminals_;
    std::string starting_non_terminal_;
    std::ofstream output_file_;

    void ProceedOnTerminal(std::string &stack_top_entry, Token *current_token);

    void ProceedOnNonTerminal(std::string &stack_top_entry, Token *current_token);

    bool checkTerminalsAndRegularExpressions();

public:
    PredicativeParser(LexicalAnalyzerDriver &lexicalAnalyzer, std::vector<NonTerminal> non_terminals,
                      std::unordered_set<std::string> &terminals, const std::string &outputFilePath);

    void Parse();

    virtual ~PredicativeParser();
};

#endif //PRSGEN_PREDICTIVE_PARSER_H
