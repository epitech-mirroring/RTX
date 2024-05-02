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
#include <unordered_map>
#include <functional>

class ObjectsFactory {
public:
    ObjectsFactory();
    Object *createObject(const std::string& type, AbstractProperties &properties);
    void registerObject(const std::string& type, std::function<Object *(AbstractProperties&)> creator);
private:
    std::unordered_map<std::string, std::function<Object *(AbstractProperties &)>> _map{};
};
