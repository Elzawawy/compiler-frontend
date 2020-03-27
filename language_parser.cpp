//
// Created by omar_swidan on 23/03/20.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "language_parser.h"

const std::vector<RegularExpression>& LanguageParser::getExpressions() const
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
}

std::string& trimBothEnds(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars)+1);
    str.erase(0, str.find_first_not_of(chars));
}

std::string& stripFirstAndLastChars(std::string& str)
{
    str.erase(0, 1);
    str.erase(str.length()-1, str.length()-1);
}

std::vector<std::string> splitOnDelimiter(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

void LanguageParser::parseRule(std::string rule)
{
    switch (rule[0]) {
    case '[': {
        stripFirstAndLastChars(rule);
        trimBothEnds(rule);
        std::vector<std::string> tokens = splitOnDelimiter(rule, ' ');
        break;
    }
    case '{': {
        stripFirstAndLastChars(rule);
        trimBothEnds(rule);
        std::vector<std::string> tokens = splitOnDelimiter(rule, ' ');
        break;
    }
    default:
        //handleRegularExpressionAndDefinition()
        break;
    }

}


