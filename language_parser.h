//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_LANGUAGE_PARSER_H
#define LEXGEN_LANGUAGE_PARSER_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>

typedef struct regular_definition {
  std::string name;
  std::string value;
} regular_definition;

typedef struct regular_expression {
  std::string name;
  std::string value;
} regular_expression;

class LanguageParser {

 public:
  void parse(std::string file_path);
  const std::vector<std::string> &getInput_table() const;
  const std::vector<regular_expression> &getExpressions() const;

 private:
  std::vector<std::string> input_table;
  std::vector<regular_expression> expressions;
  std::vector<regular_definition> definitions;
};

#endif //LEXGEN_LANGUAGE_PARSER_H
