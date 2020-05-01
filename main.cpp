#include <queue>
#include <unordered_set>
//#include "lexgen/nfa.h"
//#include "lexgen/dfa.h"
//#include "lexgen/language_parser.h"
//#include "lexgen/nfa_state.h"
#include <iostream>

#include "prsgen/non_terminal.h"

#include "prsgen/grammar_parser.h"

using namespace std;

int main() {

//    auto language_parser = new LanguageParser();
//    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
//    NFA x = NFA();
//    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
//    DFA dfa_gen = DFA();
//    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
	GrammarParser *X = new GrammarParser();
	
	
	NonTerminal* A = new NonTerminal("A");

	std::vector<std::vector<std::string> > prodrules;
	
	std::vector<std::string> tmp;
	tmp.push_back("A");
	tmp.push_back("C");
	prodrules.push_back(tmp);
	
	std::vector<std::string> tmp2;
	tmp2.push_back("S");
	tmp2.push_back("d");
	
	prodrules.push_back(tmp2);
		 
	std::vector<std::string> tmp3;
	tmp3.push_back("f");
	
	prodrules.push_back(tmp3);



	A->setProduction_rules_(prodrules);


	NonTerminal* S = new NonTerminal("S");

	prodrules.clear();

	tmp.clear();
	tmp.push_back("A");
	tmp.push_back("a");
	prodrules.push_back(tmp);

	 tmp2.clear();
	tmp2.push_back("b");

	prodrules.push_back(tmp2);





	S->setProduction_rules_(prodrules);



	//cout << X->checkImmediateLeftRecursion(A);
//	X->eliminateImmediateLeftRecursion(A);

	X->subsitution(A, S);


    return 0;
}