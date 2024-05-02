/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/objectsFactory.hpp"
#include <stdexcept>
#include "primitives/Cube.hpp"

Object ObjectsFactory::createObject(JsonObject *obj)
{
    if (_map.find(obj->getString("type")) == _map.end())
        throw std::invalid_argument("Error: Invalid object type");
    return _map[obj->getString("type")](obj);
}

std::unordered_map<std::string, std::function<Object(JsonObject*)>> ObjectsFactory::_map = {
    {"cube", [](JsonObject *obj) { return Cube(obj); }}
};
