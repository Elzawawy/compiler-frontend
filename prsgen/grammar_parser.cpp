/**
    Compiler Phase 2: PRSGEN
    grammar_parser.cpp
    Purpose: Takes in a file of grammar rules (non-terminals definition) and parses into non-terminals, terminals and production rules.

    @author(s) Amr Elzawawy
    @version 1.0
    @date 24/4/2020
*/

#include <fstream>
#include <iostream>
#include <regex>
#include "grammar_parser.h"
#include "../utils.h"
#define NON_TERMINAL_SEPARATOR '#'
#define NON_TERMINAL_SIDES_SEPARATOR "::="
#define RULE_SIDES_NUMBER 2
#define LEFT_HAND_SIDE_INDEX 0
#define RIGHT_HAND_SIDE_INDEX 1
#define PRODUCTION_RULES_SEPARATOR '|'
#define PRODUCTION_RULE_TERMS_SEPARATOR ' '
#define TERMINAL_INDICATOR '\''
#define ESCAPE_CHARACTER '\\'
#define SPACE_STRING " "
#define isInvalidNonTerminal(term) !non_terminals_names_.count(term) and !terminals_.count(term) and term!=EPSILON_EXPRESSION
#define isEscapedTerminal(term) term[0]==ESCAPE_CHARACTER and term!=EPSILON_EXPRESSION
#define isWrongNonTerminalName(name) !std::regex_match(name, std::regex("^[A-Za-z0-9_`]+$"))

/******** Public Methods ********/
const std::unordered_set<std::string>& GrammarParser::getTerminals_() const
{
    return terminals_;
}
const std::vector<NonTerminal>& GrammarParser::getNon_terminals_() const
{
    return non_terminals_;
}

void GrammarParser::parseFile(std::string grammar_file_path)
{
    // run validation cases at the beginning and store non-terminals names for later validation.
    validateGrammarFile(grammar_file_path);
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            // guard against any empty lines detected.
            if (non_terminal_definition.empty()) continue;
            // get both sides of the non-terminal definition and operate on each.
            std::vector<std::string> definition_sides = util::splitOnStringDelimiter(non_terminal_definition,
                    NON_TERMINAL_SIDES_SEPARATOR);
            std::string right_hand_side = definition_sides[RIGHT_HAND_SIDE_INDEX];
            std::string left_hand_side = definition_sides[LEFT_HAND_SIDE_INDEX];
            util::trimBothEnds(left_hand_side);
            util::trimBothEnds(right_hand_side);
            NonTerminal non_terminal(left_hand_side);
            // extracts terminals from this non-terminal definition and inserts into private terminals set.
            extractTerminalsFromRHS(right_hand_side);
            // extracts production rules from this non-terminal definition and inserts into private non_terminal variable passed.
            extractProductionRulesFromRHS(right_hand_side, non_terminal);
            non_terminals_.push_back(non_terminal);
        }
        file.close();
    }
}

void GrammarParser::eliminateRightFactoring()
{
    //TODO: PRSGEN-3
}
void GrammarParser::eliminateLeftFactoring()
{
    //TODO: PRSGEN-4
}

/******** Private Methods ********/
void GrammarParser::validateGrammarFile(std::string grammar_file_path)
{
    std::ifstream file(grammar_file_path);
    if (file.is_open()) {
        std::string non_terminal_definition;
        while (std::getline(file, non_terminal_definition, NON_TERMINAL_SEPARATOR)) {
            // guard against any empty lines detected.
            if (non_terminal_definition.empty()) continue;
            // split sides of the non-terminal definition.
            std::vector<std::string> definition_sides = util::splitOnStringDelimiter(non_terminal_definition,
                    NON_TERMINAL_SIDES_SEPARATOR);
            // Validation Case 1: Missing rule sides separator.
            if (definition_sides.size()!=RULE_SIDES_NUMBER) {
                std::cerr << "Error found in grammar rules ! Missing `::=` on any rule."
                          << "Please re-check the input file format required."
                          << std::endl;
                std::exit(0);
            }
            util::trimBothEnds(definition_sides[LEFT_HAND_SIDE_INDEX]);
            //Validation Case 2: Wrong Non-Terminal Name
            if (isWrongNonTerminalName(definition_sides[LEFT_HAND_SIDE_INDEX])) {
                std::cerr << "Error found in grammar rules ! Wrong Non Terminal Name"
                          << "Please re-check the input file format required."
                          << std::endl;
                std::exit(0);
            }
            non_terminals_names_.insert(definition_sides[LEFT_HAND_SIDE_INDEX]);
        }
        file.close();
    }
}

void GrammarParser::extractTerminalsFromRHS(std::string& right_hand_side)
{
    for (unsigned long i = 0; i<right_hand_side.size(); i++) {
        std::string found_terminal;
        // terminal is found using the reserved single quote character `'`.
        if (right_hand_side[i]==TERMINAL_INDICATOR) {
            // place a string instead of the reserved character to split on spaces later on.
            right_hand_side.replace(i, 1, SPACE_STRING);
            // until the ending single quote is met keep traversing chars and accumulating the found terminal string.
            while (i<right_hand_side.size()
                    and (right_hand_side[++i]!=TERMINAL_INDICATOR or right_hand_side[i-1]==ESCAPE_CHARACTER)) {
                if (right_hand_side[i]==ESCAPE_CHARACTER) continue;
                found_terminal += right_hand_side[i];
            }
            right_hand_side.replace(i, 1, SPACE_STRING);
            // store the terminal found in the set of terminals that we extract into.
            terminals_.insert(found_terminal);
        }
    }
}

void GrammarParser::extractProductionRulesFromRHS(std::string& right_hand_side, NonTerminal& non_terminal)
{
    std::vector<ProductionRule> production_rules;
    std::string found_rule;
    for (unsigned long i = 0; i<right_hand_side.size(); i++) {
        // production rule is found by the reserved character `|`. Also make sure that it is not escaped.
        if (right_hand_side[i]==PRODUCTION_RULES_SEPARATOR and right_hand_side[i-1]!=ESCAPE_CHARACTER) {
            production_rules.push_back(getProductionRuleFromString(found_rule));
            found_rule.clear();
        }
        else
            found_rule += right_hand_side[i];
    }
    // add all the rules found into the production rules of the non terminal passed in.
    production_rules.push_back(getProductionRuleFromString(found_rule));
    non_terminal.setProduction_rules_(production_rules);
}

ProductionRule GrammarParser::getProductionRuleFromString(std::string& production_rule)
{
    util::trimBothEnds(production_rule);
    util::removeExtraSpaces(production_rule);
    // we split terms in the single on spaces so we have to remove all extra spaces in between before that.
    std::vector<std::string> rule_terms = util::splitOnDelimiter(production_rule, PRODUCTION_RULE_TERMS_SEPARATOR);
    for (auto& rule_term : rule_terms) {
        util::trimBothEnds(rule_term);
        // if this terminal is escaped character and NOT EPSILON, then we remove the backslash before insertion.
        if (isEscapedTerminal(rule_term))
            rule_term.erase(rule_term.begin());
        // Validation Case 3: if this is a non terminal that is used but not defined we raise and error and exit.
        if (isInvalidNonTerminal(rule_term)) {
            std::cerr << "Error found in grammar rules ! A non-terminal (" << rule_term
                      << ") was used but not defined. This maybe also because of wrong input file format required."
                      << std::endl;
            std::exit(0);
        }
    }
    return rule_terms;
}