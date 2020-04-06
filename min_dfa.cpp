#include <iostream>
#include <fstream>
#include <string>
#include "dfa_state.h"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include<algorithm>
#include "partition.h"

#include<sstream>


vector<Partition *> partitions;
vector<string> symbolList;

std::vector<string> transitionsEnumerator(DFAState *root) {

    unordered_map<string, DFAState *> neighbours = root->get_neighbours();
    unordered_map<string, DFAState *>::iterator neighboursIterator = neighbours.begin();

    //enumerate all possible transitions
    std::vector<string> transitions;
    while (neighboursIterator != neighbours.end()) {

        transitions.push_back(neighboursIterator->first);
        neighboursIterator++;
    }
    return transitions;

}

string getPartition(DFAState *state) {
    vector<Partition *>::iterator partitionsIterator;

    for (partitionsIterator = partitions.begin(); partitionsIterator < partitions.end(); partitionsIterator++) {
        vector<DFAState *> members = (*partitionsIterator)->getMembers();
        vector<DFAState *>::iterator membersIterator = members.begin();
        for (membersIterator = members.begin(); membersIterator < members.end(); membersIterator++) {
            if ((*membersIterator) == state) {
                stringstream ss;
                ss << (*partitionsIterator)->getId();
                string s;
                ss >> s;
                return s;


            }

        }

    }

    return "";

}

