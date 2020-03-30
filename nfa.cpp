
// Created by omar_swidan on 23/03/20.
//

#include "nfa.h"
unordered_map<NFAState*, NFAState *> combiined_nfa_states;

NFA::NFA(){

}
NFAState NFA::regex_to_nfa(){
//    for(int i=0;i<regex.size();i++)
//    {
    unordered_set<string>input_table={"a-z","A-Z","B-E","b","o","o","l","\\="};
    struct regex{
        string name;
        string value;
    }regex;
    regex.value="bo|ol";
    string postfix;
    postfix=this->infix_to_postfix(regex.value,input_table);
    cout<<postfix;
    this->postfix_to_NFA(postfix,input_table);
    this->resolve_input_table(&input_table);

//    }

    return NFAState();
}



string NFA::infix_to_postfix(string regex,unordered_set<string>input_table) {

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
        if(isalpha(regex[i])||isalnum(regex[i]) || regex[i]=='\\') {
            while(input_acceptor==false)
            {
                input_identifier += regex[i];
                for (const auto& element: input_table) {
                    if (input_identifier.compare(element)==0) {
                        input_acceptor = true;
                        break;
                    }
                    /* ... process elem ... */
                }
                for (int comparison_iterator = 0; comparison_iterator < input_table.size(); comparison_iterator++) {

                }
                i++;
            }
            //Check if the next character is an operator or end of string
            //If no then add a concatintaion operator between the 2 characters
            //else do nothing
            if(!this->isOperator(regex[i])&&i+1<=regex.size()){
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
    else if(operator_symbol=="-"){
        return 2;
    }
    else if(operator_symbol == "|" )
        return 1;
    else
        return -1;

}



NFAState* NFA::construct_one_transition_state(string transition, vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state) {
    NFAState *start_state= new NFANormalState();
    NFAState *finish_state=this->acceptance_state_generator(final_finish_state);
    transition=resolve_backslash(transition);
    start_state->add_neighbour(transition,finish_state);
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
//    vector < pair<string , NFAState *>> x;
//    x=start_state.getNeighbours();
//    for ( vector < pair<string,NFAState*> >::const_iterator it = x.begin() ; it != x.end(); it++){
//        cout << it->first;
//    }

    return start_state;
}

NFAState* NFA::postfix_to_NFA(string postfix,unordered_set<string>input_table) {
    NFAState *start_state=new NFANormalState();
    stack <NFAState*> nfa_state_stack;
    vector < pair<NFAState *, NFAState *>> start_to_acceptance_map;
    bool input_acceptor=false;
    bool final_finish_state=false;
    string input_identifier="";


    // Scan all characters one by one
    int i=0;
    do {
        // If the scanned character is an operand (number here),
        // push it to the stack.
        if (isalpha(postfix[i]) || isalnum(postfix[i])||postfix[i]=='\\') {
            while (input_acceptor == false) {
                input_identifier += postfix[i];
                for (const auto& element: input_table) {
                    if (input_identifier.compare(element) == 0) {
                        nfa_state_stack.push(this->construct_one_transition_state(input_identifier,&start_to_acceptance_map,final_finish_state));
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
        else if (postfix[i]=='|'||postfix[i]=='-'||postfix[i]=='+'||postfix[i]=='-') {

            switch (postfix[i]) {
                case '+': {
                    NFAState* plus_nfa_state = this->kleene_and_plus(nfa_state_stack.top(),&start_to_acceptance_map,false,final_finish_state);
                    nfa_state_stack.pop();
                    nfa_state_stack.push(plus_nfa_state);
                    break;
                }
                case '*': {
                    NFAState* kleene_nfa_state = this->kleene_and_plus(nfa_state_stack.top(),&start_to_acceptance_map,true,final_finish_state);
                    nfa_state_stack.pop();
                    nfa_state_stack.push(kleene_nfa_state);
                    break;
                }
                case '|': {
                    NFAState* second_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    NFAState* first_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    nfa_state_stack.push(this->or_combiner(first_operand_union_state, second_operand_union_state,&start_to_acceptance_map,final_finish_state));
                    break;
                }
                case '-': {
                    NFAState* second_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();

                    NFAState* first_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    nfa_state_stack.push(this->concat(first_operand_union_state, second_operand_union_state,&start_to_acceptance_map,final_finish_state));
                    break;
                }

            }
        }
        cout<<"fasfsa";
        cout<<postfix[i+1];
        if(this->acceptance_nfa_identifier(nfa_state_stack.size(),postfix.length(),i,postfix[i+1])){
            final_finish_state=true;
        }
        cout<<this->acceptance_nfa_identifier(nfa_state_stack.size(),postfix.length(),i,postfix[i+1])<<endl;
        i++;

    }while(nfa_state_stack.size()>=1 && i<postfix.size());
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map.begin() ; it != start_to_acceptance_map.end(); it++){
        cout<<(it->first)->getId()<<endl;
        vector < pair<string , NFAState *>> x;
        x=(it->first)->getNeighbours();
        for ( vector < pair<string,NFAState*> >::const_iterator it = x.begin() ; it != x.end(); it++){
            cout<<"transition:";
            cout << it->first<<endl;
            cout<<it->second->getId()<<endl;
            vector < pair<string , NFAState *>> u;
            u=(it->second)->getNeighbours();
            for ( vector < pair<string,NFAState*> >::const_iterator it1 = u.begin() ; it1 != u.end(); it1++){
                cout<<"finish:";
                cout << it1->first<<endl;
                cout<<it1->second->getId()<<endl;

            }
        }
        cout<<"Done"<<endl;
    }
    return nfa_state_stack.top();
}



NFAState* NFA::or_combiner(NFAState* first_nfa_state, NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state) {
    //Initilaizing a start and acceptance node for the union thompson rule
    NFAState *start_state=new NFANormalState();
    NFAState *finish_state=this->acceptance_state_generator(final_finish_state);
    //Adding 2 neighbours from the start node with a transition epsilon where the neighbours are the 2 start nodes of the unioned nfa's
    start_state->add_neighbour("\\L",first_nfa_state);
    start_state->add_neighbour("\\L",second_nfa_state);
    //Getting the finish states of the unioned nfa's and adding the finsih state of the resulting nfa as their neigbhours with a transition epsilon
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map->begin() ; it != start_to_acceptance_map->end(); it++){
        if(it->first==first_nfa_state || it->first==second_nfa_state) {
            (it->second)->add_neighbour("\\L", finish_state);
        }
    }
    //Adding the first and finish states to the map
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
    return start_state;
}
NFAState* NFA::kleene_and_plus(NFAState* nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map,bool kleene, bool final_finish_state) {
    NFAState *start_state=new NFANormalState();
    NFAState *finish_state=this->acceptance_state_generator(final_finish_state);
    //Adding an epsilon transition from the new start state to 1-) the start state of the old nfa 2-)the finish state of the new nfa
    start_state->add_neighbour("\\L",nfa_state);
    //In case it is a kleene operator add an epsilon transition from the start state to the accept state
    //In case it is a plus operator do nothing
    if(kleene==true) {
        start_state->add_neighbour("\\L", finish_state);
    }
    //getting the start and finish states of the old nfa and making 2 transitions
    //1-)epsilon from the finsih state of the old to the start state of the old
    //2-)epsilon from the finish state of the old to the finish state of the the new
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map->begin() ; it != start_to_acceptance_map->end(); it++){
        if(it->first==nfa_state) {
            (it->second)->add_neighbour("\\L", finish_state);
            (it->second)->add_neighbour("\\L", it->first);
            break;
        }
    }
    //Adding the first and finish states of the new nfa to the map
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
    return start_state;
}

NFAState* NFA::concat(NFAState* first_nfa_state, NFAState* second_nfa_state,vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state) {
    NFAState *first_nfa_acceptance_state,*second_nfa_acceptance_state;
    vector < pair<string , NFAState *>> temp_vector;
    int iterator=0;
    //Find the acceptance state of the first concatinated nfa and the start state of the second concatinated nfa
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map->begin() ; it != start_to_acceptance_map->end(); it++){
        //Save the address of the acceptance state of the first concatinated inorder to add the neigbhours of the start state of the second concatinated nfa
        if(first_nfa_state==it->first){
            first_nfa_acceptance_state=it->second;
        }
            //Get the neighbours of the start state of the second concatinated nfa inorder to add the neighbours to the acceptance state of the first concatinted nfa
        else if((it->first)==second_nfa_state){
            temp_vector=(it->first)->getNeighbours();
            second_nfa_acceptance_state=it->second;
        }
        iterator++;
    }
    //Add the neighbours to the acceptance state of the first nfa
    for ( vector < pair<string,NFAState*> >::const_iterator it = temp_vector.begin() ; it != temp_vector.end(); it++){
        first_nfa_acceptance_state->add_neighbour(it->first,it->second);
    }
    //
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (first_nfa_state, second_nfa_acceptance_state));
    return first_nfa_state;
}

//Check if a transition has a backslash
//if yes then trancate the backslash from the string
//else return the string without change
string NFA::resolve_backslash(string transition) {
    if(transition.find('\\')!= string::npos){
        transition.erase(0,1);
    }
    return transition;

}

bool NFA::isOperator(char character) {
    if(character=='|'||character=='*'||character=='+'){
        return true;
    }
    return false;
}

//Handling the input table by removing all the backslashes from the input table inorder to sync with the transitioned data between states
void NFA::resolve_input_table(unordered_set<string>* input_table) {
    for (const auto& element: *input_table) {
        input_table->erase(element);
        input_table->insert(this->resolve_backslash(element));
    }

}

bool NFA::acceptance_nfa_identifier(int size_of_stack,int postfix_length,int current_iteration, char next_char) {

    if(current_iteration+2==postfix_length) {
        if (next_char == '-' || next_char == '|') {
            if (size_of_stack == 2) {
                return true;
            }
        } else if (next_char == '*' || next_char == '+') {
            if (size_of_stack == 1) {
                return true;
            }
        }
    }
    return false;
}

//Checks if this acceptance state is an acceptance state of the final nfa of a regex or it is one of the building nfa's
//Incase it is the final nfa of the regex it returns an nfa with the type acceptance state
//Incase it is a bulding nfa it returns a normal nfa state
NFAState *NFA::acceptance_state_generator(bool final_finish_state) {
    static int id=0;
    if(!final_finish_state){
        return new NFANormalState();
    }
    else{
        return new NFAAcceptanceState();
    }
}
