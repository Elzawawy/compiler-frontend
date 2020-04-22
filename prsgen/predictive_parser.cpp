//
// Created by zawawy on 4/21/20.
//

#include "predictive_parser.h"
#include <utility>
#include <numeric>

const std::string END_MARKER = "$";

PredicativeParser::PredicativeParser(LexicalAnalyzerDriver &lexicalAnalyzerDriver,
                                     std::map<std::string, NonTerminal> &nonTerminals, // map of name and object non terminals
                                     std::set<std::string> &terminals) :
        lexical_analyzer_{lexicalAnalyzerDriver},
        non_terminals_{std::move(nonTerminals)},
        terminals_{terminals} {
}

void PredicativeParser::Parse() {

    // Push the end marker "$" and start non terminal to the stack
    stack_.push(END_MARKER);
    stack_.push(non_terminals_.begin()->second.getName_());

    // Call first token from lexical analyzer
    Token *currentToken = lexical_analyzer_.GetNextToken();
    std::string stackTopEntry = stack_.top();
    while (stack_.top() != END_MARKER) {

        // If the top of stack is a terminal
        if (terminals_.find(stackTopEntry) != terminals_.end()) {

            // If the terminal matches the current token
            if (stackTopEntry == currentToken->GetTokenName()) {
                // Pop the top entry of the stack
                stack_.pop();
                stackTopEntry = stack_.top();
                // Call for the next token from lexical analyzer
                currentToken = lexical_analyzer_.GetNextToken();

                // Output matching message in output file
                //TODO: output matching message in output file
            }

                // If the terminal doesn't match the current token
            else {
                // Output non-matching error message in output file
                //TODO: output non-matching error message in output file

                // Skip current token and call for the next token from lexical analyzer
                currentToken = lexical_analyzer_.GetNextToken();
            }
        }

            // If the top of stack is a non-terminal
        else {
            NonTerminal nonTerminal = non_terminals_.at(stackTopEntry);

            // If there is a production rule of the non-terminal under the input token
            try {
                std::vector<std::string> productionRule = nonTerminal.GetProductionRule(currentToken->GetTokenName());
                //TODO: Check for the synchronizing token
                //TODO: Check for epsilon

                std::string productionRuleString = std::accumulate(productionRule.begin(), productionRule.end(),
                                                                   std::string(""));
                //TODO: output production rule in output file
                stack_.pop();
                for (auto iterator = productionRule.rbegin(); iterator != productionRule.rend(); ++iterator) {
                    stack_.push(*iterator);
                }
                stackTopEntry = stack_.top();
                // If there isn't a production rule of the non-terminal under the input token
            } catch (exception e) {
                // Output illegal non terminal error message in output file
                //TODO: output illegal non terminal error message in output file
            }

        }
    }

    // Check if there is still tokens in the input buffer (driver.getNextToken)
}
