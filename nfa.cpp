
// Created by omar_swidan on 23/03/20.
//

#include "nfa.h"
NFA::NFA(){

}
NFAState NFA::regex_to_nfa(){
//    for(int i=0;i<regex.size();i++)
//    {
vector<string>input_table={"a-z","A-Z","B-E"};
    struct regex{
        string name;
        string value;
    }regex;
    regex.value="a-z|(A-Z)*|(B-E)+";
   cout<<this->infix_to_postfix(regex.value,input_table);

//    }

    return NFAState(false);
}

NFAState NFA::kleene(NFAState nfa_state) {
    return NFAState(false);
}

NFAState NFA::concat(NFAState first_nfa_state, NFAState second_nfa_state) {

    return NFAState(false);
}

NFAState NFA::or_combiner(vector<NFAState> selections, int no_of_selections) {
    return NFAState(false);
}

string NFA::infix_to_postfix(string regex,vector<string>input_table) {
    // Declaring a Stack from Standard template library in C++.
    stack<string> infix_to_postfix_stack;
    string postfix = ""; // Initialize postfix as empty string.
    string input_identifier="";
    bool input_acceptor=false;
    infix_to_postfix_stack.push("N");
    string input_detector="";
    for(int i = 0; i < regex.size(); i++)
    {

        // If the scanned character is an operand, add it to output string.
        if(isalpha(regex[i])) {
            while(input_acceptor==false) {
                input_identifier += regex[i];
                for (int comparison_iterator = 0; comparison_iterator < input_table.size(); comparison_iterator++) {
                    if (input_identifier.compare(input_table[comparison_iterator])==0) {
                        input_acceptor = true;
                        break;
                    }

                }
                i++;
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
            string popped_character;
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
        }

            //If an operator is scanned
        else{
            string popped_character;
            while(infix_to_postfix_stack.top() != "N" && precedence_decision(std::string (1, regex[i])) <= precedence_decision(infix_to_postfix_stack.top()))
            {
                popped_character = infix_to_postfix_stack.top();
                infix_to_postfix_stack.pop();
                postfix += popped_character;
            }

            infix_to_postfix_stack.push(std::string (1, regex[i]));
        }

    }
    string popped_character;
    //Pop all the remaining elements from the stack
    while(infix_to_postfix_stack.top() != "N")
    {
        popped_character= infix_to_postfix_stack.top();
        infix_to_postfix_stack.pop();
        postfix += popped_character;
    }


    return postfix;
    return std::__cxx11::string();
}

bool NFA::is_operator(char character) {
    return false;
}

bool NFA::is_operand(char character) {
    return false;
}

string NFA::pre_process_regex(string regex) {
    return std::__cxx11::string();
}

int NFA::precedence_decision(string operator_symbol) {


    if(operator_symbol == "*" || operator_symbol=="+")
        return 3;
    else if(operator_symbol == "|" )
        return 1;
    else
        return -1;

}

string NFA::char_to_string_converter(char character) {
    return std::string (1, character);
}