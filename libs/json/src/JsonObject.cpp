/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/JsonObject.hpp"
#include <fstream>
#include "json/JsonArray.hpp"
#include "json/JsonBoolean.hpp"
#include "json/JsonInt.hpp"
#include "json/JsonString.hpp"

std::string JsonObject::getType() const {
    return "object";
}

JsonObject::~JsonObject() {
    for (auto &obj : this->_objects)
        delete obj.second;
}

JsonObject::JsonObject(const std::string &name) {
    this->_name = name;
    this->_is_null = false;
}

void JsonObject::remove(const std::string &name) {
    this->_objects.erase(name);
}

std::string JsonObject::getName() const {
    return this->_name;
}

bool JsonObject::isNull(const std::string &name) const {
    if (this->_objects.find(name) == this->_objects.end())
        return true;
    auto *obj = dynamic_cast<JsonObject *>(this->_objects.at(name));
    if (obj == nullptr)
        return true;
    return obj->_is_null;
}

bool JsonObject::isNull() const {
    return this->_is_null;
}

void JsonObject::setNull(bool is_null) {
    this->_is_null = is_null;
}

void JsonObject::addValue(IJsonObject *value) {
    this->_objects[value->getName()] = value;
}

std::string JsonObject::stringify() const {
    if (this->_is_null)
        return "null";
    std::string str = "{";
    for (auto &obj : this->_objects) {
        str += "\"" + obj.first + "\":" + obj.second->stringify() + ",";
    }
    if (str.back() == ',')
        str.pop_back();
    str += "}";
    return str;
}

std::size_t JsonObject::findContextEnd(const std::string &string, std::size_t start) {
    int nb_braces = 0;
    bool in_string = false;
    std::size_t len = string.length();
    std::size_t current = start;

    while (string[current] != ':' && current < len)
        current++;
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

std::size_t JsonObject::findContextStart(const std::string &string, std::size_t start) {
    std::size_t current = start;

    while (current < string.length() && string[current] != ':')
        current++;
    while (current < string.length() && string[current] != '{' && string[current] != '[' && string[current] != '"' && string[current] != 't' && string[current] != 'f' && string[current] != 'n' && (string[current] < '0' || string[current] > '9'))
        current++;
    return current;
}

std::string JsonObject::findKey(const std::string &string, std::size_t start) {
    std::size_t len = string.length();
    std::size_t current = start;
    while (current < len && string[current] != '"')
        current++;
    if (current == len)
        return "";
    return string.substr(start, current - start);
}

std::function<IJsonObject *(const std::string &)>
JsonObject::getParser(const std::string &obj, const std::string &key) {
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
    if (obj[0] >= '0' && obj[0] <= '9') {
        return [key](const std::string &str) -> IJsonObject * {
            auto *json = new JsonInt(key);
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

void JsonObject::parse(const std::string &string) {
    std::string cleaned = IJsonObject::cleanString(string);
    std::size_t len = cleaned.length();

    for (std::size_t i = 0; i < len; i++) {
        if (cleaned[i] != '"')
            continue;
        std::string key = findKey(cleaned, i + 1);
        std::size_t start = findContextStart(cleaned, i);
        std::size_t end = findContextEnd(cleaned, i + 1);
        if (end == len)
            end--;
        std::string obj = cleaned.substr(start, end - start);
        this->addValue(getParser(obj, key)(obj));
        i = end;
    }
}

void JsonObject::setNull(const std::string &name, bool is_null) {
    auto *obj = dynamic_cast<JsonObject *>(this->_objects.at(name));
    if (obj == nullptr && !is_null)
        return;
    if (obj == nullptr) {
        this->_objects[name] = new JsonObject(name);
        obj = dynamic_cast<JsonObject *>(this->_objects.at(name));
    }
    obj->_is_null = is_null;
}

JsonObject JsonObject::parseFile(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file");
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    JsonObject obj;
    obj.parse(str);
    file.close();
    return obj;
}

void JsonObject::writeToFile(const std::string &filename) const {
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file");
    file << this->stringify();
    file.close();
}

std::string JsonObject::getString(const std::string &key) const {
    auto *obj = dynamic_cast<JsonString *>(this->_objects.at(key));
    if (obj == nullptr)
        return "";
    return obj->getValue();
}

int JsonObject::getInt(const std::string &key) const {
    auto *obj = dynamic_cast<JsonInt *>(this->_objects.at(key));
    if (obj == nullptr)
        return 0;
    return obj->getValue();
}

bool JsonObject::getBoolean(const std::string &key) const {
    auto *obj = dynamic_cast<JsonBoolean *>(this->_objects.at(key));
    if (obj == nullptr)
        return false;
    return obj->getValue();
}

JsonObject *JsonObject::getObject(const std::string &key) const {
    auto *obj = dynamic_cast<JsonObject *>(this->_objects.at(key));
    if (obj == nullptr)
        return nullptr;
    return obj;
}

JsonArray *JsonObject::getArray(const std::string &key) const {
    auto *obj = dynamic_cast<JsonArray *>(this->_objects.at(key));
    if (obj == nullptr)
        return nullptr;
    return obj;
}
