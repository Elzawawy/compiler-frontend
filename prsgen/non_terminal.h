//
// Created by zawawy on 4/21/20.
//
#include <set>
#include <vector>
#include <map>

#ifndef PRSGEN_NON_TERMINAL_H
#define PRSGEN_NON_TERMINAL_H

class NonTerminal {
private:
    std::string name_;
    std::set<std::string> first_;
    std::set<std::string> follow_;
    std::vector<std::vector<std::string>> production_rules_;
    std::map<std::string, int> parse_table_entry_; //string is the input
public:
    explicit NonTerminal(const std::string& name_);
    const std::string& getName_() const;
    const std::set<std::string>& getFirst_() const;
    void setFirst_(const std::set<std::string>& first_);
    const std::set<std::string>& getFollow_() const;
    void setFollow_(const std::set<std::string>& follow_);
    const std::vector<std::vector<std::string>>& getProduction_rules_() const;
    void setProduction_rules_(const std::vector<std::vector<std::string>>& production_rules_);
    const std::map<std::string, int>& getParse_table_entry_() const;
    void setParse_table_entry_(const std::map<std::string, int>& parse_table_entry_);
    int GetProductionRuleIndex(std::string token);
    std::vector<std::string> GetProductionRule(int index);
};

#endif //PRSGEN_NON_TERMINAL_H
