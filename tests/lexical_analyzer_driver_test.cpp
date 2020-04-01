#include "catch.h"
#include "../dfa_state.h"
#include "../lexical_analyzer_driver.h"
//TODO Use the Catch2 h file instead of the downloaded one

TEST_CASE("Lexical Analyzer Driver") {
  auto *root_state = new DFANormalState();
  auto *state_1 = new DFAAcceptanceState();
  auto *state_2 = new DFANormalState();
  auto *state_3 = new DFAAcceptanceState();
  auto *state_4 = new DFAAcceptanceState();
  auto *state_5 = new DFAAcceptanceState();
  auto *state_6 = new DFADeadState();

  root_state->AddNeighbour("a", state_1);
  root_state->AddNeighbour("b", state_5);
  state_1->AddNeighbour("a", state_2);
  state_1->AddNeighbour("b", state_3);
  state_2->AddNeighbour("a", state_2);
  state_2->AddNeighbour("b", state_5);
  state_3->AddNeighbour("b", state_4);
  state_3->AddNeighbour("a", state_6); //Go to dead state
  state_4->AddNeighbour("b", state_5);
  state_4->AddNeighbour("a", state_6); //Go to dead state
  state_5->AddNeighbour("b", state_5);
  state_5->AddNeighbour("a", state_6); //Go to dead state

  SECTION("Reaching a dead State One Get Token Only") {
    ofstream output_file("../input", ios::out);
    output_file << "abba";
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == "abb");
  }SECTION("Input Over One Get Token Only") {
    ofstream output_file("../input", ios::out);
    output_file << "abb";
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == "abb");
  }SECTION("2 Get Tokens With 2 Dead States At The End") {
    ofstream output_file("../input", ios::out);
    output_file << "abbaab";
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    Token *token2 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == "abb");
    REQUIRE(token2->GetLexeme_() == "aab");
  }SECTION("2 Get Tokens With 1 Dead State and 1 Input Over At The End") {
    ofstream output_file("../input", ios::out);
    output_file << "abbaab";
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    Token *token2 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == "abb");
    REQUIRE(token2->GetLexeme_() == "aab");
  }SECTION("2 Get Tokens With 2 Dead State At The End") {
    ofstream output_file("../input", ios::out);
    output_file << "abbaaba";
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    Token *token2 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == "abb");
    REQUIRE(token2->GetLexeme_() == "aab");
  }SECTION("Simulating 2 full buffers with 1 token") {
    ofstream output_file("../input", ios::out);
    string out1, out2;
    out1 += "a";
    for (int i = 0; i < 8191; ++i) {
      out1 += "b";
    }
    output_file << out1;
    output_file.close();
    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == out1);

  }SECTION(
      "Simulating 2 full buffers with 2 tokens, the second token has its first element as the ast element in the first buffer") {
    ofstream output_file("../input", ios::out);
    string out1, out2;
    out1 += "a";
    for (int i = 0; i < 4094; ++i) {
      out1 += "b";
    }
    out1 += 'a';
    output_file << out1;
    for (int i = 0; i < 4096; ++i) {
      out2 += "b";
    }
    output_file << out2;
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();
    Token *token2 = lexicalAnalyzerDriver.GetNextToken();
    REQUIRE(token1->GetLexeme_() == out1.substr(0, 4095));
    REQUIRE(token2->GetLexeme_() == (out1[4095] + out2));

  }SECTION("1 full buffer no dead state") {
    ofstream output_file("../input", ios::out);
    string out1;
    for (int i = 0; i < 4096; ++i) {
      out1 += "b";
    }
    output_file << out1;
    output_file.close();

    LexicalAnalyzerDriver lexicalAnalyzerDriver(root_state, "../input");
    Token *token1 = lexicalAnalyzerDriver.GetNextToken();

    REQUIRE(token1->GetLexeme_() == out1);
  }

}