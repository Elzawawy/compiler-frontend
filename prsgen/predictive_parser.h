/**
    Compiler Phase 2: PRSGEN
    predictive_parser.cpp
    Purpose: The actual implementation of the parser flowchart itself that uses STACK, INPUT BUFFER and PARSING TABLE to parse the input program.

    @author(s) Mostafa Yousry
    @version 1.0
    @date 21/4/2020
*/

#ifndef PRSGEN_PREDICTIVE_PARSER_H
#define PRSGEN_PREDICTIVE_PARSER_H
#include "../lexgen/lexical_analyzer_driver.h"
#include "non_terminal.h"
#include <vector>
#include <string>
#include <fstream>

class PredicativeParser {
public:
    PredicativeParser(LexicalAnalyzerDriver& lexicalAnalyzer, std::vector<NonTerminal> non_terminals,
            std::unordered_set<std::string>& terminals, const std::string& outputFilePath);
    void Parse();
    virtual ~PredicativeParser();

private:
    std::stack<std::string> stack_;
    LexicalAnalyzerDriver& lexical_analyzer_;
    std::unordered_set<std::string>& terminals_;
    std::unordered_map<std::string, NonTerminal> non_terminals_;
    std::string starting_non_terminal_;
    std::ofstream output_file_;
    void ProceedOnTerminal(std::string& stack_top_entry, Token* current_token);
    void ProceedOnNonTerminal(std::string& stack_top_entry, Token* current_token);
    bool checkTerminalsAndRegularExpressions();
};
#endif //PRSGEN_PREDICTIVE_PARSER_H
