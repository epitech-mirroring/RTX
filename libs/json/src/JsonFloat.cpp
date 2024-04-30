/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonFloat.hpp"

JsonFloat::JsonFloat(const std::string &name, double value) {
    this->_name = name;
    this->_value = value;
}

std::string JsonFloat::stringify() const {
    return std::to_string(this->_value);
}

void JsonFloat::parse(const std::string &string) {
    this->_value = std::stod(string);
}

std::string JsonFloat::getType() const {
    return "float";
}

std::string JsonFloat::getName() const {
    return this->_name;
}

double JsonFloat::getValue() const
{
    return this->_value;
}

void JsonFloat::setValue(double value)
{
    this->_value = value;
}
