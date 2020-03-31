#include <iostream>

#include "nfa.h"
#include "language_parser.h"

int main()
{

    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");
    NFA x=NFA();
    x.regex_to_nfa(language_parser->getInput_table(),language_parser->getExpressions());
    return 0;
}