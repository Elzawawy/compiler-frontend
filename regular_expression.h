/**
    Compiler Phase 1: LEXGEN
    regular_expression.h
    Purpose: Resembles the RE Entity in our codebase and is responsible for all operations performed on REs.

    @author Amr Elzawawy
    @version 1.0
    @date 27/3/2020
*/

#ifndef LEXGEN_REGULAR_EXPRESSION_H
#define LEXGEN_REGULAR_EXPRESSION_H

#include <string>
#include <vector>

class RegularExpression {
private:
    std::string name_;
    std::string value_;
    bool isReservedCharacter(char character);
public:
    RegularExpression(const std::string& name, const std::string& value);
    const std::string& getName() const;
    const std::string& getValue() const;
    void applyRangeOperationIfExists();
    std::vector<std::string> extractInputSymbols();
};

#endif //LEXGEN_REGULAR_EXPRESSION_H
