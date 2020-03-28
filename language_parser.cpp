//
// Created by omar_swidan on 23/03/20.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "language_parser.h"

#define KEYWORD_INDICATOR '{'
#define KEYWORD "Keyword"
#define PUNCTUATION_INDICATOR '['
#define PUNCTUATION "Punctuation"
#define REGULAR_EXP_SPLITTER ":="
#define REGULAR_EXP_INDICATOR ':'
typedef unsigned long ul;

const std::vector<regular_expression>& LanguageParser::getExpressions() const
{
    return expressions_;
}
const std::vector<std::string>& LanguageParser::getInput_table() const
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
//    for (auto& expression: expressions_)
//        std::cout << expression.getName() << " " << expression.getValue() << std::endl;
//
//    for (auto& expression: definitions_)
//        std::cout << expression.first << " " << expression.second << std::endl;
}

void trimBothEnds(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars)+1);
    str.erase(0, str.find_first_not_of(chars));
}

void stripFirstAndLastChars(std::string& str)
{
    str.erase(0, 1);
    str.erase(str.length()-1, str.length()-1);
}

std::vector<std::string> splitOnDelimiter(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}
bool comparePairsAccordingToFirstLength(const std::pair<std::string, std::string>& a,
        const std::pair<std::string, std::string>& b)
{
    return a.first.length()>b.first.length();
}

void LanguageParser::parseRule(std::string rule)
{
    if (rule[0]==KEYWORD_INDICATOR or rule[0]==PUNCTUATION_INDICATOR) {
        std::string regex_name = (rule[0]==KEYWORD_INDICATOR) ? KEYWORD : PUNCTUATION;
        stripFirstAndLastChars(rule);
        trimBothEnds(rule);
        std::vector<std::string> tokens = splitOnDelimiter(rule, ' ');
        for (auto& regex_value: tokens)
            expressions_.emplace_back(regex_name, regex_value);
    }
    else {
        rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
        ul found = rule.find_first_of(REGULAR_EXP_SPLITTER);
        std::sort(definitions_.begin(), definitions_.end(), comparePairsAccordingToFirstLength);
        for (auto& definition: definitions_) {
            ul definition_pos = rule.find(definition.first, found+1);
            while (definition_pos!=std::string::npos) {
                rule.replace(definition_pos, definition.first.length(), "("+definition.second+")");
                definition_pos = rule.find(definition.first, found+1);
            }
        }
        std::string regex_name = rule.substr(0, found);
        std::string regex_value = rule.substr(found+1);
        if (rule[found]==REGULAR_EXP_INDICATOR)
            expressions_.emplace_back(regex_name, regex_value);
        else
            definitions_.emplace_back(regex_name, regex_value);
    }
}