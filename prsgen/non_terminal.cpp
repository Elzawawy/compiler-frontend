/**
    Compiler Phase 2: PRSGEN
    non_terminal.cpp
    Purpose: the non terminal entity class that holds non terminal data.

    @author(s) Amr Elzawawy
    @version 1.0
    @date 21/4/2020
*/
#include "non_terminal.h"
#define EMPTY_CELL_INDEX  -2

NonTerminal::NonTerminal(const std::string &name_)
        : name_(name_) {}

const std::string &NonTerminal::getName_() const {
    return name_;
}

const std::unordered_set<std::string> &NonTerminal::getFirst_() const {
    return first_;
}

void NonTerminal::setFirst_(const std::unordered_set<std::string> &first_) {
    NonTerminal::first_ = first_;
}

const std::unordered_set<std::string> &NonTerminal::getFollow_() const {
    return follow_;
}

void NonTerminal::setFollow_(const std::unordered_set<std::string> &follow_) {
    NonTerminal::follow_ = follow_;
}

const std::vector<std::vector<std::string>> &NonTerminal::getProduction_rules_() const {
    return production_rules_;
}

void NonTerminal::setProduction_rules_(const std::vector<std::vector<std::string>> &production_rules_) {
    NonTerminal::production_rules_ = production_rules_;
}

const std::unordered_map<std::string, int> &NonTerminal::getParse_table_entry_() const {
    return parse_table_entry_;
}

void NonTerminal::setParse_table_entry_(const std::unordered_map<std::string, int> &parse_table_entry_) {
    NonTerminal::parse_table_entry_ = parse_table_entry_;
}

int NonTerminal::GetProductionRuleIndex(std::string token) {
    if (parse_table_entry_.find(token) == parse_table_entry_.end()) {
        return EMPTY_CELL_INDEX;
    }
    return parse_table_entry_.at(token);
}

std::vector<std::string> NonTerminal::GetProductionRule(int index) {
    return this->production_rules_.at(index);
}
