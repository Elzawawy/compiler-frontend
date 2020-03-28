
// Created by omar_swidan on 23/03/20.
//

#include "nfa.h"
unordered_map<NFAState*, NFAState *> combiined_nfa_states;

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
}


int NFA::precedence_decision(string operator_symbol) {


    if(operator_symbol == "*" || operator_symbol=="+")
        return 3;
    else if(operator_symbol == "|" )
        return 1;
    else
        return -1;

}



NFAState* NFA::construct_one_transition_state(string transition, vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map) {
NFAState *start_state= new NFANormalState();
NFAState *finish_state=new NFANormalState();
start_state->add_neighbour(transition,finish_state);
start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
//    vector < pair<string , NFAState *>> x;
//    x=start_state.getNeighbours();
//start_to_acceptance_map->insert(&start_state,&finish_state);
//    for ( vector < pair<string,NFAState*> >::const_iterator it = x.begin() ; it != x.end(); it++){
//        cout << it->first;
//    }

    return start_state;
}

NFAState* NFA::postfix_to_NFA(string postfix,vector<string>input_table) {
    NFAState *start_state=new NFANormalState();
    stack <NFAState*> nfa_state_stack;
    vector < pair<NFAState *, NFAState *>> start_to_acceptance_map;
    bool input_acceptor=false;
    string input_identifier="";


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
                       nfa_state_stack.push(this->construct_one_transition_state(input_identifier,&start_to_acceptance_map));
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
                   NFAState* plus_nfa_state = this->plus(nfa_state_stack.top(),&start_to_acceptance_map);
                   nfa_state_stack.pop();
                   nfa_state_stack.push(plus_nfa_state);
                   break;
               }
               case '*': {
                   NFAState* kleene_nfa_state = this->kleene(nfa_state_stack.top(),&start_to_acceptance_map);
                   nfa_state_stack.pop();
                   nfa_state_stack.push(kleene_nfa_state);
                   break;
               }
               case '|': {
                   NFAState* second_operand_union_state = nfa_state_stack.top();

                   nfa_state_stack.pop();
                   NFAState* first_operand_union_state = nfa_state_stack.top();

                   nfa_state_stack.pop();
                   nfa_state_stack.push(this->or_combiner(first_operand_union_state, second_operand_union_state,&start_to_acceptance_map));
                   break;
               }
           }
       }
   i++;
//       cout<<"IN";
//      cout<<start_to_acceptance_map.size();
//        for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map.begin() ; it != start_to_acceptance_map.end(); it++){
//            cout << (it->first)->getId();
//        }
   }while(nfa_state_stack.size()>=1 && i<postfix.size());
    return start_state;
}

NFAState* NFA::plus(NFAState* nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map) {
    NFAState *start_state=new NFANormalState();
    return start_state;
}

NFAState* NFA::or_combiner(NFAState* first_nfa_state, NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map) {
    //Initilaizing a start and acceptance node for the union thompson rule
    NFAState *start_state=new NFANormalState();
    NFAState *finish_state=new NFANormalState();
    //Adding 2 neighbours from the start node with a transition epsilon where the neighbours are the 2 start nodes of the unioned nfa's
    start_state->add_neighbour("\\L",first_nfa_state);
    start_state->add_neighbour("\\L",second_nfa_state);
    //Getting the finish states of the unioned nfa's and adding the finsih state of the resulting nfa as their neigbhours with a transition epsilon
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map->begin() ; it != start_to_acceptance_map->end(); it++){
        (it->second)->add_neighbour("\\L",finish_state);
    }
    //Adding the first and finish states to the map
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
    return start_state;
}
NFAState* NFA::kleene(NFAState* nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map) {
    NFAState *start_state=new NFANormalState();
    return start_state;
}

NFAState* NFA::concat(NFAState* first_nfa_state, NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map) {
    NFAState *start_state=new NFANormalState();
    return start_state;
}
