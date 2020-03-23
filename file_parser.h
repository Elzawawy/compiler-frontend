//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_FILEPARSER_H
#define LEXGEN_FILEPARSER_H

using namespace std;

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>

class FileParser {
public:
    FileParser(string fileName);

    void ParseFile();

    const unordered_set<string> &getInput_table() const;

    const vector<string> &getRegular_expressions() const;

private:
    unordered_set<string> input_table;
    vector<string> regular_expressions;


};


#endif //LEXGEN_FILEPARSER_H
