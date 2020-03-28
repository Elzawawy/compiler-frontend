#include "partition.h"
#include <vector>
#include <iterator>
#include "dfa_state.h"
#include <iostream>

using namespace std;

void Partition::remove(DFAState * state)
{
	
	for (auto itr = members.begin(); itr != members.end(); itr++) {
		if ((*itr) == state)
		{
			this->members.erase(itr);
			break;
		}
	}

	
	
}

void Partition::add(DFAState * state)
{
	this->members.push_back(state);
}

vector<DFAState*> Partition::getMembers()
{
	return members;
}

void Partition::displayStates()
{
	for (std::size_t i = 0; i<members.size(); ++i)
		std::cout << members[i]->getId() << ' ';

	cout << endl;

}
static int id_counter = 0;
Partition::Partition() {

	
	partitionId = id_counter++;
	partitionSymbol = "";

}

Partition::Partition(string pSymbol)
{
	partitionId = id_counter++;
	partitionSymbol = pSymbol;
}

int Partition::getId()
{
	return this->partitionId;
}

string Partition::getPartitionsymbol()
{
	return partitionSymbol;
}

void Partition::setPartitionsymbol(string symbol)
{
	this->partitionSymbol = symbol;
}




