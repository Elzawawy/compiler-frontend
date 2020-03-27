//
// Created by zawawy on 3/27/20.
//

#ifndef LEXGEN_REGULAR_EXPRESSION_H
#define LEXGEN_REGULAR_EXPRESSION_H

#include <string>

class RegularExpression {
private:
    std::string name;
    std::string value;
public:
    RegularExpression(const std::string& name, const std::string& value);
    const std::string& getName() const;
    const std::string& getValue() const;

};

#endif //LEXGEN_REGULAR_EXPRESSION_H
