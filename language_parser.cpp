//
// Created by omar_swidan on 23/03/20.
//

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
void LanguageParser::parseFile(std::string rules_file_path)
{
    std::ifstream file(rules_file_path);
    if (file.is_open()) {
        std::string rule;
        while (getline(file, rule))
            parseRule(rule);
        file.close();
    }
}
void LanguageParser::parseRule(std::string rule)
{
    if (rule[0]==KEYWORD_INDICATOR or rule[0]==PUNCTUATION_INDICATOR) {
        std::string regex_name = (rule[0]==KEYWORD_INDICATOR) ? KEYWORD_NAME : PUNCTUATION_NAME;
        util::stripFirstAndLastChars(rule);
        util::trimBothEnds(rule);
        std::vector<std::string> tokens = util::splitOnDelimiter(rule, ' ');
        for (auto& regex_value: tokens) {
            RegularExpression regex = RegularExpression(regex_name, regex_value);
            expressions_.push_back(regex);
            std::vector<std::string> symbols = regex.extractInputSymbols();
            std::copy(symbols.begin(), symbols.end(), std::inserter(input_table_, input_table_.end()));
        }
    }
    else {
        rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
        ul found = rule.find_first_of(RULE_ASSIGN_INDICATOR);
        std::sort(definitions_.begin(), definitions_.end(), util::comparePairsAccordingToFirstLength<std::string>);
        for (auto& definition: definitions_) {
            ul definition_pos = rule.find(definition.first, found+1);
            while (definition_pos!=std::string::npos) {
                rule.replace(definition_pos, definition.first.length(), "("+definition.second+")");
                definition_pos = rule.find(definition.first, found+1);
            }
        }
        std::string regex_name = rule.substr(0, found);
        std::string regex_value = rule.substr(found+1);
        if (rule[found]==REGULAR_EXP_INDICATOR) {
            RegularExpression regex = RegularExpression(regex_name, regex_value);
            regex.applyRangeOperationIfExists();
            expressions_.push_back(regex);
            std::vector<std::string> symbols = regex.extractInputSymbols();
            std::copy(symbols.begin(), symbols.end(), std::inserter(input_table_, input_table_.end()));
        }
        else
            definitions_.emplace_back(regex_name, regex_value);
    }
}