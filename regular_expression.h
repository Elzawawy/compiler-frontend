//
// Created by zawawy on 3/27/20.
//

#ifndef LEXGEN_REGULAR_EXPRESSION_H
#define LEXGEN_REGULAR_EXPRESSION_H

#include <string>

class regular_expression {
private:
    std::string name;
    std::string value;
public:
    regular_expression(const std::string& name, const std::string& value);
    const std::string& getName() const;
    const std::string& getValue() const;

};

#endif //LEXGEN_REGULAR_EXPRESSION_H
