/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <cstddef>
#include <vector>
#include <functional>
#include "IJsonObject.hpp"

class JsonArray : public IJsonObject {
protected:
    std::string _name;
    std::vector<IJsonObject *> _values;
private:
    static std::size_t findContextEnd(const std::string &string, std::size_t start);
    static std::function<IJsonObject *(const std::string &)> getParser(const std::string &obj, const std::string &key);
public:
    JsonArray(const std::string &name = "root");
    ~JsonArray() override;

    void addValue(IJsonObject *value);
    void removeValue(std::size_t index);
    std::size_t size() const;
    template<typename T>
    T *getValue(const std::size_t &index) const {
        static_assert(std::is_base_of<IJsonObject, T>::value, "T must inherit from IJsonObject");
        return dynamic_cast<T *>(_values.at(index));
    }
    std::vector<IJsonObject *> getValues() const;
    std::string getName() const override;
    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    bool isNull(const std::size_t &index) const;

    static JsonArray parseFile(const std::string &filename);
    void writeToFile(const std::string &filename) const;
};
