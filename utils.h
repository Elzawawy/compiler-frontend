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
    if(str.size()> 2) {
        str.erase(0, 1);
        str.erase(str.length()-1);
    }
}

/**
    Removes all spaces in every position from a string. (in-place)
    @param str the string to remove from.
*/
void removeAllSpaces(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void removeExtraSpaces(std::string& str)
{
    bool seen_space = false;
    auto end{ std::remove_if(str.begin(), str.end(),
            [&seen_space](unsigned ch) {
              bool is_space = std::isspace(ch);
              std::swap(seen_space, is_space);
              return seen_space && is_space;
            }
    )
    };
    if (end != str.begin() && std::isspace(static_cast<unsigned>(end[-1])))
        --end;

    str.erase(end, str.end());
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

std::vector<std::string> splitOnFirstOfDelimiters(const std::string& str, const std::string& delimiters)
{
    std::size_t current, previous = 0;
    std::vector<std::string> tokens;
    current = str.find_first_of(delimiters);
    while (current!=std::string::npos) {
        std::string token = str.substr(previous, current-previous);
        tokens.push_back(token);
        previous = current+1;
        current = str.find_first_of(delimiters, previous);
    }
    tokens.push_back(str.substr(previous, current-previous));
    return tokens;
}

std::vector<std::string> splitOnStringDelimiter(const std::string& str, const std::string& delimiter)
{
    size_t pos_start = 0, pos_end, delimiter_len = delimiter.length();
    std::string token;
    std::vector<std::string> tokens;

    while ((pos_end = str.find(delimiter, pos_start))!=std::string::npos) {
        token = str.substr(pos_start, pos_end-pos_start);
        pos_start = pos_end+delimiter_len;
        tokens.push_back(token);
    }
    tokens.push_back(str.substr(pos_start));
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
