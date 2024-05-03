/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "primitives/ObjectsFactory.hpp"
#include <stdexcept>
#include <utility>
#include "primitives/Cube.hpp"

Object *ObjectsFactory::createObject(const std::string& type, AbstractProperties &properties)
{
    if (_map.find(type) == _map.end())
        throw std::runtime_error("Unknown object type: " + type);
    return _map[type](properties);
}

void ObjectsFactory::registerObject(const std::string& type, std::function<Object *(AbstractProperties&)> creator)
{
    _map[type] = std::move(creator);
}
