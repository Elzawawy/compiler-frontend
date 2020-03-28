#include <iostream>
#include <string>
#include "dfa_state.h"
#include "min_dfa.cpp"
#include <unordered_set>

int main() {
	/*
	DFAState * q0 = new DFAState(false);
	DFAState * q1 = new DFAState(false);
	DFAState * q2 = new DFAState(true);
	DFAState * q3 = new DFAState(false);
	DFAState * q4 = new DFAState(false);
	DFAState * q5 = new DFAState(false);
	DFAState * q6 = new DFAState(false);
	DFAState * q7 = new DFAState(false);

	q0->add_neighbour("0", q1);
	q0->add_neighbour("1", q5);

	q1->add_neighbour("0", q6);
	q1->add_neighbour("1", q2);

	q2->add_neighbour("0", q0);
	q2->add_neighbour("1", q2);

	q3->add_neighbour("0", q2);
	q3->add_neighbour("1", q6);

	q4->add_neighbour("0", q7);
	q4->add_neighbour("1", q5);

	q5->add_neighbour("0", q2);
	q5->add_neighbour("1", q6);

	q6->add_neighbour("0", q6);
	q6->add_neighbour("1", q4);

	q7->add_neighbour("0", q6);
	q7->add_neighbour("1", q2);




	unordered_set<DFAState *> list;
	
	list.insert(q0);
	list.insert(q1);
	list.insert(q2);
	list.insert(q3);
	list.insert(q4);
	list.insert(q5);
	list.insert(q6);
	list.insert(q7);
	www.youtube.com/watch?v=ex9sPLq5CRg
	*/



	//www.youtube.com/watch?v=DV8cZp-2VmM

	DFAState * A = new DFAState(false);
	DFAState * B = new DFAState(false);
	DFAState * C = new DFAState(true);
	DFAState * D = new DFAState(true);
	DFAState * E = new DFAState(true);
	DFAState * F = new DFAState(false);

	A->add_neighbour("0", B);
	A->add_neighbour("1", C);

	B->add_neighbour("0", A);
	B->add_neighbour("1", D);

	C->add_neighbour("0", E);
	C->add_neighbour("1", F);

	D->add_neighbour("0", E);
	D->add_neighbour("1", F);

	E->add_neighbour("0", E);
	E->add_neighbour("1", F);

	F->add_neighbour("0", F);
	F->add_neighbour("1", F);

	unordered_set<DFAState *> list;

	list.insert(A);
	list.insert(B);
	list.insert(C);
	list.insert(D);
	list.insert(E);
	list.insert(F);
	

	unordered_set<DFAState *>  newDFA = partitioning(constructTransitiontable(A, list), list);
	constructTransitiontable(*(newDFA.begin()), newDFA);
	
	
	//fillTable(A, createFillingtable(A, list), list);
	

    return 0;
}