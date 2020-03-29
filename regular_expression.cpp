//
// Created by zawawy on 3/27/20.
//

#include "regular_expression.h"
#define LEFT_PARENTHESES '('
#define RIGHT_PARENTHESES ')'
#define ESCAPE_RESERVED_CHAR '\\'

typedef enum RegexOperators {
  UNION_OPERATOR = '|',
  CONCAT_OPERATOR,
  KLEENE_CLOSURE_OPERATOR = '*',
  POSITIVE_CLOSURE_OPERATOR = '+',
  RANGE_OPERATOR = '-'

} RegexOperators;
typedef unsigned long ul;

const std::string& RegularExpression::getName() const
{
    return name_;
}
const std::string& RegularExpression::getValue() const
{
    return value_;
}
RegularExpression::RegularExpression(const std::string& name, const std::string& value)
        :name_(name), value_(value) { }

void RegularExpression::applyRangeOperationIfExists()
{
    for (ul char_index = 0; char_index<value_.length(); char_index++) {
        // do we got a range operator and it is not escaped using escape character ?
        if (value_[char_index]==RANGE_OPERATOR and value_[char_index-1]!=ESCAPE_RESERVED_CHAR) {
            // initialize local variables to clean up code and make more readable.
            std::string replacement_string;
            char begin_range = value_[char_index-1];
            char end_range = value_[char_index+1];
            ul length_to_replace = 3;
            // generate the exploded range given in regex and save into a string to replace in the end.
            for (char range_index = begin_range; range_index<=end_range; range_index++) {
                if (range_index==begin_range)
                    replacement_string += {LEFT_PARENTHESES, range_index, UNION_OPERATOR};
                else if (range_index==end_range)
                    replacement_string += {range_index, RIGHT_PARENTHESES};
                else
                    replacement_string += {range_index, UNION_OPERATOR};
            }
            // replace three characters in this form ('begin_range' '-' 'end_range') with the exploded string generated above.
            value_.replace(char_index-1, length_to_replace, replacement_string);
        }
    }
}