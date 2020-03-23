//
// Created by omar_swidan on 23/03/20.
//

#include "file_parser.h"

const unordered_set <string> &FileParser::getInput_table() const {
    return input_table;
}

const vector <string> &FileParser::getRegular_expressions() const {
    return regular_expressions;
}
