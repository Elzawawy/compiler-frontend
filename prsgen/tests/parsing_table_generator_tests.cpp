//
// Created by omar_swidan on 27/04/20.
//
#include <iostream>
#include "../../catch.h"
#include "../non_terminal.h"
#include "../parsing_table_generator.h"

using namespace std;

TEST_CASE("Creating First and Follow Sets") {
    NonTerminal n1("E");
    NonTerminal n2("E`");
    NonTerminal n3("T");
    NonTerminal n4("T`");
    NonTerminal n5("F");
    n1.setProduction_rules_(vector<vector<string>>{{"T", "E`"}});
    n2.setProduction_rules_(vector<vector<string>>{{"+", "T", "E`"},
                                                   {"\\L"}});
    n3.setProduction_rules_(vector<vector<string>>{{"F", "T`"}});
    n4.setProduction_rules_(vector<vector<string>>{{"*", "F", "T`"},
                                                   {"\\L"}});
    n5.setProduction_rules_(vector<vector<string>>{{"(", "E", ")"},
                                                   {"id"}});
    unordered_set<string> terminals{"+", "*", "(", ")", "id"};
    vector<NonTerminal> non_terminals{n1, n2, n3, n4, n5};
    ParsingTableGenerator parsingTableGenerator(terminals, non_terminals);
    parsingTableGenerator.computeFirst();
    parsingTableGenerator.computeFollow();

    for (auto &&non_terminal: non_terminals) {
        cout << non_terminal.getName_() << " first set: ";
        for (auto &&element: non_terminal.getFirst_()) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << "=========================================================" << endl;
    for (auto &&non_terminal: non_terminals) {
        cout << non_terminal.getName_() << " follow set: ";
        for (auto &&element: non_terminal.getFollow_()) {
            cout << element << " ";
        }
        cout << endl;
    }

};

TEST_CASE("Parsing Table Test Slides Example") {
    NonTerminal n1("E");
    NonTerminal n2("E`");
    NonTerminal n3("T");
    NonTerminal n4("T`");
    NonTerminal n5("F");
    n1.setProduction_rules_(vector<vector<string>>{{"T", "E`"}});
    n2.setProduction_rules_(vector<vector<string>>{{"+", "T", "E`"},
                                                   {"\\L"}});
    n3.setProduction_rules_(vector<vector<string>>{{"F", "T`"}});
    n4.setProduction_rules_(vector<vector<string>>{{"*", "F", "T`"},
                                                   {"\\L"}});
    n5.setProduction_rules_(vector<vector<string>>{{"(", "E", ")"},
                                                   {"id"}});
    unordered_set<string> terminals{"+", "*", "(", ")", "id"};
    vector<NonTerminal> non_terminals{n1, n2, n3, n4, n5};
    ParsingTableGenerator parsingTableGenerator(terminals, non_terminals);
    parsingTableGenerator.computeFirst();
    parsingTableGenerator.computeFollow();
    parsingTableGenerator.constructParsingTable();
    for (auto &&non_terminal  : non_terminals) {
        cout<<non_terminal.getName_()<<": ";
        for (auto &&cell : non_terminal.getParse_table_entry_()) {
            cout<<"("<<cell.first<<", "<<cell.second<<")"<<", ";
        }
        cout<<endl;
    }
};