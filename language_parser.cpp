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
#define KEYWORD "Keyword"
#define PUNCTUATION_INDICATOR '['
#define PUNCTUATION "Punctuation"
#define REGULAR_EXP_SPLITTER ":="
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
    for (auto& expression: expressions_)
        std::cout << expression.getName() << " " << expression.getValue() << std::endl;

//    for (auto& expression: definitions_)
//        std::cout << expression.first << " " << expression.second << std::endl;

//    for (auto& input: input_table_)
//        std::cout << input << std::endl;

//    std::vector<char> chars;
//    for (char j = '0'; j<'9'; j++)
//        chars.push_back(j);
//
//    for(auto& character: chars)
//        if(input_table_.count(std::string(1,character)) == 0)
//            std::cout<< false<<std::endl;

}

void LanguageParser::parseRule(std::string rule)
{
    if (rule[0]==KEYWORD_INDICATOR or rule[0]==PUNCTUATION_INDICATOR) {
        std::string regex_name = (rule[0]==KEYWORD_INDICATOR) ? KEYWORD : PUNCTUATION;
        util::stripFirstAndLastChars(rule);
        util::trimBothEnds(rule);
        std::vector<std::string> tokens = util::splitOnDelimiter(rule, ' ');
        for (auto& regex_value: tokens) {
            expressions_.emplace_back(regex_name, regex_value);
            if (regex_name==KEYWORD)
                for (auto& character: regex_value)
                    util::insertInSetIfNotExists(input_table_, std::string(1, character));
            else
                util::insertInSetIfNotExists(input_table_, regex_value);
        }
    }
    else {
        rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
        ul found = rule.find_first_of(REGULAR_EXP_SPLITTER);
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
            for (int i = 0; i<regex_value.length(); i++)
                if (regex_value[i]=='(' || regex_value[i]==')' || regex_value[i]=='*' || regex_value[i]=='+'
                        || regex_value[i]=='|')
                    continue;
                else if (regex_value[i]=='\\')
                    util::insertInSetIfNotExists(input_table_, {'\\', regex_value[++i]});
                else if (regex_value[i]=='-')
                    for (int j = regex_value[i-1]; j<regex_value[i+1]; j++)
                        util::insertInSetIfNotExists(input_table_, std::string(1, j));
                else
                    util::insertInSetIfNotExists(input_table_, std::string(1, regex_value[i]));

            RegularExpression regex = RegularExpression(regex_name, regex_value);
            regex.applyRangeOperationIfExists();
            expressions_.push_back(regex);
        }
        else
            definitions_.emplace_back(regex_name, regex_value);
    }
}