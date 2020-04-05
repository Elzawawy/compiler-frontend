
// Created by omar_swidan on 23/03/20.
//
#define EPSILON "\\L"

#include "nfa.h"
#include "regular_expression.h"

vector<pair<NFAState *, NFAState *>> combined_nfa_states;
vector<pair<NFAState *, NFAState *>> global_states;

NFA::NFA() {

}

/**
 Takes a a vector of Regular Expressions and an unordered set of strings representing the input_table
 Converts the input regex to nfa in 4 steps;
 1-)Converts the infix of the regex to postfix
 2-)Converts eact postfixed output to NFA
 3-)Resolves the input table by removing all backslashes from all transitions
 4-)Combines all the nfas of all regex
 @return an NFAState pointer representing the start state of the combined resulting NFA
*/
NFAState *NFA::regex_to_nfa(std::unordered_set<std::string> input_table, std::vector<RegularExpression> regex) {
    string postfix;
    unordered_set<string> resolved_input_table;

    //iterates over the size of the vector of regular expression
    for (int i = 0; i < regex.size(); i++) {
        //Convert each infix to postfix
        postfix = regex[i].infix_to_postfix(input_table);
        //Convert each postfix to an NFA
        this->postfix_to_NFA(postfix, input_table, regex[i].getName(),i);
    }
    NFAState *start_state = new NFANormalState();
    //Resolves the input table by removing all backslashes
    this->set_input_table(this->resolve_input_table(input_table));
    //Combining the nfastates
    for (vector<pair<NFAState *, NFAState *> >::const_iterator it = combined_nfa_states.begin();
         it != combined_nfa_states.end(); it++) {
        start_state->add_neighbour(EPSILON, it->first);
    }
//    for (vector<pair<NFAState *, NFAState *> >::const_iterator it = global_states.begin();
//         it != global_states.end(); it++) {
//        vector<pair<string, NFAState *>> x;
//        vector<pair<string, NFAState *>> u;
//        x = (it->first)->getNeighbours();
//        u = (it->second)->getNeighbours();
//        for (vector<pair<string, NFAState *> >::const_iterator it1 = x.begin(); it1 != x.end(); it1++) {
//            cout << it->first->getId();
//            cout << " ";
//            cout << it1->second->getId();
//            cout << " ";
//            cout << it1->first << endl;
//        }
//        for (vector<pair<string, NFAState *> >::const_iterator it2 = u.begin(); it2 != u.end(); it2++) {
//            cout << it->second->getId();
//            cout << " ";
//            cout << it2->second->getId();
//            cout << " ";
//
//            cout << it2->first << endl;
//
//        }
//        cout<<"DONE"<<endl;
//    }
//    cout<<"botato"<<endl;
//    for (const auto &element: this->get_input_table()) {
//        cout<<element<<endl;
//    }
    global_states.clear();
    return start_state;
}

/**
 Takes a transition an constructs an nfa state with a start and ending states using thompson rule
 @return an NFAState ponter representing the start state a single transition
*/
NFAState *
NFA::construct_one_transition_state(string transition, unordered_map<NFAState *, NFAState *> *start_to_acceptance_map,
                                    bool final_finish_state) {
    NFAState *start_state = new NFANormalState();
    NFAState *finish_state = this->acceptance_state_generator(final_finish_state);
    transition = resolve_backslash(transition);
    start_state->add_neighbour(transition, finish_state);
    start_to_acceptance_map->insert(pair<NFAState *, NFAState *>(start_state, finish_state));
    global_states.push_back(pair<NFAState *, NFAState *>(start_state, finish_state));
    return start_state;
}

