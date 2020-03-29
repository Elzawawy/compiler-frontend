/**
    Compiler Phase 1: LEXGEN
    language_parser.cpp
    Purpose: Takes in a file of lexical rules (language definition) and parses into REs and input symbols.

    @author Amr Elzawawy
    @version 1.0
    @date 25/3/2020
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "language_parser.h"
#include "utils.h"

#define KEYWORD_INDICATOR '{'
#define KEYWORD_NAME "Keyword"
#define PUNCTUATION_INDICATOR '['
#define PUNCTUATION_NAME "Punctuation"
#define RULE_ASSIGN_INDICATOR ":="
#define REGULAR_EXP_INDICATOR ':'

typedef unsigned long ul;

const std::vector<RegularExpression>& LanguageParser::getExpressions() const
{
    return expressions_;
}
const std::unordered_set<std::string>& LanguageParser::getInput_table() const
{
    return input_table_;
}

/**
    Reads lexical rules from file path content, and calls appropriate handlers for each rule on the fly.
    @param rules_file_path The path for your lexical rules file.
*/
void LanguageParser::parseFile(std::string rules_file_path)
{
    std::ifstream file(rules_file_path);
    if (file.is_open()) {
        std::string rule;
        while (getline(file, rule))
            if (rule[0]==KEYWORD_INDICATOR or rule[0]==PUNCTUATION_INDICATOR)
                keywordAndPunctuationHandler(rule);
            else
                regularExpressionHandler(rule);
        file.close();
    }
}

/**
    Knows its way through the keywords and punctuations rules that exist in file and parses them into RE and Input Syms.
    @param rule The rule read from file as string.
*/
void LanguageParser::keywordAndPunctuationHandler(std::string rule)
{
    // set the name of the regex according to one of the two types in this handler.
    std::string regex_name = (rule[0]==KEYWORD_INDICATOR) ? KEYWORD_NAME : PUNCTUATION_NAME;
    // remove expression type indicators ([,],{,}) and trim rule.
    util::stripFirstAndLastChars(rule);
    util::trimBothEnds(rule);
    // for each keyword/punctuation in the array defined, lets make a regex and populate the input table with new symbols!
    for (auto& regex_value: util::splitOnDelimiter(rule, ' '))
        updateExpressionsAndInputTable(regex_name,regex_value);
}

/**
    Unlike his brother keyword handler, that RE handler knows his way through other types of rules and again parses them into REs and Input Syms.
    @param rule The rule read from file as string.
*/
void LanguageParser::regularExpressionHandler(std::string rule)
{
    // spaces are neglected and are optional by our definition of rules.
    util::removeAllSpaces(rule);
    // find ':' or '=' position and whomever appears first of them defines whether this is definition or expression.
    ul assign_pos = rule.find_first_of(RULE_ASSIGN_INDICATOR);
    for (auto& definition: definitions_) {
        // for each definition that exists inside this expression/definition we replace the definition name with its value.
        // we pass the second param (assign_pos+1) to reduce the search space for the function to start looking after assign.
        ul definition_pos = rule.find(definition.first, assign_pos+1);
        while (definition_pos!=std::string::npos) {
            rule.replace(definition_pos, definition.first.length(), "("+definition.second+")");
            definition_pos = rule.find(definition.first, assign_pos+1);
        }
    }
    // assign regex's name and value according to the assign indicator position
    std::string regex_name = rule.substr(0, assign_pos);
    std::string regex_value = rule.substr(assign_pos+1);
    // lets make a regex and populate the input table with new symbols!
    if (rule[assign_pos]==REGULAR_EXP_INDICATOR)
        updateExpressionsAndInputTable(regex_name,regex_value);
    else {
        definitions_.emplace_back(regex_name, regex_value);
        // sort the definitions according to the length of the name to avoid longer subsets of same names problem (e.g. digits overlap digit).
        std::sort(definitions_.begin(), definitions_.end(), util::comparePairsAccordingToFirstLength<std::string>);
    }
}
void LanguageParser::updateExpressionsAndInputTable(std::string regex_name, std::string regex_value)
{
    RegularExpression regex = RegularExpression(regex_name, regex_value);
    expressions_.push_back(regex);
    std::vector<std::string> symbols = regex.extractInputSymbols();
    std::copy(symbols.begin(), symbols.end(), std::inserter(input_table_, input_table_.end()));
}