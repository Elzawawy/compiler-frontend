//
// Created by omar_swidan on 27/03/20.
//

#ifndef LEXGEN_LEXICAL_ANALYZER_DRIVER_H
#define LEXGEN_LEXICAL_ANALYZER_DRIVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include "dfa_state.h"
#include "token.h"

using std::string;

class LexicalAnalyzerDriver {
 private:
  bool input_over_;
  const string input_file_name_;
  DFAState *root_state_;
  ifstream input_file_;
  const int buffer_size_ = 4096;
  vector<char> buffer_1_, buffer_2_;
  vector<char>::iterator forward_, lexeme_begin_;
  stack<pair<char, DFAState*>> states_;
  streamsize current_buffer_size_;
 public:
  LexicalAnalyzerDriver(DFAState *root_state_, const string &input_file_name_);
  Token *GetNextToken();
  bool IsInputOver();
  virtual ~LexicalAnalyzerDriver();
};

#endif //LEXGEN_LEXICAL_ANALYZER_DRIVER_H
