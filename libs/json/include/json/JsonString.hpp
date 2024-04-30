/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>
#include "IJsonObject.hpp"

class JsonString : public IJsonObject {
protected:
    std::string _value;
    std::string _name;
public:
    JsonString(const std::string &name, const std::string &value = "");
    ~JsonString() override = default;

    const std::string &getValue() const;
    void setValue(const std::string &value);
    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    std::string getName() const override;
};
