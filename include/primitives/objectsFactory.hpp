/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Object.hpp"
#include "json/Json.hpp"

class ObjectsFactory {
public:
    static Object createObject(JsonObject *obj);
private:
    static std::unordered_map<std::string, std::function<Object(JsonObject*)>> _map;
};
