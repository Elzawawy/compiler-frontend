
// Created by omar_swidan on 23/03/20.
//

#include "nfa.h"
NFA::NFA(){

}
NFAState NFA::regex_to_nfa(){
//    for(int i=0;i<regex.size();i++)
//    {
vector<string>input_table={"a-z","A-Z","B-E","b","o","o","l"};
    struct regex{
        string name;
        string value;
    }regex;
    regex.value="a-z|A-Z";
    string postfix;
     postfix=this->infix_to_postfix(regex.value,input_table);
cout<<postfix;
      this->postfix_to_NFA(postfix,input_table);
//    }

    return NFAState();
}

NFAState NFA::kleene(NFAState nfa_state) {
    return NFAState();
}

NFAState NFA::concat(NFAState first_nfa_state, NFAState second_nfa_state) {

    return NFAState();
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
        if(isalpha(regex[i])||isalnum(regex[i])) {
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


int NFA::precedence_decision(string operator_symbol) {


    if(operator_symbol == "*" || operator_symbol=="+")
        return 3;
    else if(operator_symbol == "|" )
        return 1;
    else
        return -1;

}



NFAState NFA::construct_one_transition_state(string transition) {
    return NFAState();
}

NFAState NFA::postfix_to_NFA(string postfix,vector<string>input_table) {
    // Create a stack of capacity equal to expression size
    stack <NFAState> nfa_state_stack;
    bool input_acceptor=false;
    string input_identifier="";
    cout<<postfix;

    // Scan all characters one by one
   int i=0;
    do {
       // If the scanned character is an operand (number here),
       // push it to the stack.
       if (isalpha(postfix[i]) || isalnum(postfix[i])) {
           while (input_acceptor == false) {
               input_identifier += postfix[i];
               for (int comparison_iterator = 0; comparison_iterator < input_table.size(); comparison_iterator++) {
                   if (input_identifier.compare(input_table[comparison_iterator]) == 0) {
                       nfa_state_stack.push(this->construct_one_transition_state(input_identifier));
                       input_acceptor = true;
                       break;
                   }

               }
               i++;
           }
           i--;



           input_acceptor = false;
           input_identifier = "";

       }

           // If the scanned character is an operator, pop two
           // elements from stack apply the operator
       else if (postfix[i] == '+' || postfix[i] == '*' || postfix[i] == '|') {

           switch (postfix[i]) {
               case '+': {
                   NFAState plus_nfa_state = this->plus(nfa_state_stack.top());
                   nfa_state_stack.pop();
                   nfa_state_stack.push(plus_nfa_state);
                   break;
               }
               case '*': {
                   NFAState kleene_nfa_state = this->kleene(nfa_state_stack.top());
                   nfa_state_stack.pop();
                   nfa_state_stack.push(kleene_nfa_state);
                   break;
               }
               case '|': {
                   NFAState first_operand_union_state = nfa_state_stack.top();
                   nfa_state_stack.pop();
                   NFAState second_operand_union_state = nfa_state_stack.top();
                   nfa_state_stack.pop();
                   nfa_state_stack.push(this->or_combiner(first_operand_union_state, second_operand_union_state));
                   break;
               }
           }
       }
   i++;
   }while(!nfa_state_stack.empty());
    return NFAState();
    return NFAState();
}

NFAState NFA::plus(NFAState nfa_state) {
    return NFAState();
}

NFAState NFA::or_combiner(NFAState first_nfa_state, NFAState second_nfa_state) {
    return NFAState();
}
