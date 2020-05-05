/**
    Compiler Phase 2: PRSGEN
    predictive_parser.cpp
    Purpose: The actual implementation of the parser flowchart itself that uses STACK, INPUT BUFFER and PARSING TABLE to parse the input program.

    @author(s) Mostafa Yousry
    @version 1.0
    @date 21/4/2020
*/

#include "predictive_parser.h"
#include <utility>
#include <numeric>
#include <algorithm>
#include <iterator>
#define END_MARKER  "$"
#define EPSILON  "\\L"
#define SYNCH_INDEX  -1
#define EMPTY_CELL_INDEX -2

PredicativeParser::PredicativeParser(LexicalAnalyzerDriver& lexicalAnalyzerDriver,
        std::vector<NonTerminal> non_terminals, // map of name and object non terminals
        std::unordered_set<std::string>& terminals,
        const std::string& outputFilePath)
        :lexical_analyzer_{lexicalAnalyzerDriver},
         terminals_{terminals}
{
    starting_non_terminal_ = non_terminals.at(0).getName_();
    for (auto&& non_terminal: non_terminals) {
        non_terminals_.insert({non_terminal.getName_(), non_terminal});
    }
    output_file_.open(outputFilePath);
}

void PredicativeParser::Parse()
{
    if (checkTerminalsAndRegularExpressions()) {
        // Push the end marker "$" and start non terminal to the stack
        stack_.push(END_MARKER);
        stack_.push(starting_non_terminal_);

        // Call first token from lexical analyzer
        Token* current_token = lexical_analyzer_.GetNextToken();
        std::string stack_top_entry = stack_.top();
        while (stack_.top()!=END_MARKER) {
            // If the top of stack is a terminal
            if (terminals_.find(stack_top_entry)!=terminals_.end()) {
                ProceedOnTerminal(stack_top_entry, current_token);
            }
                // If the top of stack is a non-terminal
            else {
                ProceedOnNonTerminal(stack_top_entry, current_token);
            }
        }
        // Check if there is still tokens in the input buffer (driver.getNextToken)
        if (current_token->GetTokenName()!=END_MARKER) {
            output_file_ << "Parsing ended while there are still tokens" << endl;
        }
        delete current_token;
    }
    else {
        output_file_ << "Terminals in grammar rules and regular expressions in lexical rules don't match" << endl;
    }
    output_file_.close();
}

void PredicativeParser::ProceedOnTerminal(string& stack_top_entry, Token* current_token)
{
    // If the terminal matches the current token
    if (stack_top_entry==current_token->GetTokenName()) {
        // Output matching message in output file
        output_file_ << "Match " << stack_top_entry << endl;
        // Pop the top entry of the stack
        stack_.pop();
        stack_top_entry = stack_.top();
        // Call for the next token from lexical analyzer
        if (lexical_analyzer_.IsInputOver()) {
            *current_token = Token("$", "$");
        }
        else {
            *current_token = *lexical_analyzer_.GetNextToken();
        }
    }
        // If the terminal doesn't match the current token
    else {
        // Output missing token error message in output file
        output_file_ << "Error, missing " << stack_top_entry << endl;
        // Pop the top entry of the stack
        stack_.pop();
        stack_top_entry = stack_.top();
    }
}

void PredicativeParser::ProceedOnNonTerminal(string& stack_top_entry, Token* current_token)
{
    NonTerminal non_terminal = non_terminals_.at(stack_top_entry);
    int production_rule_index = non_terminal.GetProductionRuleIndex(current_token->GetTokenName());
    switch (production_rule_index) {
    case SYNCH_INDEX: // If there is a synchronizing token
        // Output illegal non terminal error message in output file and call next token from lexical analyzer
        output_file_ << "Illegal " << stack_top_entry << " Drop non terminal : " << stack_top_entry << endl;
        stack_.pop();
        stack_top_entry = stack_.top();
        break;
    case EMPTY_CELL_INDEX: // If there isn't a production rule under the token (empty cell)
        // Output illegal non terminal error message in output file and call next token from lexical analyzer
        output_file_ << "Illegal " << stack_top_entry << " Drop token : " << current_token->GetTokenName() << endl;
        if (lexical_analyzer_.IsInputOver()) {
            *current_token = Token("$", "$");
        }
        else {
            *current_token = *lexical_analyzer_.GetNextToken();
        }
        break;
    default: // If there is a production rule under the token
        std::vector<std::string> production_rule = non_terminal.GetProductionRule(production_rule_index);
        std::string production_rule_string = std::accumulate(production_rule.begin(), production_rule.end(),
                std::string(""),
                [](std::string& ss, std::string& s) {
                  return ss.empty() ? s : ss+" "+s;
                });

        output_file_ << stack_top_entry << " -> " << production_rule_string << endl;
        stack_.pop();
        if (production_rule_string!=EPSILON) {
            for (auto iterator = production_rule.rbegin(); iterator!=production_rule.rend(); ++iterator) {
                stack_.push(*iterator);
            }
        }
        stack_top_entry = stack_.top();
    }
}

bool PredicativeParser::checkTerminalsAndRegularExpressions()
{
    std::set<std::string> difference;
    std::set<std::string> regular_expressions_names = lexical_analyzer_.GetRegularExpressionsNames();
    std::set_difference(terminals_.begin(), terminals_.end(), regular_expressions_names.begin(),
            regular_expressions_names.end(),
            std::inserter(difference, difference.end()));

    return !difference.empty();
}

PredicativeParser::~PredicativeParser()
{
    output_file_.close();
}