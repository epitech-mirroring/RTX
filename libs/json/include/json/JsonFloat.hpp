/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "IJsonObject.hpp"

class JsonFloat : public IJsonObject {
protected:
    std::string _name;
    double _value;
public:
    JsonFloat(const std::string &name, double value = 0);
    ~JsonFloat() override = default;

    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    std::string getName() const override;
    double getValue() const;
    void setValue(double value);
};
