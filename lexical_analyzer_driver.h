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
  const int number_of_buffers_ = 2;
  vector<vector<char>> buffers_;
  vector<char>::iterator forward_, lexeme_begin_;
  stack<pair<char, DFAState*>> states_;
  int active_buffer_;
  void FillNextBuffer(int buffer_index_);

 public:
  LexicalAnalyzerDriver(DFAState *root_state_, const string &input_file_name_);
  Token *GetNextToken();
  bool IsInputOver();
  Token* GetTokenFromStatesStack();
  virtual ~LexicalAnalyzerDriver();
};

#endif //LEXGEN_LEXICAL_ANALYZER_DRIVER_H
