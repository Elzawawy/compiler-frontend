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

//The caller has to check if no more input is present by calling IsInputOver method
//The caller is the parser.
Token *LexicalAnalyzerDriver::GetNextToken() {
  //start with setting lexeme_begin with forward in order to satrt a new lexeme
  this->lexeme_begin_ = this->forward_;

  //Reading the buffers. Can be done more neatly. Refactor in the end.
  if (this->forward_ == this->buffer_1_.end()) {
    this->input_file_.read(this->buffer_2_.data(), this->buffer_size_);
    this->forward_ = this->buffer_2_.begin();
    this->current_buffer_size_ = ((this->input_file_) ? this->buffer_size_ : this->input_file_.gcount());
    this->input_over_ = !this->input_file_.good();
  } else if (this->forward_ == this->buffer_2_.end()) {
    this->input_file_.read(this->buffer_1_.data(), this->buffer_size_);
    this->forward_ = this->buffer_2_.begin();
    this->current_buffer_size_ = ((this->input_file_) ? this->buffer_size_ : this->input_file_.gcount());
    this->input_over_ = !this->input_file_.good();
  }
  if (this->input_over_) return nullptr;
  DFAState* neighbour = this->states_.top().second->GetNeighbour(*this->forward_);
  if (neighbour->isAccepting_state()) {
    return
  }




  return nullptr;
}
LexicalAnalyzerDriver::~LexicalAnalyzerDriver() {
  this->input_file_.close();
}
