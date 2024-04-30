/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "IJsonObject.hpp"

class JsonBoolean : public IJsonObject {
protected:
    bool _value;
    std::string _name;
public:
    JsonBoolean(const std::string &name, bool value = false);
    ~JsonBoolean() override = default;

    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    std::string getName() const override;
    bool getValue() const;
    void setValue(bool value);
};
