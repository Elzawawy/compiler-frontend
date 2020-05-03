//
// Created by zawawy on 4/21/20.
//
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>

#ifndef PRSGEN_NON_TERMINAL_H
#define PRSGEN_NON_TERMINAL_H

class NonTerminal {
private:
    std::string name_;
    std::unordered_set<std::string> first_;
    std::unordered_set<std::string> follow_;
    std::vector<std::vector<std::string>> production_rules_;
    std::unordered_map<std::string, int> parse_table_entry_;
public:
    explicit NonTerminal(const std::string& name_);
    const std::string& getName_() const;
    const std::unordered_set<std::string>& getFirst_() const;
    void setFirst_(const std::unordered_set<std::string>& first_);
    const std::unordered_set<std::string>& getFollow_() const;
    void setFollow_(const std::unordered_set<std::string>& follow_);
    const std::vector<std::vector<std::string>>& getProduction_rules_() const;
    void setProduction_rules_(const std::vector<std::vector<std::string>>& production_rules_);
    const std::unordered_map<std::string, int>& getParse_table_entry_() const;
    void setParse_table_entry_(const std::unordered_map<std::string, int>& parse_table_entry_);
};

#endif //PRSGEN_NON_TERMINAL_H
