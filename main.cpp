#include <queue>
#include <unordered_set>
#include "lexgen/nfa.h"
#include "lexgen/dfa.h"
#include "lexgen/language_parser.h"
#include "lexgen/nfa_state.h"
#include "lexgen/lexical_analyzer_driver.h"
#include "prsgen/grammar_parser.h"

using namespace std;

int main() {

//    auto language_parser = new LanguageParser();
//    language_parser->parseFile(
//            "./lexgen/test_cases/case_1/b_lexical_rules.txt");
//    NFA x = NFA();
//    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
//    DFA dfa_gen = DFA();
//    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());

//    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state, "./lexgen/test_cases/case_1/b_test_program.txt",
//                                                language_parser->getExpressions());

    GrammarParser *X = new GrammarParser();

    /*
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


    std::vector<NonTerminal *> terminals;
    terminals.push_back(S);
    terminals.push_back(A);
    //cout << X->checkImmediateLeftRecursion(A);
//	X->eliminateImmediateLeftRecursion(A);

//	X->subsitution(A, S);
    X->eliminateLeftRecursion(terminals);
    */
//
//	NonTerminal* S = new NonTerminal("S");
//
//	std::vector<std::vector<std::string> > prodrules;
//
//	std::vector<std::string> tmp2;
//	std::vector<std::string> tmp3;
//	std::vector<std::string> tmp;
//	tmp.push_back("E");
//	prodrules.push_back(tmp);
//	S->setProduction_rules_(prodrules);
//
//
//	NonTerminal* E = new NonTerminal("E");
//
//	prodrules.clear();
//
//	tmp.clear();
//	tmp.push_back("E");
//	tmp.push_back("+");
//	tmp.push_back("T");
//	prodrules.push_back(tmp);
//
//	tmp2.clear();
//	tmp2.push_back("T");
//
//	prodrules.push_back(tmp2);
//
//	E->setProduction_rules_(prodrules);
//
//
//	NonTerminal* T = new NonTerminal("T");
//
//	prodrules.clear();
//
//	tmp.clear();
//	tmp.push_back("E");
//	tmp.push_back("-");
//	tmp.push_back("T");
//	prodrules.push_back(tmp);
//
//	tmp2.clear();
//	tmp2.push_back("F");
//
//	prodrules.push_back(tmp2);
//
//	T->setProduction_rules_(prodrules);
//
//	NonTerminal* F = new NonTerminal("F");
//
//	prodrules.clear();
//
//	tmp.clear();
//	tmp.push_back("E");
//	tmp.push_back("*");
//	tmp.push_back("F");
//	prodrules.push_back(tmp);
//
//	tmp2.clear();
//	tmp2.push_back("id");
//
//	prodrules.push_back(tmp2);
//
//	F->setProduction_rules_(prodrules);
//
//
//	std::vector<NonTerminal > terminals;
//	terminals.push_back(*S);
//	terminals.push_back(*E);
//	terminals.push_back(*T);
//	terminals.push_back(*F);
//
//
//
//	 X->eliminateLeftRecursion(terminals);



    //TEST CASE LINK
    return 0;
}