#include "rule.hpp"

Rule::Rule(const std::string ruleName) : name(ruleName) {}
std::string Rule::getName() const { return this->name; }