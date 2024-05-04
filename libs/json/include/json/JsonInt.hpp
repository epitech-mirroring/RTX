/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "IJsonObject.hpp"

class JsonInt : public IJsonObject {
protected:
    std::string _name;
    int _value;
public:
    JsonInt(const std::string &name, int value = 0);
    ~JsonInt() override = default;

    std::string stringify() const override;
    void parse(const std::string &string) override;
    std::string getType() const override;
    std::string getName() const override;
    int getValue() const;
    void setValue(int value);
};
