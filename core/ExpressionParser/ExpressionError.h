#pragma once

#include <stdexcept>
#include <string>
#include <limits>

class ExpressionError : public std::runtime_error
{
public:
    explicit ExpressionError(const std::string& message) : std::runtime_error(message)
    {
    }
};
