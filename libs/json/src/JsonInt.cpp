/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonInt.hpp"

JsonInt::JsonInt(const std::string &name, int value) {
    this->_name = name;
    this->_value = value;
}

std::string JsonInt::stringify() const {
    return std::to_string(this->_value);
}

void JsonInt::parse(const std::string &string) {
    this->_value = std::stoi(string);
}

std::string JsonInt::getType() const {
    return "int";
}

std::string JsonInt::getName() const {
    return this->_name;
}

int JsonInt::getValue() const
{
    return this->_value;
}

void JsonInt::setValue(int value)
{
    this->_value = value;
}
