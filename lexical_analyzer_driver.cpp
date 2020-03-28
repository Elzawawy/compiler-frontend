//
// Created by omar_swidan on 27/03/20.
//

#include "lexical_analyzer_driver.h"
bool LexicalAnalyzerDriver::IsInputOver() {
  return this->input_over_;
}
LexicalAnalyzerDriver::LexicalAnalyzerDriver( DFAState *root_state_, const string &input_file_name_) :
    root_state_(root_state_), input_file_name_(input_file_name_), buffer_1_(this->buffer_size_ + 1, 0),
    buffer_2_(this->buffer_size_ + 1, 0) {

  input_file_.open(input_file_name_, ifstream::binary);
  cout<<input_file_.good()<<endl;
  this->forward_ = this->buffer_1_.begin();

  this->input_file_.read(this->buffer_1_.data(), this->buffer_size_);
  this->current_buffer_size_ = ((this->input_file_) ? this->buffer_size_ : this->input_file_.gcount());


  this->lexeme_begin_ = this->buffer_2_.begin();
  this->states_.push(make_pair('L',this->root_state_));
}

