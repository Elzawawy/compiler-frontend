/**
    Compiler Phase 1: LEXGEN
    regular_expression.cpp
    Purpose: Resembles the RE Entity in our codebase and is responsible for all operations performed on REs.

    @author Amr Elzawawy
    @version 1.0
    @date 27/3/2020
*/

#include "regular_expression.h"
#define LEFT_PARENTHESES '('
#define RIGHT_PARENTHESES ')'
#define ESCAPE_CHARACTER '\\'
#define RANGE_EXTRA_OPERATION  '-'

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

bool RegularExpression::isReservedCharacter(char character)
{
    return (character==LEFT_PARENTHESES || character==RIGHT_PARENTHESES
            || character==ESCAPE_CHARACTER
            || character==KLEENE_CLOSURE_OPERATOR
            || character==POSITIVE_CLOSURE_OPERATOR
            || character==UNION_OPERATOR
            || character==CONCAT_OPERATOR);
}

/**
    Expands the range operator to the full fledged meaning of it in the RE.
    Operates on the RE value of the instance being called on.
*/
void RegularExpression::applyRangeOperationIfExists()
{
    for (ul char_index = 0; char_index<value_.length(); char_index++) {
        // do we got a range operator and it is not escaped using escape character ?
        if (value_[char_index]==RANGE_EXTRA_OPERATION and value_[char_index-1]!=ESCAPE_CHARACTER) {
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

/**
    Extracts the existing input symbols from the RE value contained in this instance being called on.
    @return vector<string> a list of all input symbols found in an RE.
*/
std::unordered_set<std::string> RegularExpression::extractInputSymbols()
{
    std::unordered_set<std::string> input_symbols;
    for (int char_index = 0; char_index<value_.length(); char_index++)
        if (isReservedCharacter(value_[char_index]))
            // if an escape character, we need to take it and the next character as a whole symbol.
            if (value_[char_index]==ESCAPE_CHARACTER)
                input_symbols.insert({value_[char_index], value_[++char_index]});
                // if a range operation, we have to consider characters from the left till the right of the character.
            else if (value_[char_index]==RANGE_EXTRA_OPERATION)
                for (int range_index = value_[char_index-1]+1; range_index<value_[char_index+1]; range_index++)
                    input_symbols.emplace(1, range_index);
                // otherwise, its a operator we don't need to place as symbol.
            else
                continue;
            // otherwise, its a normal non reserved character that we need to add as symbol.
        else
            input_symbols.emplace(1, value_[char_index]);
    return input_symbols;
}



std::string RegularExpression::infix_to_postfix(std::unordered_set<std::string>input_table) {
    this->applyRangeOperationIfExists();
    std::string regex=this->getValue();
    // Declaring a Stack from Standard template library in C++.
    std::stack<std::string> infix_to_postfix_stack;
    std::string postfix = ""; // Initialize postfix as empty string.
    std::string input_identifier="";
    bool input_acceptor=false;
    infix_to_postfix_stack.push("N");
    std::string input_detector="";
    std::cout<<regex<<std::endl;
    for(int i = 0; i < regex.size(); i++)
    {
        // If the scanned character is an operand, add it to output string.
        if(isNotOperator(regex[i])) {
            while(input_acceptor==false)
            {
                input_identifier += regex[i];
                for (const auto& element: input_table) {
                    if (input_identifier.compare(element)==0) {
                        input_acceptor = true;
                        break;
                    }
                }

                i++;
            }
            //Check if the next character is an operator or end of string
            //If no then add a concatintaion operator between the 2 characters
            //else do nothing
            if(!this->isConcated(regex[i])&&i+1<=regex.size()){
                regex.insert(i,"-",1);
            }
            i--;
            postfix += input_identifier;
            input_acceptor=false;
            input_identifier="";

        }
            // If the scanned character is an ‘(‘, push it to the stack.
        else if(regex[i] == '(')

            infix_to_postfix_stack.push("(");

            // If the scanned character is an ‘)’, pop and to output string from the stack
            // until an ‘(‘ is encountered.
        else if(regex[i] == ')')
        {

            std::string popped_character;
            while(infix_to_postfix_stack.top() != "N" && infix_to_postfix_stack.top() != "(")
            {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
                postfix += popped_character;
            }
            if(infix_to_postfix_stack.top() == "(")
            {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
            }
            if(regex[i+1]=='('&&i+1<=regex.size()){
                regex.insert(i+1,"-",1);
            }
        }

            //If an operator is scanned
        else{
            std::string popped_character;
            while(infix_to_postfix_stack.top() != "N" && precedence_decision(std::string (1, regex[i])) <= precedence_decision(infix_to_postfix_stack.top()))
            {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
                postfix += popped_character;
            }

            infix_to_postfix_stack.push(std::string (1, regex[i]));
        }

    }
    std::string popped_character;
    //Pop all the remaining elements from the stack
    while(infix_to_postfix_stack.top() != "N")
    {
        popped_character= infix_to_postfix_stack.top();
        infix_to_postfix_stack.pop();
        postfix += popped_character;
    }


    return postfix;
}

int RegularExpression::precedence_decision(std::string operator_symbol) {


    if(operator_symbol == "*" || operator_symbol=="+")
        return 3;
    else if(operator_symbol=="-"){
        return 2;
    }
    else if(operator_symbol == "|" )
        return 1;
    else
        return -1;

}

bool RegularExpression::isConcated(char character) {
    if(character=='|'||character=='*'||character=='+'||character==')'){
        return true;
    }
    return false;
}
bool RegularExpression::isNotOperator(char character) {
    if(character=='|'||character=='*'||character=='+'||character=='-'||character=='('|| character==')'){
        return false;
    }
    return true;
}
