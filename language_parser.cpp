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
//    for (auto& expression: expressions_)
//        std::cout << expression.getName() << " " << expression.getValue() << std::endl;

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
template<class T>
bool comparePairsAccordingToFirstLength(const std::pair<T, T>& a,
        const std::pair<T, T>& b)
{
    return a.first.length()>b.first.length();
}

template<class T>
void insertInSetIfNotExists(std::unordered_set<T>& set, T element)
{
    if (set.count(element)==0)
        set.insert(element);
}

void LanguageParser::parseRule(std::string rule)
{
    if (rule[0]==KEYWORD_INDICATOR or rule[0]==PUNCTUATION_INDICATOR) {
        std::string regex_name = (rule[0]==KEYWORD_INDICATOR) ? KEYWORD : PUNCTUATION;
        stripFirstAndLastChars(rule);
        trimBothEnds(rule);
        std::vector<std::string> tokens = splitOnDelimiter(rule, ' ');
        for (auto& regex_value: tokens) {
            expressions_.emplace_back(regex_name, regex_value);
            if (regex_name==KEYWORD)
                for (auto& character: regex_value)
                    insertInSetIfNotExists(input_table_, std::string(1, character));
            else
                insertInSetIfNotExists(input_table_, regex_value);
        }
    }
    else {
        rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
        ul found = rule.find_first_of(REGULAR_EXP_SPLITTER);
        std::sort(definitions_.begin(), definitions_.end(), comparePairsAccordingToFirstLength<std::string>);
        for (auto& definition: definitions_) {
            ul definition_pos = rule.find(definition.first, found+1);
            while (definition_pos!=std::string::npos) {
                rule.replace(definition_pos, definition.first.length(), "("+definition.second+")");
                definition_pos = rule.find(definition.first, found+1);
            }
        }

        for (int i = 0; i<rule.length(); i++){
            if(rule[i] == '-' and rule[i-1] != '\\'){
                std::string replacement_string;
                for (char j = rule[i-1]; j<=rule[i+1]; j++) {
                    if(j == rule[i-1])
                        replacement_string += {'(',j, '|'};
                    else if(j == rule[i+1])
                        replacement_string += {j, ')'};
                    else
                        replacement_string += {j, '|'};
                }
                rule.replace(static_cast<unsigned long>(i-1),3,replacement_string);
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
                    insertInSetIfNotExists(input_table_, {'\\', regex_value[++i]});
                else if (regex_value[i]=='-')
                    for (int j = regex_value[i-1]; j<regex_value[i+1]; j++)
                        insertInSetIfNotExists(input_table_, std::string(1, j));
                else
                    insertInSetIfNotExists(input_table_, std::string(1, regex_value[i]));

            expressions_.emplace_back(regex_name, regex_value);
        }
        else
            definitions_.emplace_back(regex_name, regex_value);
    }
}