template<typename T>
void remove_duplicates(std::vector<T> &vec) {
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

void setMark(unordered_set<DFAState *> listofstates) {
    vector<Partition *>::iterator partitionsIterator;

    for (partitionsIterator = partitions.begin(); partitionsIterator < partitions.end(); partitionsIterator++) {
        vector<DFAState *> members = (*partitionsIterator)->getMembers();
        vector<DFAState *>::iterator membersIterator = members.begin();
        for (membersIterator = members.begin(); membersIterator < members.end(); membersIterator++) {
            unordered_map<string, DFAState *> neigbours = (*membersIterator)->get_neighbours();
            unordered_map<string, DFAState *>::iterator neighboursItr = neigbours.begin();
            string symbol = "";

            while (neighboursItr != neigbours.end()) {

                DFAState *neighbour = neighboursItr->second;

                symbol += getPartition(neighbour) + ",";
                neighboursItr++;
            }
            symbol = symbol + (*partitionsIterator)->getPartitionsymbol();
            (*membersIterator)->setCombiningsymbol(symbol);
            symbolList.push_back(symbol);
        }
    }
    remove_duplicates(symbolList);


}


DFAState ***constructTransitiontable(DFAState *root, unordered_set<DFAState *> listofstates) {
    unordered_map<string, DFAState *> neighbours = root->get_neighbours();
    unordered_map<string, DFAState *>::iterator neighboursIterator = neighbours.begin();
    std::vector<string> transitions = transitionsEnumerator(root);
/*
	//enumerate all possible transitions
	std::vector<string> transitions;
	while (neighboursIterator != neighbours.end())
	{
		
		transitions.push_back(neighboursIterator->first);
		neighboursIterator++;
	}*/


    //Construct the transition table

    DFAState ***matrix = new DFAState **[listofstates.size()]; // each element is a pointer to an array.

    unordered_set<DFAState *>::iterator statesIterator = listofstates.begin();
    for (size_t i = 0; i < listofstates.size(); ++i)
        matrix[i] = new DFAState *[transitions.size()]; // build rows
    //cout	<< listofstates.size()<<endl;
    std::ofstream transition_table_file;
    transition_table_file.open("../output/transition_table.csv");
    transition_table_file << " ";
    for (auto &&input: transitions) {
        transition_table_file << input << " ";
    }
    transition_table_file << "\n";
    for (size_t stateIndex = 0; stateIndex < listofstates.size(); stateIndex++) {
        transition_table_file << (*statesIterator)->get_id() << " ";
        for (size_t transitionIndex = 0; transitionIndex < transitions.size(); transitionIndex++) {
            unordered_map<string, DFAState *> currentNeighbour = (*statesIterator)->get_neighbours();
            matrix[stateIndex][transitionIndex] = currentNeighbour[transitions[transitionIndex]];

            transition_table_file << currentNeighbour[transitions[transitionIndex]]->get_id() << " ";
        }
        transition_table_file << "\n";
        statesIterator++;
    }
    transition_table_file.close();
    return matrix;
    //dont forget to remove matrix if unused
    /*for(size_t i = 0; i < N; i++)
    delete matrix[i];

delete matrix;*/


}

/*
Myhill Nerode Algorithm failed :)

bool **   createFillingtable(DFAState* root, unordered_set<DFAState *> listofstates)
{
       //building the base of filling table with accept state xoring mechanism values
       bool ** matrix = new bool*[listofstates.size()]; // each element is a pointer to an array.
       unordered_set<DFAState *>::iterator rowsIterator = listofstates.begin();
       unordered_set<DFAState *>::iterator columnsIterator = listofstates.begin();
       for (size_t i = 0; i < listofstates.size(); i++)
           matrix[i] = new bool[listofstates.size()]; // build rows

       for (size_t rawIndex = 0; rawIndex < listofstates.size(); rawIndex++)
       {
           //cout << (*rowsIterator)->getId() << ' ';

           for (size_t columnIndex = 0; columnIndex < listofstates.size(); columnIndex++)
           {

               matrix[rawIndex][columnIndex] = (*rowsIterator)->isAccepting_state()^ (*columnsIterator)->isAccepting_state();
               cout << matrix[rawIndex][columnIndex];
               columnsIterator++;
           }
           cout << endl;
           columnsIterator = listofstates.begin();
           rowsIterator++;
       }
       return matrix;
}

bool **   fillTable(DFAState* root ,bool ** fillingTable, unordered_set<DFAState *> listofstates)
{
    unordered_set<DFAState *>::iterator rowsIterator = listofstates.begin();
    unordered_set<DFAState *>::iterator columnsIterator = listofstates.begin();
    std::vector<string> transitions = transitionsEnumerator(root);

    for (size_t i = 0; i < listofstates.size(); i++)
    {


        for (size_t j = 0; j < i; j++)
        {

            if (fillingTable[i][j] == false)	//skip true cases
            {
                //fillingTable[i][j] = true;
                //cout << fillingTable[i][j];


            }

            columnsIterator++;
        }
        cout << endl;
        columnsIterator = listofstates.begin();
        rowsIterator++;
    }

    return fillingTable;
}


bool checkNeighbours(DFAState * rowState, DFAState * columnState  , bool ** fillingTable )
{
    std::vector<string> transitions = transitionsEnumerator(rowState);

    for (size_t transitionIndex = 0; transitionIndex < transitions.size(); transitionIndex++)
    {
        unordered_map<string, DFAState *> rowNeigbours = rowState->getNeighbours();
        unordered_map<string, DFAState *>  columnNeigbours = columnState->getNeighbours();


    }
}

*/
void putProperPartition(DFAState *State) {

    vector<Partition *>::iterator partitionsIterator;

    for (partitionsIterator = partitions.begin(); partitionsIterator < partitions.end(); partitionsIterator++) {
        if (State->getCombiningsymbol().compare((*partitionsIterator)->getPartitionsymbol()) == 0)
            (*partitionsIterator)->add(State);

    }


}


unordered_set<DFAState *> partitioning(DFAState ***transitionTable, unordered_set<DFAState *> listofstates) {

    Partition *accept = new Partition("x");
    Partition *normal = new Partition("y");
    partitions.push_back(normal);
    partitions.push_back(accept);
    //first step is to classify states to 2 states_partitions
    for (unordered_set<DFAState *>::iterator itr = listofstates.begin(); itr != listofstates.end(); itr++) {

        if ((*itr)->IsAcceptingState())
            accept->add((*itr));
        else
            normal->add((*itr));


    }


    int oldParitionsize = 0;
    while (oldParitionsize != partitions.size()) {
        oldParitionsize = partitions.size();
        //mark all states with combining symbols
        setMark(listofstates);
        //create new states_partitions equal to # of symbols and link them to states_partitions list
        for (size_t i = 0; i < symbolList.size(); i++) {
            partitions.push_back(new Partition((*(symbolList.begin() + i))));

        }
        //iterate through old states_partitions and put every state in the proper partition
        vector<Partition *>::iterator partitionsIterator = partitions.begin();

        for (size_t i = 0; i < partitions.size() - symbolList.size(); i++) {
            vector<DFAState *> members = (*partitionsIterator)->getMembers();
            vector<DFAState *>::iterator membersIterator = members.begin();

            for (size_t j = 0; j < (*partitionsIterator)->getMembers().size(); j++) {
                //	DFAState * currentState = ;
                putProperPartition((*membersIterator));


                membersIterator++;
            }

            partitionsIterator++;
        }

        //remove old paritions
        partitionsIterator = partitions.begin();
        int partSize = partitions.size();
        for (size_t i = 0; i < partSize - symbolList.size(); i++)
            partitionsIterator = partitions.erase(partitionsIterator);

        symbolList.clear();

    }
    vector<Partition *>::iterator partitionsIterator;
    unordered_set<DFAState *> newDFA;
    //set euiv states property to all states
    for (partitionsIterator = partitions.begin(); partitionsIterator < partitions.end(); partitionsIterator++) {
        {

            vector<DFAState *> members = (*partitionsIterator)->getMembers();
            vector<DFAState *>::iterator membersIterator = members.begin();
            DFAState *equivState = (*membersIterator);
            newDFA.insert(equivState);
            for (membersIterator = members.begin(); membersIterator < members.end(); membersIterator++) {
                (*membersIterator)->setEquivstate(equivState);
            }
        }
    }

    //setting neighbours for the minimized dfa to their equivilant
    for (size_t i = 0; i < newDFA.size(); i++) {
        unordered_set<DFAState *>::iterator statesIterator;
        //iterate through neighbours
        for (statesIterator = newDFA.begin(); statesIterator != newDFA.end(); statesIterator++) {
            unordered_map<string, DFAState *> neighbours = (*statesIterator)->get_neighbours();
            unordered_map<string, DFAState *>::iterator neighboursIterator = neighbours.begin();
            for (neighboursIterator = neighbours.begin();
                 neighboursIterator != neighbours.end(); neighboursIterator++) {
                (*statesIterator)->UpdateNeighbours((neighboursIterator)->first,
                                                    (neighboursIterator)->second->getEquivstate());

            }


        }


    }

    return newDFA;
}



//it returns the symbol generated from id transitions of neighbours

//it returns the partition id of the given state
