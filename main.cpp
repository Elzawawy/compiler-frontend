#include <queue>
#include <unordered_set>
#include "lexgen/nfa.h"
#include "lexgen/dfa.h"
#include "lexgen/language_parser.h"
#include "lexgen/nfa_state.h"
#include "lexgen/lexical_analyzer_driver.h"
#include "prsgen/non_terminal.h"
#include "prsgen/predictive_parser.h"

using namespace std;

int main() {

    auto language_parser = new LanguageParser();
    language_parser->parseFile(
            "/home/mostafayousry/TERM10/Programming Languages Translation/Assignments/LEXGEN/lexgen/test_cases/case_1/b_lexical_rules.txt");
    NFA x = NFA();
    NFAState *nfa_start_state = x.regex_to_nfa(language_parser->getInput_table(), language_parser->getExpressions());
    DFA dfa_gen = DFA();
    DFAState *dfa_start_state = dfa_gen.GenerateDFA(*nfa_start_state, x.get_input_table());
    LexicalAnalyzerDriver lexicalAnalyzerDriver(dfa_start_state,
                                                "/home/mostafayousry/TERM10/Programming Languages Translation/Assignments/LEXGEN/lexgen/test_cases/case_1/b_test_program.txt",
                                                language_parser->getExpressions());

//    set<string> ex = lexicalAnalyzerDriver.GetRegularExpressionsNames();
//    for (string x : ex) {
//        cout << x << endl;
//    }
        set<string> terminals{"id", "+", "*", "(", ")", "$"};
    NonTerminal e = NonTerminal("E");
    NonTerminal e_ = NonTerminal("E\'");
    NonTerminal t = NonTerminal("T");
    NonTerminal t_ = NonTerminal("T\'");
    NonTerminal f = NonTerminal("F");

    vector<vector<string>> e_parsing_row{
            {"T", "E\'"}
    };
    vector<vector<string>> e_prime_parsing_row{
            {"+", "T", "E\'"},
            {"\\L"}
    };
    vector<vector<string>> t_parsing_row{
            {"F", "T\'"}
    };
    vector<vector<string>> t_prime_parsing_row{
            {"*", "F", "T\'"},
            {"\\L"}
    };
    vector<vector<string>> f_parsing_row{
            {"(", "E", ")"},
            {"id"}
    };

    e.setProduction_rules_(e_parsing_row);
    e_.setProduction_rules_(e_prime_parsing_row);
    t.setProduction_rules_(t_parsing_row);
    t_.setProduction_rules_(t_prime_parsing_row);
    f.setProduction_rules_(f_parsing_row);


    map<string, int> e_table_entry{
            {"id", 0},
            {"(",  0},
            {"$",  -1},
            {")",  -1},
            {"+",  -2},
            {"*",  -2}
    };

    map<string, int> e_prime_table_entry{
            {"id", -2},
            {"(",  -2},
            {"$",  1},
            {")",  1},
            {"+",  0},
            {"*",  -2}
    };
    map<string, int> t_table_entry{
            {"id", 0},
            {"(",  0},
            {"$",  -1},
            {")",  -1},
            {"+",  -1},
            {"*",  -2}
    };
    map<string, int> t_prime_table_entry{
            {"id", -2},
            {"(",  -2},
            {"$",  1},
            {")",  1},
            {"+",  1},
            {"*",  0}
    };
    map<string, int> f_table_entry{
            {"id", 1},
            {"(",  0},
            {"$",  -1},
            {")",  -1},
            {"+",  -1},
            {"*",  -1}
    };


    e.setParse_table_entry_(e_table_entry);
    e_.setParse_table_entry_(e_prime_table_entry);
    t.setParse_table_entry_(t_table_entry);
    t_.setParse_table_entry_(t_prime_table_entry);
    f.setParse_table_entry_(f_table_entry);

    map<string, NonTerminal> non_terminals{
            {"E",   e},
            {"E\'", e_},
            {"T",   t},
            {"T\'", t_},
            {"F",   f}
    };

    PredicativeParser predicativeParser = PredicativeParser(lexicalAnalyzerDriver, non_terminals, terminals,
                                                            "/home/mostafayousry/TERM10/Programming Languages Translation/Assignments/LEXGEN/output.txt");

    predicativeParser.Parse();

//    while (true) {
//        cout << lexicalAnalyzerDriver.GetNextToken()->GetTokenName() << endl;
//    }
    return 0;
}