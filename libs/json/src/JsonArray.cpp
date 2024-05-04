/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonArray.hpp"
#include "json/JsonString.hpp"
#include "json/JsonInt.hpp"
#include "json/JsonBoolean.hpp"
#include "json/JsonObject.hpp"
#include "json/JsonFloat.hpp"
#include <fstream>
#include <iostream>

JsonArray::JsonArray(const std::string &name) {
    this->_name = name;
}

JsonArray::~JsonArray() {
    for (auto &obj : this->_values)
        delete obj;
}

std::string JsonArray::stringify() const {
    std::string str = "[";
    for (auto &elem : this->_values) {
        str += elem->stringify();
        if (&elem != &this->_values.back())
            str += ",";
    }
    str += "]";
    return str;
}

std::function<IJsonObject *(const std::string &)>
JsonArray::getParser(const std::string &obj, const std::string &key) {
    if (obj[0] == '{') {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonObject(key);
            json->parse(str);
            return json;
        };
    }
    if (obj[0] == '[') {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonArray(key);
            json->parse(str);
            return json;
        };
    }
    if (obj[0] == '"') {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonString(key);
            json->parse(str);
            return json;
        };
    }
    if ((obj[0] >= '0' && obj[0] <= '9' || obj[0] == '-' || obj[0] == '+')
        && obj.find('.') == std::string::npos) {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonInt(key);
            json->parse(str);
            return json;
        };
    }
    if ((obj[0] >= '0' && obj[0] <= '9' || obj[0] == '-' || obj[0] == '+')
        && obj.find('.') != std::string::npos) {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonFloat(key);
            json->parse(str);
            return json;
        };
    }
    if (obj == "true" || obj == "false") {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonBoolean(key);
            json->parse(str);
            return json;
        };
    }

    return [key](const std::string &str) -> IJsonObject * {
        (void)str;
        auto *json = new JsonObject(key);
        json->setNull(true);
        return json;
    };
}

std::size_t JsonArray::findContextEnd(const std::string &string, std::size_t start) {
    int nb_braces = 0;
    bool in_string = false;
    std::size_t len = string.length();
    std::size_t current = start;

    while (current < len && (nb_braces > 0 || string[current] != ',' || in_string)) {
        if (string[current] == '"')
            in_string = !in_string;
        if (string[current] == '{' || string[current] == '[')
            nb_braces++;
        if (string[current] == '}' || string[current] == ']')
            nb_braces--;
        current++;
    }
    return current;
}

void JsonArray::parse(const std::string &string) {
    std::string cleaned = IJsonObject::cleanString(string);
    std::size_t len = cleaned.length();
    std::size_t start = 1;

    this->_values.clear();
    while (start < len) {
        std::size_t end = JsonArray::findContextEnd(cleaned, start);
        if (end == len)
            end--;
        std::string obj = cleaned.substr(start, end - start);
        if (obj.empty())
            break;
        _values.push_back(getParser(obj, std::to_string(this->size()))(obj));
        start = end + 1;
    }
}

bool JsonArray::isNull(const std::size_t &index) const {
    auto *obj = dynamic_cast<JsonObject *>(_values.at(index));
    if (obj == nullptr)
        return false;
    return obj->isNull();
}

std::string JsonArray::getName() const {
    return this->_name;
}

std::string JsonArray::getType() const {
    return "array";
}

std::size_t JsonArray::size() const {
    return this->_values.size();
}

JsonArray JsonArray::parseFile(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file");
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    JsonArray obj;
    obj.parse(str);
    file.close();
    return obj;
}

void JsonArray::writeToFile(const std::string &filename) const {
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file");
    file << this->stringify();
    file.close();
}

void JsonArray::addValue(IJsonObject *value) {
    this->_values.push_back(value);
}
