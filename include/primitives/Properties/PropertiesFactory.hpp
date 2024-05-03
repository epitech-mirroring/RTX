/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdexcept>
#include "json/Json.hpp"
#include "primitives/Properties/AbstractProperties.hpp"
#include "primitives/Properties/RectangleProperties.hpp"

class PropertiesFactory {
public:
    PropertiesFactory() = default;
    AbstractProperties *createProperties(const std::string &type, JsonObject *obj);
    void registerProperties(const std::string &type, std::function<AbstractProperties *(JsonObject *)> creator);

private:
    std::unordered_map<std::string, std::function<AbstractProperties *(JsonObject *)>> _creators{};
};
