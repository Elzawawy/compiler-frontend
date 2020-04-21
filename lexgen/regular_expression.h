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
#define ESCAPE_CHARACTER '\\'

#include <iostream>

#include <string>
#include <unordered_set>
#include <stack>
/**
 * The algberic operators that can be applied on regular expressions while evaluating the regex.
 * While, concat operator doesn't have a definite indicator, we use '-' for it since this is already reserved for range extra operation as a user extension and not a algberic operator.
 * The range extra operation indicator is ensured to be replaced early before processing an infix to postfix conversion.
 * */
typedef enum RegexOperators {
    UNION_OPERATOR = '|',
    CONCAT_OPERATOR = '-',
    KLEENE_CLOSURE_OPERATOR = '*',
    POSITIVE_CLOSURE_OPERATOR = '+',

} RegexOperators;
class RegularExpression {
private:
    std::string name_;
    std::string value_;

    bool isReservedCharacter(char character);

    int precedence_decision(std::string operator_symbol);

    bool isConcated(char character);

    bool isNotOperator(char character);


public:
    RegularExpression(const std::string &name, const std::string &value);

    const std::string &getName() const;

    const std::string &getValue() const;

    void applyRangeOperationIfExists();

    std::unordered_set<std::string> extractInputSymbols();

    std::string infix_to_postfix(std::unordered_set<std::string> input_table);

};

#endif //LEXGEN_REGULAR_EXPRESSION_H
