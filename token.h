//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_TOKEN_H
#define LEXGEN_TOKEN_H
#include <string>
using std::string;

class Token {
 private:
  string lexeme_;
  string token_name_;
 public:
  const string &GetLexeme() const;
  const string &GetTokenName() const;
  Token(string lexeme_, string token_name_);
};


#endif //LEXGEN_TOKEN_H
