#pragma once

#include <limits>
#include <stdexcept>
#include <string>

class ExpressionError : public std::runtime_error
{
public:
	explicit ExpressionError(const std::string& message) : std::runtime_error(message) {}
};
