/**
    Compiler Front-end Project
    utils.h
    Purpose: contains generic multiple methods to be reused by more than one component.

    @author Amr Elzawawy
    @version 1.0
    @date 29/3/2020
*/

#ifndef LEXGEN_UTILS_H
#define LEXGEN_UTILS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

namespace util {

/**
    Removes trailing and starting spaces from a string. (in-place)
    @param str the string to remove from.
*/
void trimBothEnds(std::string& str)
{
    const std::string& chars = "\t\n\v\f\r ";
    str.erase(str.find_last_not_of(chars)+1);
    str.erase(0, str.find_first_not_of(chars));
}

/**
    Removes the first and last chars whatever their value from a string. (in-place)
    @param str the string to remove from.
*/
void stripFirstAndLastChars(std::string& str)
{
    str.erase(0, 1);
    str.erase(str.length()-1, str.length()-1);
}

/**
    Removes all spaces in every position from a string. (in-place)
    @param str the string to remove from.
*/
void removeAllSpaces(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

/**
    Splits a string on any given delimiter character into a vector of tokens.
    @param str the string to operate on.
    @return vector<string> the tokens resulted from the split of the string.
*/
std::vector<std::string> splitOnDelimiter(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

/**
    A Generic Comparable Function that works on pairs and defines comparability based on first element's length.
    @param a the first pair in comparison.
    @param b the second pair in comparison.
    @return bool a boolean that is true if the first pair is larger and false otherwise.
*/
template<class T>
bool comparePairsAccordingToFirstLength(const std::pair<T, T>& a,
        const std::pair<T, T>& b)
{
    return a.first.length()>b.first.length();
}
}
#endif //LEXGEN_UTILS_H
