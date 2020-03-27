#include <iostream>
#include "language_parser.h"

int main() {
    auto language_parser = new LanguageParser();
    language_parser->parseFile("../test_cases/a_lexical_rules.txt");

    return 0;
}