//
// Created by zawawy on 3/29/20.
//

#ifndef LEXGEN_UTILS_H
#define LEXGEN_UTILS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

namespace util {

void trimBothEnds(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars)+1);
    str.erase(0, str.find_first_not_of(chars));
}

void stripFirstAndLastChars(std::string& str)
{
    str.erase(0, 1);
    str.erase(str.length()-1, str.length()-1);
}
void removeAllSpaces(std::string & str){
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}
std::vector<std::string> splitOnDelimiter(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}
template<class T>
bool comparePairsAccordingToFirstLength(const std::pair<T, T>& a,
        const std::pair<T, T>& b)
{
    return a.first.length()>b.first.length();
}

template<class T>
void insertInSetIfNotExists(std::unordered_set<T>& set, T element)
{
    if (set.count(element)==0)
        set.insert(element);
}
}
#endif //LEXGEN_UTILS_H
