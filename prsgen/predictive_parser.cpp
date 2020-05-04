#include "predictive_parser.h"
#include <utility>
#include <numeric>
#include <algorithm>

const std::string END_MARKER = "$";
const std::string EPSILON = "\\L";
const int SYNC_INDEX = -1;
const int EMPTY_CELL_INDEX = -2;

PredicativeParser::PredicativeParser(LexicalAnalyzerDriver &lexicalAnalyzerDriver,
                                     std::unordered_map<std::string, NonTerminal> &nonTerminals, // map of name and object non terminals
                                     std::unordered_set<std::string> &terminals,
                                     const std::string &outputFilePath) :
        lexical_analyzer_{lexicalAnalyzerDriver},
        non_terminals_{std::move(nonTerminals)},
        terminals_{terminals} {
    output_file_.open(outputFilePath);
}

void PredicativeParser::Parse() {
    if (checkTerminalsAndRegularExpressions()) {
        // Push the end marker "$" and start non terminal to the stack
        stack_.push(END_MARKER);
        stack_.push("METHOD_BODY");

        // Call first token from lexical analyzer
        Token *currentToken = lexical_analyzer_.GetNextToken();
        std::string stackTopEntry = stack_.top();
        while (stack_.top() != END_MARKER) {
            // If the top of stack is a terminal
            if (terminals_.find(stackTopEntry) != terminals_.end()) {
                ProceedOnTerminal(stackTopEntry, currentToken);
            }
                // If the top of stack is a non-terminal
            else {
                ProceedOnNonTerminal(stackTopEntry, currentToken);
            }
        }
        // Check if there is still tokens in the input buffer (driver.getNextToken)
        if (currentToken->GetTokenName() != END_MARKER) {
            output_file_ << "Parsing ended while there is still tokens" << endl;
        }
        delete currentToken;
    } else {
        output_file_ << "Terminals in grammar rules and regular expressions in lexical rules don't match" << endl;
    }
    output_file_.close();
}

void PredicativeParser::ProceedOnTerminal(string &stackTopEntry, Token *currentToken) {
    // If the terminal matches the current token
    if (stackTopEntry == currentToken->GetTokenName()) {
        // Output matching message in output file
        output_file_ << "Match " << stackTopEntry << endl;
        // Pop the top entry of the stack
        stack_.pop();
        stackTopEntry = stack_.top();
        // Call for the next token from lexical analyzer
        if (lexical_analyzer_.IsInputOver()){
            *currentToken = Token("$", "$");
        } else{
            *currentToken = *lexical_analyzer_.GetNextToken();
        }
    }
        // If the terminal doesn't match the current token
    else {
        // Output missing token error message in output file
        output_file_ << "Error, missing " << stackTopEntry << endl;
        // Pop the top entry of the stack
        stack_.pop();
        stackTopEntry = stack_.top();
    }
}

void PredicativeParser::ProceedOnNonTerminal(string &stackTopEntry, Token *currentToken) {
    NonTerminal nonTerminal = non_terminals_.at(stackTopEntry);
    int productionRuleIndex = nonTerminal.GetProductionRuleIndex(currentToken->GetTokenName());
    switch (productionRuleIndex) {
        case SYNC_INDEX: // If there is a synchronizing token
            // Output illegal non terminal error message in output file and call next token from lexical analyzer
            output_file_ << "illegal " << stackTopEntry << endl;
            stack_.pop();
            stackTopEntry = stack_.top();
            break;
        case EMPTY_CELL_INDEX: // If there isn't a production rule under the token (empty cell)
            // Output illegal non terminal error message in output file and call next token from lexical analyzer
            output_file_ << "illegal " << stackTopEntry << endl;
            if (lexical_analyzer_.IsInputOver()){
                *currentToken = Token("$", "$");
            } else{
                *currentToken = *lexical_analyzer_.GetNextToken();
            }
            break;
        default: // If there is a production rule under the token
            std::vector<std::string> productionRule = nonTerminal.GetProductionRule(productionRuleIndex);
            std::string productionRuleString = std::accumulate(productionRule.begin(),
                                                               productionRule.end(), std::string(""));
            output_file_ << productionRuleString << endl;
            stack_.pop();
            if (productionRuleString != EPSILON) {
                for (auto iterator = productionRule.rbegin(); iterator != productionRule.rend(); ++iterator) {
                    stack_.push(*iterator);
                }
            }
            stackTopEntry = stack_.top();
    }
}

PredicativeParser::~PredicativeParser() {
    output_file_.close();
}

bool PredicativeParser::checkTerminalsAndRegularExpressions() {
    std::set<std::string> difference;
    std::set<std::string> regular_expressions_names = lexical_analyzer_.GetRegularExpressionsNames();
    std::set_difference(terminals_.begin(), terminals_.end(), regular_expressions_names.begin(),
                        regular_expressions_names.end(),
                        std::inserter(difference, difference.end()));

    return !difference.empty();
}
