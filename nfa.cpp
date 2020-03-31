
// Created by omar_swidan on 23/03/20.
//
#include "nfa.h"
vector < pair<NFAState *, NFAState *>> combined_nfa_states;
NFA::NFA(){

}
NFAState* NFA::regex_to_nfa( std::unordered_set<std::string>input_table,std::vector<RegularExpression>regex){
    string postfix;
    unordered_set<string>resolved_input_table;

for(int i=0;i<regex.size();i++){
    postfix=regex[i].infix_to_postfix(input_table);
    this->postfix_to_NFA(postfix,input_table,regex[i].getName());
}
    cout<<postfix;
NFAState* start_state=new NFANormalState();

    this->set_input_table(this->resolve_input_table(input_table));
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = combined_nfa_states.begin() ; it !=combined_nfa_states.end(); it++){
start_state->add_neighbour("\\L",it->first);
    }

    return start_state;
}





NFAState* NFA::construct_one_transition_state(string transition, vector < pair<NFAState *, NFAState *>>* start_to_acceptance_map, bool final_finish_state) {
    NFAState *start_state= new NFANormalState();
    NFAState *finish_state=this->acceptance_state_generator(final_finish_state);
    transition=resolve_backslash(transition);
    start_state->add_neighbour(transition, finish_state);
    start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (start_state, finish_state));
    return start_state;
}

NFAState* NFA::postfix_to_NFA(string postfix,unordered_set<string>input_table,string regex_name) {
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
        if (!isOperator(postfix[i])) {
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

        cout<<final_finish_state;
        i++;

    }while(nfa_state_stack.size()>=1 && i<postfix.size());
    //Adding the start and acceptance states of the final nfa to the global combined nfa map
    NFAState* acceptance=new NFAAcceptanceState();
    NFAAcceptanceState* acceptance_state= dynamic_cast<NFAAcceptanceState*>(acceptance);
    start_to_acceptance_map[start_to_acceptance_map.size()-1].second->add_neighbour("\\L",acceptance_state);
    cout<<acceptance_state->getId();
    acceptance_state->set_token(regex_name);
    combined_nfa_states.push_back(pair<NFAState*, NFAState*> (nfa_state_stack.top(),acceptance_state));




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
    NFAState *first_nfa_acceptance_state;

    vector < pair<string , NFAState *>> temp_vector;
    int iterator=0;
    //Find the acceptance state of the first concatinated nfa and the start state of the second concatinated nfa
    for ( vector < pair<NFAState*,NFAState*> >::const_iterator it = start_to_acceptance_map->begin() ; it != start_to_acceptance_map->end(); it++){
        //Save the address of the acceptance state of the first concatinated inorder to add the neigbhours of the start state of the second concatinated nfa
        if(first_nfa_state==it->first){
            first_nfa_acceptance_state=it->second;
            iterator++;
        }
            //Get the neighbours of the start state of the second concatinated nfa inorder to add the neighbours to the acceptance state of the first concatinted nfa
        else if((it->first)==second_nfa_state){
            temp_vector=(it->first)->getNeighbours();
            start_to_acceptance_map->push_back(pair<NFAState*, NFAState*> (first_nfa_state,it->second));

            iterator++;
        }
        if(iterator==2){
            break;
        }
    }
    //Add the neighbours to the acceptance state of the first nfa
    for ( vector < pair<string,NFAState*> >::const_iterator it = temp_vector.begin() ; it != temp_vector.end(); it++){
        first_nfa_acceptance_state->add_neighbour(it->first,it->second);

    }


    //
    return first_nfa_state;
}

//Check if a transition has a backslash
//if yes then trancate the backslash from the string
//else return the string without change
std::string NFA::resolve_backslash(std::string transition) {
    if(transition.find('\\')!= string::npos){
        transition.erase(0,1);
    }
    return transition;

}



//Handling the input table by removing all the backslashes from the input table inorder to sync with the transitioned data between states
unordered_set<string>NFA::resolve_input_table(unordered_set<string>input_table){
    unordered_set<string>editted_input_table;
    for (const auto& element: input_table) {
             editted_input_table.insert(this->resolve_backslash(element));

    }
    return editted_input_table;
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
    if(!final_finish_state){
        return new NFANormalState();
    }
    else{
        cout<<"IN";
        return new NFAAcceptanceState();
    }
}

bool NFA::isOperator(char character) {
    if(character=='|'||character=='*'||character=='+'||character=='-'){
        return true;
    }
    return false;
}

unordered_set<string> NFA::get_input_table() {
    return this->input_table;
}

void NFA::set_input_table(unordered_set<string> input_table) {
this->input_table=input_table;
}


