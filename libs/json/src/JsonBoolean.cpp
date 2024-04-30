/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonBoolean.hpp"

JsonBoolean::JsonBoolean(const std::string &name, bool value) {
    this->_name = name;
    this->_value = value;
}

std::string JsonBoolean::stringify() const {
    return this->_value ? "true" : "false";
}

void JsonBoolean::parse(const std::string &string) {
    if (string == "true")
        this->_value = true;
    else if (string == "false")
        this->_value = false;
}

std::string JsonBoolean::getType() const {
    return "boolean";
}

std::string JsonBoolean::getName() const {
    return this->_name;
}

bool JsonBoolean::getValue() const
{
    return this->_value;
}

void JsonBoolean::setValue(bool value)
{
    this->_value = value;
}
