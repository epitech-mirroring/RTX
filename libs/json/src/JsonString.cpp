/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonString.hpp"

JsonString::JsonString(const std::string &name, const std::string &value) {
    this->_name = name;
    this->_value = value;
}

std::string JsonString::stringify() const {
    return "\"" + this->_value + "\"";
}

void JsonString::parse(const std::string &string) {
    this->_value = string.substr(1, string.size() - 2);
}

std::string JsonString::getType() const {
    return "string";
}

std::string JsonString::getName() const {
    return this->_name;
}

const std::string &JsonString::getValue() const
{
    return this->_value;
}

void JsonString::setValue(const std::string &value)
{
    this->_value = value;
}