/**
 Converts the postfix to NFA by iterating over the chracters of the postfix and distinguishing whether
 it is an operand or an operator and based on that it constructs the nfa state for each operator using thompson rules
 @return an NFAState ponter representing the start state an NFA of a regex
*/
NFAState *NFA::postfix_to_NFA(string postfix, unordered_set<string> input_table, string regex_name,int priority) {
    stack<NFAState *> nfa_state_stack;
    unordered_map<NFAState *, NFAState *> start_to_acceptance_map;
    bool input_acceptor = false;
    bool final_finish_state = false;
    string input_identifier = "";
    // Scan all characters one by one
    int i = 0;
    do {


        // If the scanned character is an operand (number here),
        // push it to the stack.
        if (!isOperator(postfix[i])) {
            while (input_acceptor == false) {
                input_identifier += postfix[i];
                for (const auto &element: input_table) {
                    if (input_identifier.compare(element) == 0) {
                        nfa_state_stack.push(
                                this->construct_one_transition_state(input_identifier, &start_to_acceptance_map,
                                                                     final_finish_state));
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
        else if (isOperator(postfix[i])) {

            switch (postfix[i]) {
                case POSITIVE_CLOSURE_OPERATOR: {
                    NFAState *plus_nfa_state = this->kleene_and_plus(nfa_state_stack.top(), &start_to_acceptance_map,
                                                                     false, final_finish_state);
                    nfa_state_stack.pop();
                    nfa_state_stack.push(plus_nfa_state);
                    break;
                }
                case KLEENE_CLOSURE_OPERATOR: {
                    NFAState *kleene_nfa_state = this->kleene_and_plus(nfa_state_stack.top(), &start_to_acceptance_map,
                                                                       true, final_finish_state);
                    nfa_state_stack.pop();
                    nfa_state_stack.push(kleene_nfa_state);
                    break;
                }
                case UNION_OPERATOR: {
                    NFAState *second_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    NFAState *first_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    nfa_state_stack.push(this->or_combiner(first_operand_union_state, second_operand_union_state,
                                                           &start_to_acceptance_map, final_finish_state));
                    break;
                }
                case CONCAT_OPERATOR: {
                    NFAState *second_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();

                    NFAState *first_operand_union_state = nfa_state_stack.top();

                    nfa_state_stack.pop();
                    nfa_state_stack.push(this->concat(first_operand_union_state, second_operand_union_state,
                                                      &start_to_acceptance_map, final_finish_state));
                    break;
                }

            }
        }

        i++;

    } while (nfa_state_stack.size() >= 1 && i < postfix.size());
    //Adding the start and acceptance states of the final nfa to the global combined nfa map
    NFAState *acceptance = new NFAAcceptanceState();
    NFAAcceptanceState *acceptance_state = dynamic_cast<NFAAcceptanceState *>(acceptance);

    global_states[global_states.size() - 1].second->add_neighbour(EPSILON, acceptance_state);
    acceptance_state->set_token(regex_name);
    acceptance_state->set_priority(priority);
    combined_nfa_states.push_back(pair<NFAState *, NFAState *>(nfa_state_stack.top(), acceptance_state));



    return nfa_state_stack.top();
}

/**
 Takes a transition and 2 NFAStates representing the start of each state and constructs an nfa state with a start and ending states using thompson rule
 @return an NFAState ponter representing the start state the uniuond transition
*/
NFAState *NFA::or_combiner(NFAState *first_nfa_state, NFAState *second_nfa_state,
                           unordered_map<NFAState *, NFAState *> *start_to_acceptance_map, bool final_finish_state) {
    //Initilaizing a start and acceptance node for the union thompson rule
    NFAState *start_state = new NFANormalState();
    NFAState *finish_state = this->acceptance_state_generator(final_finish_state);
    //Adding 2 neighbours from the start node with a transition epsilon where the neighbours are the 2 start nodes of the unioned nfa's
    start_state->add_neighbour(EPSILON, first_nfa_state);
    start_state->add_neighbour(EPSILON, second_nfa_state);
    //Getting the finish states of the unioned nfa's and adding the finsih state of the resulting nfa as their neigbhours with a transition epsilon
    unordered_map<NFAState *, NFAState *>::iterator it = start_to_acceptance_map->begin();
    for (std::pair<NFAState *, NFAState *> element : *start_to_acceptance_map) {
        if (element.first == first_nfa_state || element.first == second_nfa_state) {
            (element.second)->add_neighbour(EPSILON, finish_state);
        }
    }
//    for (vector<pair<NFAState *, NFAState *> >::const_iterator it = start_to_acceptance_map->begin();
//         it != start_to_acceptance_map->end(); it++) {
//        if (it->first == first_nfa_state || it->first == second_nfa_state) {
//            (it->second)->add_neighbour(EPSILON, finish_state);
//        }
//    }
    //Adding the first and finish states to the map
    start_to_acceptance_map->insert(pair<NFAState *, NFAState *>(start_state, finish_state));
    global_states.push_back(pair<NFAState *, NFAState *>(start_state, finish_state));

    return start_state;
}

/**
 Takes a transition and 2 NFAStates representing the start of each state and constructs an nfa state with a start and ending states using thompson rule
 Based on the kleene boolean it constucts a different state in case it is a plus opeartor
 @return an NFAState pointer representing the start state the kleene or plus operation
*/
NFAState *
NFA::kleene_and_plus(NFAState *nfa_state, unordered_map<NFAState *, NFAState *> *start_to_acceptance_map, bool kleene,
                     bool final_finish_state) {
    NFAState *start_state = new NFANormalState();
    NFAState *finish_state = this->acceptance_state_generator(final_finish_state);
    //Adding an epsilon transition from the new start state to 1-) the start state of the old nfa 2-)the finish state of the new nfa
    start_state->add_neighbour(EPSILON, nfa_state);
    //In case it is a kleene operator add an epsilon transition from the start state to the accept state
    //In case it is a plus operator do nothing
    if (kleene == true) {
        start_state->add_neighbour(EPSILON, finish_state);
    }
    //getting the start and finish states of the old nfa and making 2 transitions
    //1-)epsilon from the finsih state of the old to the start state of the old
    //2-)epsilon from the finish state of the old to the finish state of the the new
    unordered_map<NFAState *, NFAState *>::iterator it = start_to_acceptance_map->begin();
    for (std::pair<NFAState *, NFAState *> element : *start_to_acceptance_map) {
        if (element.first == nfa_state) {
            (element.second)->add_neighbour(EPSILON, finish_state);
            (element.second)->add_neighbour(EPSILON, element.first);
            break;
        }
    }

    //Adding the first and finish states of the new nfa to the map
    start_to_acceptance_map->insert(pair<NFAState *, NFAState *>(start_state, finish_state));
    global_states.push_back(pair<NFAState *, NFAState *>(start_state, finish_state));

    return start_state;
}

/**
 Takes a transition and 2 NFAStates representing the start of each state and constructs an nfa state with a start and ending states using thompson rule
 @return an NFAState ponter representing the start state the concated operation
*/
NFAState *NFA::concat(NFAState *first_nfa_state, NFAState *second_nfa_state,
                      unordered_map<NFAState *, NFAState *> *start_to_acceptance_map, bool final_finish_state) {
    NFAState *first_nfa_acceptance_state;
    vector<pair<string, NFAState *>> temp_vector;

    int iterator = 0;
    unordered_map<NFAState *, NFAState *>::iterator it = start_to_acceptance_map->begin();
    for (std::pair<NFAState *, NFAState *> element : *start_to_acceptance_map) {
        //Save the address of the acceptance state of the first concatinated inorder to add the neigbhours of the start state of the second concatinated nfa
        if (first_nfa_state == element.first) {
            for (std::pair<NFAState *, NFAState *> element1 : *start_to_acceptance_map) {
                if ((element1.first) == second_nfa_state) {

                    start_to_acceptance_map->erase(first_nfa_state);
                    start_to_acceptance_map->insert(pair<NFAState *, NFAState *>(first_nfa_state, element1.second));
                    element.second->add_neighbour(EPSILON, second_nfa_state);
                    global_states.push_back(pair<NFAState *, NFAState *>(first_nfa_state, element1.second));

                    iterator++;
                }
            }
            iterator++;
        }
        //Get the neighbours of the start state of the second concatinated nfa inorder to add the neighbours to the acceptance state of the first concatinted nfa

        if (iterator == 2) {
            break;
        }
    }

    return first_nfa_state;
}

/**
Check if a transition has a backslash,if yes then trancate the backslash from the string else return the string without change
@return string with no backslash
*/
std::string NFA::resolve_backslash(std::string transition) {

    if (transition.find(ESCAPE_CHARACTER) != string::npos) {
        if (transition[1] != 'L')
            transition.erase(0, 1);
    }
    return transition;

}

/**
Handling the input table by removing all the backslashes from the input table inorder to sync with the transitioned data between states
 @return string with no backslash
*/
unordered_set<string> NFA::resolve_input_table(unordered_set<string> input_table) {
    unordered_set<string> editted_input_table;
    for (const auto &element: input_table) {
if(element==EPSILON){
continue;
}
else{
    editted_input_table.insert(this->resolve_backslash(element));
}
    }
    return editted_input_table;
}

/**
 Checks the final boolean state and returns an NFAAcceptanceState if boolean is true,else it returns an NFANormalState
 @return NFAState pointer of type Normal State or Acceptance State
*/
NFAState *NFA::acceptance_state_generator(bool final_finish_state) {
    if (!final_finish_state) {
        return new NFANormalState();
    } else {
        return new NFAAcceptanceState();
    }
}

/**
 Checks if the character is an operator or not
 @return a boolean indicating if it is a character or not
*/
bool NFA::isOperator(char character) {
    if (character == UNION_OPERATOR || character == KLEENE_CLOSURE_OPERATOR || character == POSITIVE_CLOSURE_OPERATOR ||
        character == CONCAT_OPERATOR) {
        return true;
    }
    return false;
}

/**
 Getter for the input_table
 @return unordered_set of type string
*/
unordered_set<string> NFA::get_input_table() {
    return this->input_table;
}

/**
 Sets the input table
 @return void
*/
void NFA::set_input_table(unordered_set<string> input_table) {
    this->input_table = input_table;
}


