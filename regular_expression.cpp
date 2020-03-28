//
// Created by zawawy on 3/27/20.
//

#include "regular_expression.h"
const std::string& regular_expression::getName() const
{
    return name;
}
const std::string& regular_expression::getValue() const
{
    return value;
}
regular_expression::regular_expression(const std::string& name, const std::string& value)
        :name(name), value(value) { }
