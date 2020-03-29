//
// Created by omar_swidan on 27/03/20.
//

#include "lexical_analyzer_driver.h"
#include <algorithm>

bool LexicalAnalyzerDriver::IsInputOver() {
  return this->input_over_;
}
LexicalAnalyzerDriver::LexicalAnalyzerDriver(DFAState *root_state_, const string &input_file_name_) :
    root_state_(root_state_), input_file_name_(input_file_name_),
    buffers_((unsigned long) this->number_of_buffers_, vector<char>(this->buffer_size_+1, 0)) {

  input_file_.open(input_file_name_, ifstream::binary);
  this->forward_ = this->buffers_[0].begin();
  this->active_buffer_ = 1;
  this->input_file_.read(this->buffers_[0].data(), this->buffer_size_);

  this->states_.push(make_pair('L', this->root_state_));
}

//The caller has to check if no more input is present by calling IsInputOver method
//The caller is the parser.
Token *LexicalAnalyzerDriver::GetNextToken() {
  //start with setting lexeme_begin with forward in order to satrt a new lexeme
  this->lexeme_begin_ = this->forward_;

  while (true) {
    //Reading the buffers. Can be done more neatly. Refactor in the end.
    //If the buffer is at the end then fill the next buffer but take care that the buffer is 1 + buffer size
    if (this->forward_ == this->buffers_[this->active_buffer_].end()) {
      this->FillNextBuffer(++this->active_buffer_);
    }

    //if the char now is 0 then the buffer isn't fully filled and that means the input is finished without
    //finding an accepting state.
    //TODO check if this ever happens as the last state before this iteration would probably be a dead state that forces a return
    if (*this->forward_ == 0) return nullptr;

    if (this->input_over_) return nullptr;

    DFAState *neighbour = this->states_.top().second->GetNeighbour(*this->forward_);

    //Push the neighbour onto the stack
    this->states_.push(make_pair(*this->forward_, neighbour));

    //return the lexeme found with the token name stored in the dfa state
    if (neighbour->isAccepting_state()) {
      Token* token = this->GetTokenFromStatesStack();
      //Getting the lexeme from stack requires popping all the elements of the stack
      //The last state found has to be pushed again onto the stack to be used in the next call of GetNextToken
      this->states_.push(make_pair(*this->forward_, neighbour));
      return token;
    }

    //if dead state then pop until finding an accepting state else return error
    if (neighbour->IsDeadState()) {
      for (int i = 0; i < this->states_.size(); ++i) {
        if (this->states_.top().second->isAccepting_state()) {
          return this->GetTokenFromStatesStack();
        }
        this->states_.pop();
      }
    }
    this->forward_++;
  }

}

Token *LexicalAnalyzerDriver::GetTokenFromStatesStack() {
  //TODO push the last state onto the stack again at the end
  //Here the strings are created on the stack as they're copied into the  constructor of token
  string lexeme;
  string token_name = this->states_.top().second->GetTokenName();
  for (int i = 0; i < this->states_.size(); ++i) {
    //Append the character that transited the current DFAState
    lexeme += this->states_.top().first;
    this->states_.pop();
  }
  reverse(lexeme.begin(), lexeme.end());
  return new Token(lexeme, token_name);
}
void LexicalAnalyzerDriver::FillNextBuffer(int buffer_index) {
  this->input_file_.read(this->buffers_[buffer_index].data(), this->buffer_size_);
  this->forward_ = this->buffers_[buffer_index].begin();
  this->input_over_ = !this->input_file_.good();

}

LexicalAnalyzerDriver::~LexicalAnalyzerDriver() {
  this->input_file_.close();
}
