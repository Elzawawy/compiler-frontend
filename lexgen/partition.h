

#ifndef LEXGEN_PARTITION_H
#define LEXGEN_PARTITION_H

#include <vector>
#include <unordered_map>
#include <iterator>
#include "dfa_state.h"
using namespace std;

class Partition{

public:
	void remove(DFAState * state);
	void add(DFAState * state);
	vector<DFAState *> getMembers();
	void displayStates();
	explicit Partition();
	explicit Partition(string partitionSymbol);
	int getId();
	string getPartitionsymbol();
	void setPartitionsymbol(string symbol);
	

private:
	int partitionId;
	vector<DFAState *> members;
	string partitionSymbol;



};


#endif //LEXGEN_NFASTATE_H