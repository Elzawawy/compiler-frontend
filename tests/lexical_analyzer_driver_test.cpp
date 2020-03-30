#include <catch2/catch.hpp>
#include "../dfa_state.h"
#include "../lexical_analyzer_driver.h"

TEST_CASE( "Lexical Analyzer Driver Ending With No More Input" ) {
  DFAState* root_state = new DFAState(false);
  DFAState* state_1 = new DFAState(true);
  DFAState* state_2 = new DFAState(false);
  DFAState* state_3 = new DFAState(true);
  DFAState* state_4 = new DFAState(true);
  DFAState* state_5 = new DFAState(true);
  DFAState* state_6 = new DFAState(false);

  root_state->add_neighbour("a", state_1);
  root_state->add_neighbour("b", state_5);
  state_1->add_neighbour("a", state_2);
  state_1->add_neighbour("b", state_3);
  state_2->add_neighbour("a", state_2);
  state_2->add_neighbour("b", state_5);
  state_3->add_neighbour("b", state_4);
  state_4->add_neighbour("b", state_5);
  state_4->add_neighbour("a", state_6);
  state_5->add_neighbour("b", state_5);

  state_6->SetDeadState(true);



  LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
  Token* token1 = lexicalAnalyzerDriver.GetNextToken();
  if (token1)
    REQUIRE( token1->GetLexeme_() == "abb" );

}