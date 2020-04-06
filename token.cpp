//
// Created by omar_swidan on 23/03/20.
//

#include "token.h"
Token::Token(const string lexeme_, const string token_name_) : lexeme_(lexeme_), token_name_(token_name_) {}
const string &Token::GetLexeme() const {
  return lexeme_;
}
const string &Token::GetTokenName() const {
  return token_name_;
}
