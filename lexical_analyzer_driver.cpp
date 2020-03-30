
#include "lexical_analyzer_driver.h"
#include <algorithm>

bool LexicalAnalyzerDriver::IsInputOver() {
  return this->input_over_;
}
LexicalAnalyzerDriver::LexicalAnalyzerDriver(DFAState *root_state_, const string &input_file_name_) :
    root_state_(root_state_), input_over_(false), input_file_name_(input_file_name_),
    buffers_((unsigned long) this->number_of_buffers_, vector<char>(this->buffer_size_ + 1, 0)) {

  input_file_.open(input_file_name_, ifstream::binary);
  this->forward_ = this->buffers_[0].begin();
  this->active_buffer_ = 1;
  this->input_file_.read(this->buffers_[0].data(), this->buffer_size_);
  //We get the read number of bytes. We don't need to set the last byte with 0 here as it's all initialized with zeros but below we should as data circulates
  this->active_buffer_size_ = ((this->input_file_) ? this->buffer_size_ : this->input_file_.gcount());
  //This char is dummy as it's skipped when returning the lexeme as the root state has no character transitioner
  const char dummy_initial_transition_char = 'L';
  this->characters_states_.push(make_pair(dummy_initial_transition_char, this->root_state_));
}

//The caller has to check if no more input is present by calling IsInputOver method
//The caller is the parser.
//TAKE CARE this function assumes that a lexeme is strictly smaller than the size of a single buffer so make sure the buffer size is large enough
Token *LexicalAnalyzerDriver::GetNextToken() {
  //start with setting lexeme_begin with forward in order to satrt a new lexeme
  this->lexeme_begin_ = this->forward_;
  while (true) {
    //Skippable characters are handled in the forward pointer transition functions but this check is for the first ever character
    if (this->IsSkippableCharacter(*this->forward_)) {
      this->IncreaseForwardPointer();
    }

    if (this->input_over_) return nullptr;

    //if dead state then pop until finding an accepting state else return error
    //if the char now is 0 then the buffer isn't fully filled and that means the input is finished not at the end of the buffer
    if (characters_states_.top().second->IsDeadState() || *this->forward_ == 0) {
      for (int i = 0; i < this->characters_states_.size(); ++i) {
        if (this->characters_states_.top().second->isAccepting_state()) {
          //The next pair with the next char in the sequence and the neighbour of this accepting state by using the next char
          DFAState *next_state = this->characters_states_.top().second->GetNeighbour(*this->forward_);
          Token *token = this->GetTokenFromStatesStack();
          if (next_state == nullptr) {
            this->input_over_ = true;
            return token;
          }
          this->IncreaseForwardPointer();
          //Push the state after the accepting state onto the stack in order to be used in the next call of GetNextToken
          this->characters_states_.push(make_pair(*this->forward_, next_state));
          return token;
        }

        this->characters_states_.pop();
        //After calling decrease pointer if there's an error, then there's no accepting state as we reached lexeme_begin without finding one
        if (!this->DecreaseForwardPointer()) return nullptr;
      }
    }

    //Push the neighbour onto the stack transitioned wth the current character forward points to
    this->characters_states_.push(make_pair(*this->forward_,
                                            this->characters_states_.top().second->GetNeighbour(*this->forward_)));

    this->IncreaseForwardPointer();
  }

}

Token *LexicalAnalyzerDriver::GetTokenFromStatesStack() {
  //Here the strings are created on the stack as they're copied into the  constructor of token
  string lexeme;
  string token_name = this->characters_states_.top().second->GetTokenName();
  int charcaters_states_size_ = this->characters_states_.size();
  for (int i = 0; i < charcaters_states_size_; ++i) {
    if (this->characters_states_.top().second == this->root_state_) continue;
    //Append the character that transited the current DFAState
    lexeme += this->characters_states_.top().first;
    this->characters_states_.pop();
  }
  reverse(lexeme.begin(), lexeme.end());
  return new Token(lexeme, token_name);
}

void LexicalAnalyzerDriver::IncreaseForwardPointer() {
  //Reading the buffers. Fill next buffer if reached the end of the current buffer
  if (this->forward_ == this->buffers_[this->active_buffer_].end() - 1) {
    this->active_buffer_ = (this->active_buffer_ + 1) % this->number_of_buffers_;
    this->input_file_.read(this->buffers_[this->active_buffer_].data(), this->buffer_size_);
    this->forward_ = this->buffers_[this->active_buffer_].begin();
    this->input_over_ = !this->input_file_.good();
    this->active_buffer_size_ = ((this->input_file_) ? this->buffer_size_ : this->input_file_.gcount());
    //Set the last character in the buffer to \0 in order to indicate the end of the input
    //Take care that this is needed asa this is a  circular buffer.
    //Each buffer is filled with initialized with buffer size + 1 that's why we add the \0 index active buffer size
    this->buffers_[this->active_buffer_][this->active_buffer_size_] = 0;
  } else this->forward_++;

  //recursively forward pointer untill reaching a non skippable character
  if (this->IsSkippableCharacter(*this->forward_)) return this->IncreaseForwardPointer();
}
bool LexicalAnalyzerDriver::DecreaseForwardPointer() {
  if (this->forward_ == this->lexeme_begin_) return false;

  //Jump to the previous buffer if at the beginning of the current buffer the mod handles the circulation in the buffer
  if (this->forward_ == this->buffers_[this->active_buffer_].begin()) {
    this->active_buffer_ = (this->active_buffer_ - 1) % this->number_of_buffers_;
    this->forward_ = this->buffers_[this->active_buffer_].end() - 1;
  }

  this->forward_--;
  if (IsSkippableCharacter(*this->forward_)) return this->DecreaseForwardPointer();
  return true;
}

LexicalAnalyzerDriver::~LexicalAnalyzerDriver() {
  this->input_file_.close();
}
bool LexicalAnalyzerDriver::IsSkippableCharacter(char c) const {
  return c == '\n' || c == ' ' || c == '\t';
}

