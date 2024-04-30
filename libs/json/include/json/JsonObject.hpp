/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>
#include <unordered_map>
#include <list>
#include <type_traits>
#include "IJsonObject.hpp"
#include <functional>

class JsonObject: public IJsonObject {
protected:
    std::string _name;
    std::unordered_map<std::string, IJsonObject *> _objects;
    bool _is_null;
private:
    static std::size_t findContextEnd(const std::string &string, std::size_t start);
    static std::size_t findContextStart(const std::string &string, std::size_t start);
    static std::string findKey(const std::string &string, std::size_t start);
    static std::function<IJsonObject *(const std::string &)> getParser(const std::string &obj, const std::string &key);
public:
    JsonObject(const std::string &name = "root");
    ~JsonObject() override;
    void remove(const std::string &name);
    std::string getName() const override;
    bool isNull(const std::string &name) const;
    bool isNull() const;
    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    template<typename T>
    T *getValue(const std::string &key) const {
        static_assert(std::is_base_of<IJsonObject, T>::value, "T must inherit from IJsonObject");
        return dynamic_cast<T *>(_objects.at(key));
    }
    void addValue(IJsonObject *value);
    void setNull(const std::string &name, bool is_null);
    void setNull(bool is_null);

    static JsonObject parseFile(const std::string &filename);
    void writeToFile(const std::string &filename) const;
};
