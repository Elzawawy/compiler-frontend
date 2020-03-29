/**
    Compiler Phase 1: LEXGEN
    language_parser.h
    Purpose: Takes in a file of lexical rules (language definition) and parses into REs and input symbols.

    @author Amr Elzawawy
    @version 1.0
    @date 25/3/2020
*/

#ifndef LEXGEN_LANGUAGE_PARSER_H
#define LEXGEN_LANGUAGE_PARSER_H
#include <string>
#include <vector>
#include <unordered_set>
#include "regular_expression.h"


class LanguageParser {

public:
    void parseFile(std::string rules_file_path);
    const std::unordered_set<std::string>& getInput_table() const;
    const std::vector<RegularExpression>& getExpressions() const;

private:
    std::unordered_set<std::string> input_table_;
    std::vector<RegularExpression> expressions_;
    std::vector<std::pair<std::string,std::string>> definitions_;
    void keywordAndPunctuationHandler(std::string rule);
    void regularExpressionHandler(std::string rule);
};

#endif //LEXGEN_LANGUAGE_PARSER_H
