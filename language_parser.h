//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_LANGUAGE_PARSER_H
#define LEXGEN_LANGUAGE_PARSER_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>

typedef struct RegularDefinition {
  std::string name;
  std::string value;
} RegularDefinition;

typedef struct RegularExpression {
  std::string name;
  std::string value;
} RegularExpression;

class LanguageParser {

public:
    void parseFile(std::string rules_file_path);
    const std::vector<std::string>& getInput_table() const;
    const std::vector<RegularExpression>& getExpressions() const;

private:
    std::vector<std::string> input_table_;
    std::vector<RegularExpression> expressions_;
    std::vector<RegularDefinition> definitions_;
    void parseRule(std::string rule);
};

#endif //LEXGEN_LANGUAGE_PARSER_H
