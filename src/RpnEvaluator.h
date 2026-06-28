#pragma once
#include <string>
#include <optional>
#include <vector>

class RpnEvaluator
{
public:
    static std::optional<double> evaluate(const std::string& expression);

private:
    static std::vector<std::string> convertToRpn(const std::string& expression);
    static std::optional<double> calculateRpn(const std::vector<std::string>& rpn);
    static int get_precedence(char op);
};