//
// Created by zawawy on 3/27/20.
//

#include "regular_expression.h"
const std::string& RegularExpression::getName() const
{
    return name;
}
const std::string& RegularExpression::getValue() const
{
    return value;
}
RegularExpression::RegularExpression(const std::string& name, const std::string& value)
        :name(name), value(value) { }
