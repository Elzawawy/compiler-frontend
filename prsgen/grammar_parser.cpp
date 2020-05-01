//
// Created by zawawy on 4/21/20.
//

#include <iostream>
#include "grammar_parser.h"
const std::set<std::string>& GrammarParser::getTerminals_() const
{
    return terminals_;
}
const std::vector<NonTerminal>& GrammarParser::getNon_terminals_() const
{
    return non_terminals_;
}

void GrammarParser::parseFile(std::string file_name)
{
    //TODO: PRSGEN-2
}

void GrammarParser::eliminateRightFactoring()
{
    //TODO: PRSGEN-3
}
void GrammarParser::eliminateLeftFactoring()
{
    for(auto non_terminal:this->non_terminals_){
        std::vector<std::vector<std::string>> production_rules=non_terminal.getProduction_rules_();
        std::unordered_map<std::string, std::vector<int>> factoring_map;
        std::vector<int> factored_index;
        /**
         *  iterating over the production rules and getting the common starts and marking them as factors to be
         *  factorized in the next loop
         */
        for(int index=0;index<production_rules.size();index++){
            std::cout<<((production_rules[index])[0])<<std::endl;

            /**if the start of the production rule is not present in the factoring map
             * then add a new key in the factoring map with the new start of this production rule and add the index of the
             * production rule as the first element in the array of values of the factoring map
             */
            if(factoring_map.find((production_rules[index])[0])==factoring_map.end()){
                factored_index.push_back(index);
                factoring_map.insert({(production_rules[index])[0],factored_index});

            }
                /**if the start of the production rule is present in the factoring map which means that it should be factore
                 * then push the index of the production rule in the array of the value of the map
                 */
            else{
                std::unordered_map<std::string, std::vector<int>>::iterator it = factoring_map.find((production_rules[index])[0]);
                (it->second).push_back(index);
            }
        }
        /**
         *   Looping over the factoring map and creating new non terminals if needed by checking each array value in the map
         *   and using their indices to factor the common production rules
         */
        std::unordered_map<std::string, std::vector<int>>::iterator it = factoring_map.begin();
        for (std::pair<std::string, std::vector<int>> element : factoring_map) {

        }
    }


}